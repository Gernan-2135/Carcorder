#include "videodecode.h"
#include <QFileInfo>
#include <QMessageBox>

VideoDecode::VideoDecode()
{

}

VideoDecode::~VideoDecode()
{
    qDebug()<<"Format thread exit!";
    if(NULL!=pDecodeState->pFormatContext){
        avformat_close_input(&pDecodeState->pFormatContext);
        free(pDecodeState->pFormatContext);
    }
}

bool VideoDecode::CreateVideoDecode(QString url)
{
    //每次解码开始时 先将pDecodeState初始化 防止内存叠加占用
    fileLen=0;
    ret = -1;
    pDecodeState = new DecodeState;
    pDecodeState->pFormatContext = NULL;
    pDecodeState->outFormatContext = NULL;
    pDecodeState->outVideoStream = NULL;
    pDecodeState->inVideoStream = NULL;
    pDecodeState->videoStreamIndex = -1;
    pDecodeState->frameCount = 0;
    pDecodeState->startFlag = false;


    av_register_all();  //注册所有组件

    pDecodeState->pFormatContext = avformat_alloc_context();
    ret = avformat_open_input(&pDecodeState->pFormatContext, url.toStdString().c_str(), NULL,NULL);
    if (ret < 0){
        qDebug()<<"Can not open:"<<url;
        return -1;
    }

    if (avformat_find_stream_info(pDecodeState->pFormatContext,NULL) < 0){
        qDebug()<<"Unable to get stream info!";
        return -1;
    }

    for (int i = 0; i < pDecodeState->pFormatContext->nb_streams; i++)
    {
        if (pDecodeState->pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
            pDecodeState->videoStreamIndex = i;
            break;
        }
    }
    if (pDecodeState->videoStreamIndex == -1){
       qDebug()<<"Unable to find video stream!";
       return -1;
    }

    QFileInfo fileInfo;
    fileInfo.setFile(url);
    if(!fileInfo.isFile()) return -1;
    fileLen = fileInfo.size()/1024;     //计算出文件大小 KB

    return true;
}

void VideoDecode::setFileName(QString filename)
{
    outFileName = filename;
}

bool VideoDecode::checkFileData()
{
    if(fileLen == NULL) {
        return false;
    }
    return true;
}

void VideoDecode::run()
{
    if(NULL==pDecodeState->pFormatContext) return;
    qDebug()<<"Thread start.";

    uint32_t sizeCount=0;

    pDecodeState->inVideoStream=pDecodeState->pFormatContext->streams[pDecodeState->videoStreamIndex];
    avformat_alloc_output_context2(&pDecodeState->outFormatContext, NULL, NULL,outFileName.toStdString().c_str());

    pDecodeState->outVideoStream = avformat_new_stream(pDecodeState->outFormatContext, NULL);
    avcodec_copy_context(pDecodeState->outVideoStream->codec,
                         pDecodeState->inVideoStream->codec);
    pDecodeState->outVideoStream->codec->codec_tag = 0;
    pDecodeState->outVideoStream->codec->flags = pDecodeState->inVideoStream->codec->flags;
    pDecodeState->outVideoStream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
    pDecodeState->outVideoStream->codec->time_base.num = pDecodeState->inVideoStream->avg_frame_rate.den;
    pDecodeState->outVideoStream->codec->time_base.den = pDecodeState->inVideoStream->avg_frame_rate.num;

    avio_open(&pDecodeState->outFormatContext->pb, outFileName.toStdString().c_str(), AVIO_FLAG_WRITE);
    avformat_write_header(pDecodeState->outFormatContext, NULL);

    while (av_read_frame(pDecodeState->pFormatContext, &pDecodeState->pAVPacket) >= 0)
    {
        sizeCount+=pDecodeState->pAVPacket.size/1024;
        emit sig(100*sizeCount/fileLen);

        if(pDecodeState->pAVPacket.stream_index==pDecodeState->videoStreamIndex){
            if(!pDecodeState->startFlag){
                if(pDecodeState->pAVPacket.flags)
                {
                    pDecodeState->startFlag=true;
                }
                else continue;
            }

            pDecodeState->frameCount++;
            //qDebug()<<"frame:"<<pDecodeState->frameCount;

            if(pDecodeState->pAVPacket.pts==AV_NOPTS_VALUE){
                //Write PTS
                AVRational time_base1=pDecodeState->inVideoStream->time_base;
                //Duration between 2 frames (us)
                int64_t calc_duration=(double)AV_TIME_BASE/av_q2d(pDecodeState->inVideoStream->r_frame_rate);
                //Parameters
                pDecodeState->pAVPacket.pts=(double)(pDecodeState->frameCount*calc_duration)/(double)(av_q2d(time_base1)*AV_TIME_BASE);
                pDecodeState->pAVPacket.dts=pDecodeState->pAVPacket.pts;
                pDecodeState->pAVPacket.duration=(double)calc_duration/(double)(av_q2d(time_base1)*AV_TIME_BASE);
            }

            //Convert PTS/DTS
            pDecodeState->pAVPacket.pts = av_rescale_q_rnd(pDecodeState->pAVPacket.pts, pDecodeState->inVideoStream->time_base, pDecodeState->outVideoStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
            pDecodeState->pAVPacket.dts = av_rescale_q_rnd(pDecodeState->pAVPacket.dts, pDecodeState->inVideoStream->time_base, pDecodeState->outVideoStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
            pDecodeState->pAVPacket.duration = av_rescale_q(pDecodeState->pAVPacket.duration, pDecodeState->inVideoStream->time_base, pDecodeState->outVideoStream->time_base);

            pDecodeState->pAVPacket.pos = -1;
            pDecodeState->pAVPacket.flags |= AV_PKT_FLAG_KEY;
            pDecodeState->pAVPacket.stream_index = 0;

            av_interleaved_write_frame(pDecodeState->outFormatContext, &pDecodeState->pAVPacket);
        }
        av_free_packet(&pDecodeState->pAVPacket);
    }
    av_write_trailer(pDecodeState->outFormatContext);

    avcodec_close(pDecodeState->outFormatContext->streams[0]->codec);
    av_freep(&pDecodeState->outFormatContext->streams[0]->codec);
    av_freep(&pDecodeState->outFormatContext->streams[0]);
    avio_close(pDecodeState->outFormatContext->pb);
    av_free(pDecodeState->outFormatContext);

    avformat_close_input(&pDecodeState->pFormatContext);
    free(pDecodeState->pFormatContext);
    pDecodeState->pFormatContext=NULL;

    emit sig(100);
    qDebug()<<"Finish!";
}
