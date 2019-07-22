#-------------------------------------------------
#
# Project created by QtCreator 2019-05-23T17:01:23
#
#-------------------------------------------------

QT       += core gui
QT +=script
QT +=sql
QT +=network

LIBS +=./lib-SmartHomeGateway-X86-V4.so
#LIBS +=./lib-SmartHomeGateway-ARM-V4.so

TARGET = QTPro_001H
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    qextserialport.cpp \
    qextserialport_unix.cpp \
    serialthread.cpp \
    dialog.cpp \
    guanli.cpp \
    resgister.cpp \
    mylog.cpp \
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
    resgister.h \
    mylog.h \
    mode1.h \
    mode2.h \
    mode3.h

FORMS    += login.ui \
    dialog.ui \
    guanli.ui \
    resgister.ui \
    mylog.ui

RESOURCES += \
    image/image.qrc
