#-------------------------------------------------
#
# Project created by QtCreator 2019-05-17T06:29:27
#
#-------------------------------------------------

QT       += core gui
QT +=sql
QT +=script
QT +=network

LIBS +=./lib-SmartHomeGateway-X86-V4.so
#LIBS +=./lib-SmartHomeGateway-ARM-V4.so


TARGET = QTPro_001C
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    qextserialport_unix.cpp \
    qextserialport.cpp \
    serialthread.cpp \
    dialog.cpp \
    resgister.cpp \
    guanli.cpp \
    mylog.cpp \
    mode1.cpp \
    mode2.cpp \
    mode3.cpp \
    mode4.cpp

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
    resgister.h \
    guanli.h \
    mylog.h \
    mode1.h \
    mode2.h \
    mode3.h \
    mode4.h

FORMS    += login.ui \
    dialog.ui \
    resgister.ui \
    guanli.ui \
    mylog.ui

RESOURCES += \
    image/image.qrc
