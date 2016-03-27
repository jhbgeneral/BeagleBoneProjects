TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    i2cdevice.cpp

target.path = /home/jhb

INSTALLS += target

HEADERS += \
    i2cdevice.h
