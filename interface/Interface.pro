QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 sdk_no_version_check
TEMPLATE = app
TARGET = Orion

ICON = icon.icns

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    centralwidget.cpp \
    displaywidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    centralwidget.h \
    displaywidget.h \
    mainwindow.h

FORMS += \
    about.ui \
    mainwindow.ui

LIBEMULATORNAME   = libemulator
LIBEMULATORDIR    = $$PWD/../emulator
ROMDIR            = $$PWD/../rom

unix:LIBEMULATOR  = $$LIBEMULATORDIR/$$LIBEMULATORNAME.so
macos:LIBEMULATOR = $$LIBEMULATORDIR/$$LIBEMULATORNAME.dylib

macos
{
    !exists( $$LIBEMULATORDIR/libemulator.dylib ) {
        system( cd $$LIBEMULATORDIR && make )
    }

    RES.files = $$ROMDIR
    RES.path  = Contents/Resources

    FRW.files = $$LIBEMULATORDIR/libemulator.dylib
    FRW.path  = Contents/Frameworks

    LOC.files = locversion.plist InfoPlist.strings
    LOC.path  = COntents/Resources/ru.lproj

    QMAKE_BUNDLE_DATA += RES FRW LOC
}

LIBS += -L$$LIBEMULATORDIR -lemulator

unix:INCLUDEPATH += $$system(find $$LIBEMULATORDIR -type d -print)
unix:DEPENDPATH  += $$system(find $$LIBEMULATORDIR -type d -print)

TRANSLATIONS += $$PWD/translation/language_ru.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    interface.qrc
