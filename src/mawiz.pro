#-------------------------------------------------
#
# Project created by QtCreator 2012-11-21T10:34:00
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = mawiz
TEMPLATE = lib

DEFINES += MAWIZ_LIBRARY

SOURCES += \
    mawiz.cpp \
    movebar.cpp \
    mawizpage.cpp

HEADERS += \
    mawiz.h \
    mawiz_p.h \
    movebar.h \
    mawizpage.h

FORMS += \
    mawiz.ui

RESOURCES += \
    mawiz_resources.qrc


target.path = /usr/lib

includefiles.path = /usr/include/MaWiz
includefiles.files = mawiz.h mawizpage.h

INSTALLS += target includefiles
