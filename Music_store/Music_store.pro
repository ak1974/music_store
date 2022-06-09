QT       += core gui sql widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    sqlstandartitemmodel.cpp \
    sqlworker.cpp

HEADERS += \
    cdebug.h \
    mainwindow.h \
    sqlhelper.h \
    sqlstandartitemmodel.h \
    sqlworker.h

FORMS += \
    mainwindow.ui

