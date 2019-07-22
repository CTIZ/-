#-------------------------------------------------
#
# Project created by QtCreator 2019-05-25T05:18:04
#
#-------------------------------------------------

QT       += core gui
QT +=sql
QT +=script
QT +=network

LIBS +=./lib-SmartHomeGateway-X86-V4.so
#LIBS +=./lib-SmartHomeGateway-ARM-V4.so

TARGET = QTPro_003B
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    qextserialport.cpp \
    qextserialport_unix.cpp \
    serialthread.cpp \
    updatepwd.cpp \
    dialog.cpp \
    welcome.cpp \
    rfid.cpp \
    draw.cpp \
    clean.cpp \
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
    updatepwd.h \
    dialog.h \
    welcome.h \
    rfid.h \
    draw.h \
    clean.h \
    mode1.h \
    mode2.h \
    mode3.h

FORMS    += login.ui \
    updatepwd.ui \
    dialog.ui \
    welcome.ui \
    rfid.ui \
    draw.ui \
    clean.ui

RESOURCES += \
    image/image.qrc
