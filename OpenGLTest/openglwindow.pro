include(openglwindow.pri)

SOURCES += \
    main.cpp \
    ctLoger.cpp

TARGET = dreamgymf2p

target.path = $$[QT_INSTALL_EXAMPLES]/gui/openglwindow
INSTALLS += target

QT += opengl
QT += core

HEADERS += \
    ctLoger.h
#CONFIG += c++11
#QMAKE_CXXFLAGS += -std=c++11
