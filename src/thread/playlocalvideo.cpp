#include "playlocalvideo.h"
#include "allwidget.h"

PlayLocalVideo::PlayLocalVideo()
{

}

bool PlayLocalVideo::CreatePlayState(QString url)
{
    m_stop = false;
    ret = -1;
    speed = 50;
    down = 0;
    up = 0;
    pPlayState = new PlayState;
    pPlayState->pFormatContext = NULL;
    pPlayState->pAVCodecContext = NULL;
    pPlayState->pAVFrameIn = NULL;
    pPlayState->pAVFrameOutRGB = NULL;
    pPlayState->pAVPacket = NULL;
    pPlayState->pAVCodec = NULL;
    pPlayState->pSwsContext = NULL;
    pPlayState->out_buffer = NULL;
    pPlayState->out_file_yuv = NULL;
    pPlayState->av_stream_index = -1;


    qDebug()<<"第一步：注册所有组件";
    av_register_all();

    qDebug()<<"第二步：打开视频输入文件";
    pPlayState->pFormatContext = avformat_alloc_context();
    ret = avformat_open_input(&pPlayState->pFormatContext,url.toStdString().c_str(),NULL,NULL);
    if (ret != 0)
    {
        //获取异常信息
        char* error_info = new char[32];
        av_strerror(ret, error_info, 1024);
        qDebug()<<QString("异常信息 %1").arg(ret);
        return false;
    }

    qDebug()<<"第三步：查找视频文件信息";
    ret = avformat_find_stream_info(pPlayState->pFormatContext, NULL);
    if (ret < 0)
    {
        //获取失败
        char* error_info = new char[32];
        av_strerror(ret, error_info, 1024);
        qDebug()<<QString("异常信息 %1").arg(error_info);
        return false;
    }

    qDebug()<<"第四步：查找解码器";
    pPlayState->av_stream_index = -1;
    for (int i = 0; i < pPlayState->pFormatContext->nb_streams; ++i) {
        //循环遍历每一流
        //视频流、音频流、字幕流等等...
        if (pPlayState->pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            //找到了
            pPlayState->av_stream_index = i;
            break;
        }
    }
    if (pPlayState->av_stream_index == -1 )
    {
        qDebug()<<QString("没有找到视频流");
        return false;
    }
    //第二点：根据视频流->查找到视频解码器上下文->视频压缩数据
    pPlayState->pAVCodecContext = pPlayState->pFormatContext->streams[pPlayState->av_stream_index]->codec;

    //第三点：根据解码器上下文->获取解码器ID
    pPlayState->pAVCodec = avcodec_find_decoder(pPlayState->pAVCodecContext->codec_id);
    if (pPlayState->pAVCodec == NULL)
    {
        qDebug()<<QString("没有找到视频解码器");
        return false;
    }

    qDebug()<<"第五步：打开解码器";
    //第五步：打开解码器
    ret = avcodec_open2(pPlayState->pAVCodecContext,pPlayState->pAVCodec,NULL);
    if (ret != 0)
    {
        char* error_info = new char[32];
        av_strerror(ret, error_info, 1024);
        qDebug()<<QString("异常信息 %1").arg(error_info);
        return false;
    }
    //输出视频信息
    //输出：文件格式
    qDebug()<<QString("文件格式： %1").arg(pPlayState->pFormatContext->iformat->name);
    //输出：解码器名称
    qDebug()<<QString("解码器名称： %1").arg(pPlayState->pAVCodec->name);
    qDebug()<<QString("宽 %1 高 %2").arg(pPlayState->pAVCodecContext->width).arg(pPlayState->pAVCodecContext->height);

    //此函数打印输入或输出的详细信息
    av_dump_format(pPlayState->pFormatContext, 0, url.toStdString().c_str(), 0);

    return true;
}

