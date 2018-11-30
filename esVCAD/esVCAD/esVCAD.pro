#-------------------------------------------------
#
# Project created by QtCreator 2018-11-30T16:30:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = esVCAD
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
    dxf_parser/dxf_creationclass.cpp \
    entities/arc.cpp \
    entities/block.cpp \
    entities/circle.cpp \
    entities/coordxy.cpp \
    entities/ellipse.cpp \
    entities/face3d.cpp \
    entities/layer.cpp \
    entities/line.cpp \
    entities/point.cpp \
    entities/polyline.cpp \
    entities/ray.cpp \
    entities/rect.cpp \
    entities/spline.cpp \
    entities/xline.cpp \
    graphicsframe.cpp

HEADERS += \
        mainwindow.h \
    dxf_parser/dxf_creationclass.h \
    entities/arc.h \
    entities/block.h \
    entities/circle.h \
    entities/coordxy.h \
    entities/ellipse.h \
    entities/entity.h \
    entities/face3d.h \
    entities/layer.h \
    entities/line.h \
    entities/mouseoperation.h \
    entities/point.h \
    entities/polyline.h \
    entities/ray.h \
    entities/rect.h \
    entities/spline.h \
    entities/xline.h \
    include/dxf/dl_attributes.h \
    include/dxf/dl_codes.h \
    include/dxf/dl_creationadapter.h \
    include/dxf/dl_creationinterface.h \
    include/dxf/dl_dxf.h \
    include/dxf/dl_entities.h \
    include/dxf/dl_exception.h \
    include/dxf/dl_extrusion.h \
    include/dxf/dl_global.h \
    include/dxf/dl_writer.h \
    include/dxf/dl_writer_ascii.h \
    include/tinyspline/tinysplinecpp.h \
    include/tinyspline/tinysplinelib_global.h \
    graphicsframe.h

FORMS += \
        mainwindow.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../3rd/dxf/MinGW_Win32/lib/release/ -ldxf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../3rd/dxf/MinGW_Win32/lib/debug/ -ldxf
else:unix: LIBS += -L$$PWD/../../3rd/dxf/MinGW_Win32/lib/ -ldxf

INCLUDEPATH += $$PWD/../../3rd/dxf/MinGW_Win32/lib/debug
DEPENDPATH += $$PWD/../../3rd/dxf/MinGW_Win32/lib/debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../3rd/tinyspline/MinGW_Win32/lib/release/ -ltinyspline
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../3rd/tinyspline/MinGW_Win32/lib/debug/ -ltinyspline
else:unix: LIBS += -L$$PWD/../../3rd/tinyspline/MinGW_Win32/lib/ -ltinyspline

INCLUDEPATH += $$PWD/../../3rd/tinyspline/MinGW_Win32/lib/debug
DEPENDPATH += $$PWD/../../3rd/tinyspline/MinGW_Win32/lib/debug
