TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

target.path = /home/jhb

include(deployment.pri)
qtcAddDeployment()

