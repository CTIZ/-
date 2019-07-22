#-------------------------------------------------
#
# Project created by QtCreator 2019-04-11T20:50:44
#
#-------------------------------------------------

QT       += core gui
QT +=sql
QT +=script
QT +=network

LIBS +=./lib-SmartHomeGateway-X86-V4.so
#LIBS +=./lib-SmartHomeGateway-ARM-V4.so

TARGET = QTPro_001
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    qextserialport_unix.cpp \
    qextserialport.cpp \
    serialthread.cpp \
    dialog.cpp \
    resgister.cpp \
    mode.cpp \
    draw.cpp

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
    mode.h \
    draw.h

FORMS    += login.ui \
    dialog.ui \
    resgister.ui \
    draw.ui

RESOURCES += \
    image/image.qrc
