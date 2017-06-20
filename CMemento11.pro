#-------------------------------------------------
#
# Project created by QtCreator 2017-06-18T17:39:20
#
#-------------------------------------------------

QT       += core gui qml quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CMemento11
TEMPLATE = app


SOURCES += main.cpp\
        ui/cmementomainwindow.cpp \
    model/cundoableinventory.cpp \
    model/listables/ccdrom.cpp \
    utilities/cutility.cpp \
    model/listables/cbook.cpp \
    model/listables/cdvd.cpp \
    model/cundoableinventorymanager.cpp \
    model/clistablefactory.cpp \
    model/cinventorymodel.cpp

HEADERS  += ui/cmementomainwindow.h \
    model/cundoableinventory.h \
    model/clistable.h \
    model/listables/ccdrom.h \
    utilities/cutility.h \
    model/listables/cbook.h \
    model/listables/cdvd.h \
    model/cundoableinventorymanager.h \
    model/clistablefactory.h \
    model/cinventorymodel.h

FORMS    += ui/cmementomainwindow.ui

DISTFILES += \
    qml/inventoryView.qml

RESOURCES += \
    inventoryresources.qrc
