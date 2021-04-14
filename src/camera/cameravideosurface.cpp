#include "cameravideosurface.h"
#include "allwidget.h"
#include <QDateTime>


CameraVideoSurface::CameraVideoSurface(QObject *parent) : QAbstractVideoSurface(
      parent),
      pOutputFormatCtx(NULL),
      pCodec(NULL),
      pOutputStream(NULL),
      packet(NULL),
      yuvFrame(NULL),
      image_convert_ctx(NULL)
{
//    this->InitEncoder();
}

CameraVideoSurface::~CameraVideoSurface()
{
    av_write_trailer(pOutputFormatCtx);
    avio_close(pOutputFormatCtx->pb);
    avformat_close_input(&pOutputFormatCtx);
    av_frame_free(&yuvFrame);
    av_packet_free(&packet);
    avcodec_close(pCodecCtx);
}

void CameraVideoSurface::setCameraResolution(const QSize &size)
{
    this->setNativeResolution(size);
}

QList<QVideoFrame::PixelFormat> CameraVideoSurface::supportedPixelFormats
(QAbstractVideoBuffer::HandleType handleType) const
{
    QList<QVideoFrame::PixelFormat > pixelFormats;
    pixelFormats.append(QVideoFrame::Format_RGB32);
    pixelFormats.append(QVideoFrame::Format_YUV420P);
    return pixelFormats;
}

bool CameraVideoSurface::present(const QVideoFrame &frame)
{
    if(!AllWidget::pLoginWidget->CurUser.isEmpty() && !AllWidget::pSettingWidget->pSettingPath->ImagePath.isEmpty()){
        if (frame.isValid()){
            QVideoFrame cloneFrame(frame);
            cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
            QImage image(cloneFrame.bits(), cloneFrame.width(), cloneFrame.height(),
                         QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));
            image = image.mirrored(true, true);

            // rgb 转 yuv
            uint8_t *data[AV_NUM_DATA_POINTERS] = {0};
            data[0] = (uint8_t *)image.constBits();
            int linesize[AV_NUM_DATA_POINTERS] = {0};
            linesize[0] = pCodecCtx->width * 4;
            sws_scale(image_convert_ctx, data, linesize, 0, pCodecCtx->height,
                      yuvFrame->data, yuvFrame->linesize);
            // 编码
            this->Encode(yuvFrame);
            emit showFrame(image);
            if(FirstImg == 0){
                image.save(QString("%1.jpg").arg(FileName));
                FirstImg++;
            }
            cloneFrame.unmap();
            return true;
        }
        return false;
    }
    return false;
}

