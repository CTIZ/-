#-------------------------------------------------
#
# Project created by QtCreator 2019-06-08T22:40:30
#
#-------------------------------------------------

QT       += core gui
QT +=sql
QT +=script
QT +=network

LIBS +=./lib-SmartHomeGateway-X86-V4.so
#LIBS +=./lib-SmartHomeGateway-ARM-V4.so

TARGET = QTPro_005F
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    qextserialport_unix.cpp \
    qextserialport.cpp \
    serialthread.cpp \
    dialog.cpp \
    guanli.cpp \
    draw.cpp \
    mode1.cpp \
    mode2.cpp \
    mode3.cpp \
    mode4.cpp \
    mode5.cpp

HEADERS  += login.h \
    VariableDefinition.h \
    tcpserver.h \
    tcpclientthread.h \
    systemConfig.h \
    sql.h \
    serialportreceive.h \
    serialdatahandle.h \
    qextserialport_p.h \
    qextserialport_global.h \
    qextserialport.h \
    jsonsendhandle.h \
    jsonreceivehandle.h \
    cjson.h \
    serialthread.h \
    dialog.h \
    guanli.h \
    draw.h \
    mode1.h \
    mode2.h \
    mode3.h \
    mode4.h \
    mode5.h

FORMS    += login.ui \
    dialog.ui \
    guanli.ui \
    draw.ui

RESOURCES += \
    image/image.qrc
