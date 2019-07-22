#-------------------------------------------------
#
# Project created by QtCreator 2019-06-07T22:55:19
#
#-------------------------------------------------

QT       += core gui
QT +=network
QT +=sql
QT +=script

LIBS +=./lib-SmartHomeGateway-X86-V4.so
#LIBS +=./lib-SmartHomeGateway-ARM-V4.so

TARGET = QTPro_005
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    qextserialport_unix.cpp \
    qextserialport.cpp \
    serialthread.cpp \
    resgister.cpp \
    dialog.cpp \
    mylog3.cpp \
    mode.cpp

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
    resgister.h \
    dialog.h \
    mylog3.h \
    mode.h

FORMS    += login.ui \
    resgister.ui \
    dialog.ui \
    mylog3.ui

RESOURCES += \
    image/image.qrc