void CameraVideoSurface::InitEncoder()
{
    FirstImg = 0;

    av_register_all();
    avformat_network_init();
    avcodec_register_all();

    FileName = AllWidget::pSettingWidget->pSettingPath->VideoPath;
    QString CurDate = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    FileName = QString("%1/%2").arg(FileName).arg(CurDate);
    OutPutFileName = QString("%1.h264").arg(FileName);
    qDebug() << OutPutFileName;

    QString encoderName = "libx264";
    //QString rtmpAddress = "rtmp://192.168.1.111/live/livestream";

    pCodec = avcodec_find_encoder_by_name(encoderName.toStdString().c_str());
    if(NULL == pCodec){
        qDebug() <<"查找视频编码器失败！";
        return;
    }

    pCodecCtx = avcodec_alloc_context3(pCodec);
    if(NULL == pCodecCtx){
        qDebug() <<"开辟编解码器上下文";
        return;
    }
    // 输入样本参数
    pCodecCtx->bit_rate = 400000;
    pCodecCtx->width = 1280/2;
    pCodecCtx->height = 720/2;
    pCodecCtx->time_base = {1, 25};
    pCodecCtx->framerate = {25, 1};
    pCodecCtx->gop_size = 10;
    pCodecCtx->max_b_frames = 1;
    pCodecCtx->qmin = 10;
    pCodecCtx->qmax = 51;
    pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;

    if(AV_CODEC_ID_H264 == pCodecCtx->codec_id){
        av_opt_set(pCodecCtx->priv_data, "preset", "slow", 0);
        av_opt_set(pCodecCtx->priv_data, "tune", "zerolatency", 0);
    }

    // 打开编码器
    if(avcodec_open2(pCodecCtx, pCodec, NULL) < 0){
        qDebug() <<"打开编码器失败 !";
        return;
    }

    pOutputFormatCtx = avformat_alloc_context();
    if(NULL == pOutputFormatCtx){
        qDebug() <<"视频封装器开辟失败!";
        return;
    }

    AVOutputFormat *outputFormat = av_guess_format(NULL, OutPutFileName.toStdString().c_str(), NULL);
    if(NULL == outputFormat){
        qDebug() <<"猜测outputformat失败 !";
        return;
    }

    pOutputFormatCtx->oformat = outputFormat;
    // oprn url
    if(avio_open(&pOutputFormatCtx->pb, OutPutFileName.toStdString().c_str(), AVIO_FLAG_READ_WRITE) < 0){
        qDebug() <<"打开输出文件失败!";
        return;
    }

    pOutputStream = avformat_new_stream(pOutputFormatCtx, NULL);
    if(NULL == pOutputStream){
        qDebug() <<"新建输出流失败 !";
        return;
    }
    // 输出详细信息
    av_dump_format(pOutputFormatCtx, 0, OutPutFileName.toStdString().c_str(), 1);
    // 新建数据包
    packet = av_packet_alloc();
    if(NULL == packet){
        qDebug() <<"新建数据包失败 !";
        return;
    }
    // yuvFrame 初始化
    yuvFrame = av_frame_alloc();
    if(NULL == yuvFrame){
        qDebug() <<"开辟AVFrame失败 !";
        return;
    }
    yuvFrame->width = pCodecCtx->width;
    yuvFrame->height = pCodecCtx->height;
    yuvFrame->format = pCodecCtx->pix_fmt;
    // 初始化 image 空间
    av_image_alloc(yuvFrame->data, yuvFrame->linesize, yuvFrame->width, yuvFrame->height,
                       pCodecCtx->pix_fmt, 32);
    // 转换上下文
    image_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB32, pCodecCtx->width,
                                       pCodecCtx->height, AV_PIX_FMT_YUV420P,
                                       SWS_BICUBIC, NULL, NULL, NULL);
    if(NULL == image_convert_ctx){
        qDebug() <<"转换上下文失败 !";
        return;
    }
    // 写封装头
    if(avformat_write_header(pOutputFormatCtx, NULL) < 0){
        qDebug() <<"视频封装头写失败 !";
        return;
    }   
}

// 编码为 h.264
void CameraVideoSurface::Encode(AVFrame *frame)
{
    static int index = 0;
    frame->pts = index++;

    int ret = 0;
    if((ret = avcodec_send_frame(pCodecCtx, frame)) < 0){
        qDebug() <<"avcodec_send_frame 失败 !";
        return;
    }

    while(ret >= 0)
    {
        ret = avcodec_receive_packet(pCodecCtx, packet);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF){
            return;
        }
        else if (ret < 0){
            qDebug() <<  "编码时出错";
            return;
        }
        packet->stream_index = 0;
        av_interleaved_write_frame(pOutputFormatCtx, packet); // write frame
        av_packet_unref(packet);
    }
}

void CameraVideoSurface::escEvent()
{
    qDebug()<<"关闭摄像头";
    av_write_trailer(pOutputFormatCtx);
    avio_close(pOutputFormatCtx->pb);
    av_frame_free(&yuvFrame);
    avcodec_close(pCodecCtx);
    QString CurDate = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    pSqlData->insert_sourcetable(
                AllWidget::pLoginWidget->CurUser,
                CurDate,
                "video",
                AllWidget::pSettingWidget->pSettingPath->VideoPath);
    AllWidget::pSettingWidget->pSettingPath->ImagePath.clear();
    AllWidget::pSettingWidget->pSettingPath->VideoPath.clear();
    AllWidget::pSettingWidget->pSettingPath->TimeInterval.clear();
}

void CameraVideoSurface::cameraStopSlot()
{
    qDebug()<<"关闭摄像头";
    av_write_trailer(pOutputFormatCtx);
    avio_close(pOutputFormatCtx->pb);   
    av_frame_free(&yuvFrame);
    avcodec_close(pCodecCtx);
    QString CurDate = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    if(!AllWidget::pLoginWidget->CurUser.isEmpty()){
        pSqlData->insert_sourcetable(
                    AllWidget::pLoginWidget->CurUser,
                    CurDate,
                    "video",
                    AllWidget::pSettingWidget->pSettingPath->VideoPath);
    }
    InitEncoder();
}
