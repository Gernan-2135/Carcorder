#include "openglwidget.h"
#include <QPainter>

OpenGLWidget::OpenGLWidget(QWidget *parent)
{

}

void OpenGLWidget::paintGL()
{
    QPainter painter(this);
    if (m_CameraFrame.size().width() <= 0)
    {
        return;
    }
    QImage _image = m_CameraFrame.scaled(this->size());
    painter.drawImage(0, 0, _image);
}

void OpenGLWidget::showCameraFrameSlot(QImage image)
{
    m_CameraFrame = image;
    this->update();
}
