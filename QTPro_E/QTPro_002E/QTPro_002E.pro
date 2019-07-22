#-------------------------------------------------
#
# Project created by QtCreator 2019-05-18T12:43:46
#
#-------------------------------------------------

QT       += core gui
QT +=sql
QT +=script
QT +=network

LIBS +=./lib-SmartHomeGateway-X86-V4.so
#LIBS +=./lib-SmartHomeGateway-ARM-V4.so


TARGET = QTPro_002E
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    qextserialport.cpp \
    qextserialport_unix.cpp \
    serialthread.cpp \
    dialog.cpp \
    guanli.cpp \
    draw.cpp \
    mode1.cpp \
    mode2.cpp \
    mode3.cpp

HEADERS  += login.h \
    cjson.h \
    jsonreceivehandle.h \
    jsonsendhandle.h \
    qextserialport.h \
    qextserialport_global.h \
    qextserialport_p.h \
    serialdatahandle.h \
    serialportreceive.h \
    sql.h \
    systemConfig.h \
    tcpclientthread.h \
    tcpserver.h \
    VariableDefinition.h \
    serialthread.h \
    dialog.h \
    guanli.h \
    draw.h \
    mode1.h \
    mode2.h \
    mode3.h

FORMS    += login.ui \
    dialog.ui \
    guanli.ui \
    draw.ui

RESOURCES += \
    image/image.qrc
