QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 sdk_no_version_check
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
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

macos {

    ROM.files = $$PWD/../rom
    ROM.path  = Contents/Resources

    LIB.files = $$PWD/../libemulator.dylib
    LIB.path = Contents/Frameworks

    QMAKE_BUNDLE_DATA += ROM LIB
}

LIBS += -L$$PWD/../ -lemulator

unix:INCLUDEPATH += $$system(find ../emulator -type d -print)
unix:DEPENDPATH  += $$system(find ../emulator -type d -print)
