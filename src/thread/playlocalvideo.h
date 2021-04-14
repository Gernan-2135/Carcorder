#ifndef PLAYLOCALVIDEO_H
#define PLAYLOCALVIDEO_H

#include "QThread"
#include <QDebug>
#include <QImage>
#include <QMutex>

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
//音频采样数据格式库
#include "libswresample/swresample.h"
}

struct PlayState
{
    AVFormatContext *pFormatContext;    //文件封装格式
    AVCodecContext *pAVCodecContext;    //文件上下文
    AVCodec *pAVCodec;  //解码器
    //读取帧数据换成到哪里->缓存到packet里面
    AVPacket* pAVPacket;    //解码初始数据包
    //输入->环境一帧数据->缓冲区->类似于一张图
    AVFrame* pAVFrameIn;  //解码出来的视频流/音频流
    //输出->帧数据->视频像素数据格式->RGB
    AVFrame* pAVFrameOutRGB;
    SwsContext *pSwsContext;  //解压成的音频格式
    FILE* out_file_yuv; //打开文件
    uint8_t *out_buffer;
    int av_stream_index;
};

class PlayLocalVideo : public QThread
{
    Q_OBJECT
public:
    PlayLocalVideo();
    bool CreatePlayState(QString url);
    void stop();    //字体正的 自定义函数
    int downSpeed();
    int upSpeed();

protected:
    void run();     //字体斜的 系统的虚函数    重写

signals:
    void sigGetOneFrame(QImage);

private:
    QMutex m_lock;
    int ret;
    bool m_stop;
    PlayState *pPlayState;
    QImage m_image;
    QString cinfilepath;    //解码的文件
    int mask = 1;
    int speed;
    int down;
    int up;

private slots:
    void psSlot();  //暂停、继续
};

#endif // PLAYLOCALVIDEO_H
