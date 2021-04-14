#ifndef VIDEODECODE_H
#define VIDEODECODE_H

#include <QThread>
#include <QDebug>

extern "C"
{
//编码库
#include "libavcodec/avcodec.h"
//各种设备的输入输出
#include "libavdevice/avdevice.h"
//封装格式
#include "libavformat/avformat.h"
//滤镜
#include "libavfilter/avfilter.h"
//视频像素数据格式化
#include "libswscale/swscale.h"
}

struct DecodeState
{
    AVFormatContext *pFormatContext;    //文件封装格式
    //读取帧数据换成到哪里->缓存到packet里面
    AVPacket pAVPacket;    //解码初始数据包
    AVFormatContext *outFormatContext;
    AVStream *outVideoStream;
    AVStream *inVideoStream;
    int startFlag;
    int frameCount;
    int videoStreamIndex;
};

class VideoDecode : public QThread
{
    Q_OBJECT

public:
    VideoDecode();
    void run();     //字体斜的 系统的虚函数 重写
    bool CreateVideoDecode(QString url);
    void setFileName(QString filename);
    bool checkFileData();   //查看文件大小 是否为空文件 0KB
    ~VideoDecode();

signals:
    void sig(int value);

private:
    DecodeState *pDecodeState;
    uint64_t fileLen;
    QString inFileName;     //解码的文件
    QString outFileName;    //存入的文件
    int ret;
};

#endif // VIDEODECODE_H
