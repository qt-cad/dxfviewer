#-------------------------------------------------
#
# Project created by QtCreator 2018-11-28T15:37:10
#
#-------------------------------------------------

QT       -= gui

TARGET = dxf
TEMPLATE = lib

DEFINES += DXFLIB_LIBRARY

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
    src/dl_dxf.cpp \
    src/dl_writer_ascii.cpp

HEADERS += \
    src/dl_attributes.h \
    src/dl_codes.h \
    src/dl_creationadapter.h \
    src/dl_creationinterface.h \
    src/dl_dxf.h \
    src/dl_entities.h \
    src/dl_exception.h \
    src/dl_extrusion.h \
    src/dl_global.h \
    src/dl_writer.h \
    src/dl_writer_ascii.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