void PlayLocalVideo::run()
{
    qDebug() << "线程开始";
    qDebug()<<"第六步：循环读取视频帧，进行循环解码";
    //准备读取
    //AVPacket用于存储一帧一帧的压缩数据（H264）
    //缓冲区，开辟空间
    pPlayState->pAVPacket = (AVPacket*)av_malloc(sizeof(AVPacket));

    //输入->环境一帧数据->缓冲区->类似于一张图
    pPlayState->pAVFrameIn = av_frame_alloc();
    //输出->帧数据->数据格式->RGB
    pPlayState->pAVFrameOutRGB = av_frame_alloc();
    //只有指定了AVFrame的像素格式、画面大小才能真正分配内存
    //缓冲区分配内存
    pPlayState->out_buffer = (uint8_t *)av_malloc(avpicture_get_size(
                                                       AV_PIX_FMT_RGB32, pPlayState->pAVCodecContext->width, pPlayState->pAVCodecContext->height));
    //初始化缓冲区
    avpicture_fill((AVPicture *)pPlayState->pAVFrameOutRGB, pPlayState->out_buffer,
                   AV_PIX_FMT_RGB32, pPlayState->pAVCodecContext->width, pPlayState->pAVCodecContext->height);

    //解码的状态类型(0:表示解码完毕，非0:表示正在解码)
    int current_frame_index = 0;

    //用于转码（缩放）的参数，转之前的宽高，转之后的宽高，格式等
    //准备一个视频像素数据格式上下文
    //参数一：输入帧数据宽
    //参数二：输入帧数据高
    //参数三：输入帧数据格式
    //参数四：输出帧数据宽
    //参数五：输出帧数据高
    //参数六：输出帧数据格式->AV_PIX_FMT_RGB32
    //参数七：视频像素数据格式转换算法类型
    //参数八：字节对齐类型(C/C++里面)->提高读取效率
    pPlayState->pSwsContext = sws_getContext(pPlayState->pAVCodecContext->width,
                                              pPlayState->pAVCodecContext->height,
                                              pPlayState->pAVCodecContext->pix_fmt,
                                              pPlayState->pAVCodecContext->width,
                                              pPlayState->pAVCodecContext->height,
                                              AV_PIX_FMT_RGB32,
                                              SWS_BICUBIC,NULL,NULL,NULL);

    //m_lock.lock();
    while(!m_stop)
    {
        while (av_read_frame(pPlayState->pFormatContext, pPlayState->pAVPacket) >= 0)
        {
            m_lock.lock();
            //如果是视频数据
            if (pPlayState->pAVPacket->stream_index == pPlayState->av_stream_index)
            {
                //解码一帧视频数据
                avcodec_send_packet(pPlayState->pAVCodecContext, pPlayState->pAVPacket);

                //接收一帧数据->解码一帧
                ret = avcodec_receive_frame(pPlayState->pAVCodecContext,pPlayState->pAVFrameIn);

                if (ret == 0)
                {
                    sws_scale(pPlayState->pSwsContext, (const unsigned char* const*)pPlayState->pAVFrameIn->data, pPlayState->pAVFrameIn->linesize, 0, pPlayState->pAVCodecContext->height,
                              pPlayState->pAVFrameOutRGB->data,  pPlayState->pAVFrameOutRGB->linesize);

                    QImage  *tmpImg  = new QImage((uchar *)pPlayState->out_buffer, pPlayState->pAVCodecContext->width,
                                                  pPlayState->pAVCodecContext->height,QImage::Format_RGB32);

                    QImage image=tmpImg->copy();    //拷贝

  //                  qDebug()<<"接收图片信号"<<image;

                    emit sigGetOneFrame(image);
                    current_frame_index++;
                    qDebug()<<QString("视频遍历第 %1 帧").arg(current_frame_index);
                    msleep(speed);
                }
            }
            m_lock.unlock();
        }
        av_free_packet(pPlayState->pAVPacket);
        msleep(30);
        this->stop();
    }
    AllWidget::pShowVideoWidget->setPlayButton();
    av_packet_free(&pPlayState->pAVPacket);
    sws_freeContext(pPlayState->pSwsContext);
    av_frame_free(& pPlayState->pAVFrameOutRGB);
    av_frame_free(&pPlayState->pAVFrameIn);
    avcodec_close(pPlayState->pAVCodecContext);
    avformat_close_input(&pPlayState->pFormatContext);
}

void PlayLocalVideo::psSlot()
{
    mask = ~mask;
    if(mask != 1){
        m_lock.lock();
    }
    else{
        m_lock.unlock();
    }
}

void PlayLocalVideo::stop()
{
    m_stop = true;
}

int PlayLocalVideo::downSpeed()
{
    down++;
    speed = speed + down*10;
    if(speed > 90){
        speed = 90;
        qDebug() << "speed max";
        down--;
    }
    return speed;
}

int PlayLocalVideo::upSpeed()
{
    up++;
    speed = speed - up*10;
    if(speed < 10){
        speed = 10;
        qDebug() << "speed min";
        up--;
    }
    return speed;
}
