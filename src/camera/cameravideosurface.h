#ifndef CAMERAVIDEOSURFACE_H
#define CAMERAVIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QDebug>
#include "sqldata.h"

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
#include <libavutil/imgutils.h>
//音频采样数据格式库
#include <libswresample/swresample.h>
}

class CameraVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    CameraVideoSurface(QObject *parent = NULL);
    ~CameraVideoSurface();
    void setCameraResolution(const QSize &size);
    void escEvent();
    void InitEncoder();
protected:
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
    QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const override;
    bool present(const QVideoFrame &frame) override;
private slots:
    void cameraStopSlot();
signals:
    void showFrame(QImage image);
private:    
    void Encode(AVFrame *frame);    
    SqlData *pSqlData;
    int FirstImg;
private:
    AVFormatContext *pOutputFormatCtx;
    AVCodecContext *pCodecCtx;
    AVCodec *pCodec;
    AVStream *pOutputStream;
    AVPacket *packet;
    AVFrame *yuvFrame;
    QString FileName;
    QString OutPutFileName;
    struct SwsContext *image_convert_ctx;   
};

#endif // CAMERAVIDEOSURFACE_H
