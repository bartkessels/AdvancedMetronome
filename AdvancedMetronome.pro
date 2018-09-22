QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

TARGET = advancedmetronome
TEMPLATE = app

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build

include($$PWD/updateqm.pri)

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

TRANSLATIONS = \
        translations/advancedmetronome_nl.ts

RESOURCES += resources.qrc

macx {
    ICON = resources/mac/net.bartkessels.advancedmetronome.icns
} else:win32 {
    RC_FILE = resources/windows/net.bartkessels.advancedmetronome.rc
} else:unix {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }

    isEmpty(BINDIR) {
        BINDIR = $$PREFIX/bin
    }

    isEmpty(DATADIR) {
        DATADIR = $$PREFIX/share
    }

    target.path = $$BINDIR

    icon.files = resources/linux/icons/*
    icon.path = $$DATADIR/icons/hicolor

    desktop.files = resources/linux/net.bartkessels.advancedmetronome.desktop
    desktop.path = $$DATADIR/applications/

    appdata.files = resources/linux/net.bartkessels.advancedmetronome.appdata.xml
    appdata.path = $$DATADIR/appdata/

    qm.files = TRANSLATIONS
    qm.path = $$DATADIR/net.bartkessels.advancedmetronome/translations

    INSTALLS += \
        target \
        icon \
        desktop \
        appdata \
        qm
}
