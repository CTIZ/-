#-------------------------------------------------
#
# Project created by QtCreator 2019-05-24T16:25:44
#
#-------------------------------------------------

QT       += core gui
QT +=sql
QT +=script
QT +=network

LIBS +=./lib-SmartHomeGateway-X86-V4.so
#LIBS +=./lib-SmartHomeGateway-ARM-V4.so

TARGET = QTPro_003A
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    qextserialport.cpp \
    qextserialport_unix.cpp \
    serialthread.cpp \
    dialog.cpp \
    resgister.cpp \
    mode1.cpp \
    mode2.cpp \
    mode3.cpp \
    mode4.cpp \
    draw.cpp \
    mode5.cpp

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
    resgister.h \
    mode1.h \
    mode2.h \
    mode3.h \
    mode4.h \
    draw.h \
    mode5.h

FORMS    += login.ui \
    dialog.ui \
    resgister.ui \
    draw.ui

RESOURCES += \
    image/image.qrc
