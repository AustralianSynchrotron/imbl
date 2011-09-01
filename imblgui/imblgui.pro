#-------------------------------------------------
#
# Project created by QtCreator 2011-07-29T11:17:06
#
#-------------------------------------------------

CONFIG += qwt
QT       += core gui

TARGET = imblgui
TEMPLATE = app


SOURCES += main.cpp\
        imblgui.cpp \
    beamlineview.cpp

HEADERS  += imblgui.h \
    beamlineview.h

FORMS    += imblgui.ui

QMAKE_LFLAGS += -Wl,-rpath,\'\$$ORIGIN/../lib/imbl\'

INCLUDEPATH += ../ \
               ../shutterFE/shutterFEgui \
               ../shutterFE/shutterFEbase \
               ../hhlSlits/hhlSlitsBase \
               ../hhlSlits/hhlSlitsGui \
               ../filters/filtersBase \
               ../filters/filtersGui \
               ../shutter1A/shutter1Agui \
               ../shutter1A/shutter1Abase \
               ../mrtShutter/mrtShutterGui \
               ../mrtShutter/mrtShutterBase \
               ../DEImono/DEImonoGui \
               ../DEImono/DEImonoBase \
               ../component/componentBase \
               ../component/componentGui


LIBS += \
        -lmotorstack \
        -L../shutterFE/shutterFEbase -lshutterFE \
        -L../shutterFE/shutterFEgui -lshutterFEgui \
        -L../filters/filtersBase -lfilters \
        -L../filters/filtersGui -lfiltersGui \
        -L../hhlSlits/hhlSlitsBase -lhhlSlits \
        -L../hhlSlits/hhlSlitsGui -lhhlSlitsGui \
        -L../shutter1A/shutter1Abase -lshutter1A \
        -L../shutter1A/shutter1Agui -lshutter1Agui \
        -L../mrtShutter/mrtShutterBase -lmrtShutter \
        -L../mrtShutter/mrtShutterGui -lmrtShutterGui \
        -L../DEImono/DEImonoBase -lDEImono \
        -L../DEImono/DEImonoGui -lDEImonoGui \
        -L../component/componentBase -lcomponent \
        -L../component/componentGui -lcomponentGui


RESOURCES += \
    data.qrc

target.files = $$[TARGET]
target.path = $$INSTALLBASE/bin
INSTALLS += target

