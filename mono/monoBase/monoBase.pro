#-------------------------------------------------
#
# Project created by QtCreator 2011-08-23T17:11:17
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = mono

TEMPLATE = lib

HEADERS += \
    mono.h

SOURCES += \
    mono.cpp

INCLUDEPATH += . ../../ ../../component/componentBase

LIBS += -lqcamotor \
        -L../../component/componentBase -lcomponent

headers.files = $$HEADERS
headers.path = $$INSTALLBASE/include/imbl
INSTALLS += headers

target.files = $$[TARGET]
target.path = $$INSTALLBASE/lib/imbl
INSTALLS += target

