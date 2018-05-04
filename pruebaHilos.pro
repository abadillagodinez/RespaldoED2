#-------------------------------------------------
#
# Project created by QtCreator 2018-04-28T12:04:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pruebaHilos
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainwindowlogic.cpp \
    prueba.cpp

HEADERS  += mainwindow.h \
    mainwindowlogic.h \
    prueba.h \
    RespaldoED2/estudiante.h \
    stringParser.h \
    ArbolBEstudiantes.h \
    arbolbprofesores.h \
    arbolbbcarreras.h \
    arbolavlcursos.h \
    listademesas.h \
    nodeavl.h \
    nododebst.h

FORMS    += mainwindow.ui
