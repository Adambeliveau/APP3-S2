TEMPLATE     = vcapp
TARGET       = APP3-S2_temp
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += MonInterface.h centralwidget.h leds.h switches.h visiTest.h vecteur.h CommunicationFPGA.h
SOURCES     += TestVisiTest.cpp MonInterface.cpp
INCLUDEPATH += ../APP3-S2_temp
LIBS	      +=../APP3-S2_temp/LiB/VisiTest.lib
LIBS        += ../APP3-S2_temp/LiB/CommunicationFPGA.lib
QT += widgets
