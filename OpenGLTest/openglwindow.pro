include(openglwindow.pri)

SOURCES += \
    main.cpp \
    ctLoger.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/gui/openglwindow
INSTALLS += target

QT += opengl

HEADERS += \
    ctLoger.h
