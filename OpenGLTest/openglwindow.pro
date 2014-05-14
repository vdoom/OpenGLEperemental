include(openglwindow.pri)

SOURCES += \
    main.cpp \
    ctLoger.cpp

TARGET = HardHanoi



target.path = $$[QT_INSTALL_EXAMPLES]/gui/openglwindow
INSTALLS += target

targ.files = assets/muse.mp3
targ.path = /assets
    # android platform
    # From: http://community.kde.org/Necessitas/Assets
    //SAMPLES_INSTALL_PATH=/assets


# - setup the 'make install' step
#samples.path = $$SAMPLES_INSTALL_PATH
#samples.files += $$SAMPLE_FILES
#samples.depends += FORCE

INSTALLS += targ
QT += opengl
QT += core
QT += multimedia

HEADERS += \
    ctLoger.h
#CONFIG += c++11
#QMAKE_CXXFLAGS += -std=c++11


OTHER_FILES += \
    android/AndroidManifest.xml \
    android/res/layout/splash.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-et/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
    android/version.xml \
    assets/Samples/muse.mp3 \
    android/assets/Samples/muse.mp3

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
