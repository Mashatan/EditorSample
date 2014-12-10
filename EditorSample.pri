## Author: Ali Mashatan
## Email : ali.mashatan@gmail.com

TEMPLATE = app
TARGET = EditorSample
QMAKE_PROJECT_NAME = EditorSample
DESTDIR = bin

ARCHITECTURE = x86-64
QT_CONFIG += x64 

QT += widgets
QT += declarative
QT += quick

CONFIG += qt
CONFIG += warn_on
CONFIG += console
CONFIG += thread 

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x000000

QMAKE_CXXFLAGS_DEBUG   += -openmp -Zi -Od -MP8
QMAKE_LFLAGS_DEBUG += /DEBUG
#QMAKE_CXXFLAGS += -std=c++11 

CONFIG(debug, debug|release) {
    win32: TARGET = $$join(TARGET,,,_d)
}

QMAKE_LIBDIR += 
LIBS += 

Release:OBJECTS_DIR = build/release/.obj
Release:MOC_DIR     = build/release/.moc
Release:RCC_DIR     = build/release/.rcc
Release:UI_DIR      = build/release/.ui
Release:INCLUDEPATH += build/release/.ui

Debug:OBJECTS_DIR = build/debug/.obj
Debug:MOC_DIR     = build/debug/.moc
Debug:RCC_DIR     = build/debug/.rcc
Debug:UI_DIR      = build/debug/.ui
Debug:INCLUDEPATH += build/debug/.ui

INCLUDEPATH += .
INCLUDEPATH += inc/


SOURCES += src/main.cpp
SOURCES += src/editor.cpp

HEADERS += inc/editor.h

RESOURCES += Resource.qrc

