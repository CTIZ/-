#-------------------------------------------------
#
# Project created by QtCreator 2019-06-09T17:21:20
#
#-------------------------------------------------

QT       += core gui
QT +=script
QT +=sql
QT +=network

LIBS +=./lib-SmartHomeGateway-X86-V4.so
#LIBS +=./lib-SmartHomeGateway-ARM-V4.so

TARGET = QTPro_004G
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    qextserialport_unix.cpp \
    qextserialport.cpp \
    serialthread.cpp \
    resgister.cpp \
    guanli.cpp \
    dialog.cpp \
    ld_guanli.cpp \
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
    guanli.h \
    dialog.h \
    ld_guanli.h \
    mode.h

FORMS    += login.ui \
    resgister.ui \
    guanli.ui \
    dialog.ui \
    ld_guanli.ui

RESOURCES += \
    image/image.qrc
