
QT += core
QT -= gui

CONFIG += c++15

TARGET = LFA
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    MenuAFD.cpp \
    MenuAFND.cpp \
    MenuAF_Epson.cpp

HEADERS += \
    Estado.h \
    Aresta.h \
    ArestaEstado.h \
    AFD.h \
    AFND.h \
    MenuAFND.h \
    MenuAF_Epson.h \
    AF_Epson.h

DISTFILES +=


