#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QImage>

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);
    QImage m_CameraFrame;

protected:
    void paintGL() override;

signals:

public slots:
    void showCameraFrameSlot(QImage image);
};

#endif // OPENGLWIDGET_H
