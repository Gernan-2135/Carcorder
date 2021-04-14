#-------------------------------------------------
#
# Project created by QtCreator 2020-06-03T12:48:34
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Carcorder
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(src/camera/camera.pri)
include(src/main/main.pri)
include(src/carton/carton.pri)
include(src/data/data.pri)
include(src/decode/decode.pri)
include(src/thread/thread.pri)
include(src/widget/widget.pri)

INCLUDEPATH += $$PWD/src/camera
INCLUDEPATH += $$PWD/src/main
INCLUDEPATH += $$PWD/src/carton
INCLUDEPATH += $$PWD/src/data
INCLUDEPATH += $$PWD/src/decode
INCLUDEPATH += $$PWD/src/thread
INCLUDEPATH += $$PWD/src/widget


INCLUDEPATH += $$PWD/ffmpeg/include \

LIBS    += $$PWD/ffmpeg/lib/avcodec.lib \
            $$PWD/ffmpeg/lib/avdevice.lib \
            $$PWD/ffmpeg/lib/avfilter.lib \
            $$PWD/ffmpeg/lib/avformat.lib \
            $$PWD/ffmpeg/lib/avutil.lib \
            $$PWD/ffmpeg/lib/postproc.lib \
            $$PWD/ffmpeg/lib/swresample.lib \
            $$PWD/ffmpeg/lib/swscale.lib \

MOC_DIR = temp/moc
RCC_DIR = temp/rccr
OBJECTS_DIR = temp/obj
UI_HEADERS_DIR = temp/ui
DESTDIR = $$PWD/bin
