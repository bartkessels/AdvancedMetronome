QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

TARGET = AdvancedMetronome
TEMPLATE = app

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/metronome.cpp \
        src/measure.cpp

HEADERS += \
        src/mainwindow.h \
        src/metronome.h \
        src/measure.h

FORMS += \
        src/ui/mainwindow.ui \
        src/ui/measure.ui

RESOURCES += \
        resources.qrc
