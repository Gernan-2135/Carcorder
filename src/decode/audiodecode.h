#ifndef AUDIODECODE_H
#define AUDIODECODE_H

#include <QThread>

extern "C"
{
//avcodec:编解码(最重要的库)
#include <libavcodec/avcodec.h>
//avformat:封装格式处理
#include <libavformat/avformat.h>
//swscale:视频像素数据格式转换
#include <libswscale/swscale.h>
//avdevice:各种设备的输入输出
#include <libavdevice/avdevice.h>
//avutil:工具库（大部分库都需要这个库的支持）
#include <libavutil/avutil.h>
//音频采样数据格式库
#include <libswresample/swresample.h>
}

class AudioDecode : public QThread
{
public:
    AudioDecode();
};

#endif // AUDIODECODE_H
