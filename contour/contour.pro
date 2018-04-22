#-------------------------------------------------
#
# Project created by QtCreator 2018-03-05T15:30:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = contour
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    file.cpp \
    showimage.cpp \
    adaptivethreshold.cpp \
    adaptiveset.cpp \
    filter.cpp \
    threshold.cpp \
    boxfilter.cpp \
    boxfilterset.cpp \
    blur.cpp \
    blurset.cpp \
    gaussianblur.cpp \
    gaussianblurset.cpp \
    bilateralfilter.cpp \
    bilateralfilterset.cpp \
    morph.cpp \
    edge.cpp \
    contour.cpp \
    contourset.cpp \
    canny.cpp \
    cannyset.cpp \
    sobel.cpp \
    sobelset.cpp \
    multioperateset.cpp \
    multioperate.cpp \
    showimageui.cpp \
    transform.cpp \
    practical.cpp

HEADERS += \
        mainwindow.h \
    file.h \
    showimage.h \
    adaptivethreshold.h \
    adaptiveset.h \
    boxfilter.h \
    boxfilterset.h \
    blur.h \
    blurset.h \
    gaussianblur.h \
    gaussianblurset.h \
    bilateralfilter.h \
    bilateralfilterset.h \
    contour.h \
    contourset.h \
    canny.h \
    cannyset.h \
    sobel.h \
    sobelset.h \
    multioperateset.h

FORMS += \
        mainwindow.ui \
    adaptivethreshold.ui \
    boxfilter.ui \
    blur.ui \
    gaussianblur.ui \
    bilateralfilter.ui \
    contour.ui \
    canny.ui \
    sobel.ui

INCLUDEPATH += E:\Opencv\QTOpenCV\include \
               E:\Opencv\QTOpenCV\include/opencv \
               E:\Opencv\QTOpenCV\include/opencv2

LIBS += E:\Opencv\QTOpenCV\x64\mingw\lib/libopencv_*

RESOURCES += \
    projecticon.qrc

RC_FILE += icon.rc

DISTFILES += \
    icon.rc
