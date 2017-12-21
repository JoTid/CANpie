#=============================================================================#
# File:          qcan_usart.pro                                               #
# Description:   qmake project file for CANpie to USART plugin                #
#                                                                             #
# Copyright (C) MicroControl GmbH & Co. KG                                    #
# 53844 Troisdorf - Germany                                                   #
# www.microcontrol.net                                                        #
#                                                                             #
#=============================================================================#


#---------------------------------------------------------------
# Name of QMake project
#
QMAKE_PROJECT_NAME = "QCan USART"

#---------------------------------------------------------------
# compile plugin only if necessary header file exists
#
#macx {
#   DRIVER_API = ./include/PCBUSB.h
#}
#win32 {
#   DRIVER_API = ./include/PCANBasic.h
#}
#exists($$DRIVER_API) {

#---------------------------------------------------------------
# template type
#
TEMPLATE = lib

#---------------------------------------------------------------
# Qt modules used
#
QT      += widgets serialport

#---------------------------------------------------------------
# target file name
#
TARGET          = $$qtLibraryTarget(QCanUsart)

#---------------------------------------------------------------
# directory for target file
#
macx {
   DESTDIR = ../../../../../bin/CANpieServer.app/Contents/Plugins
}
win32 {
   DESTDIR = ../../../../../bin/plugins
}
#---------------------------------------------------------------
# Objects directory
#
OBJECTS_DIR = ./objs/

#---------------------------------------------------------------
# project configuration and compiler options
#
CONFIG += release
CONFIG += plugin
CONFIG += warn_on
CONFIG += C++11
CONFIG += silent

#---------------------------------------------------------------
# version of the plugin
#
VERSION = 0.82.1

#---------------------------------------------------------------
# definitions for preprocessor
#
DEFINES  = MC_USART_PORT_MAX=CP_CHANNEL_MAX

#---------------------------------------------------------------
# UI files
#
FORMS   =

#---------------------------------------------------------------
# resource collection files
#
RESOURCES = qcan_usart.qrc

#---------------------------------------------------------------
# include directory search path
#
INCLUDEPATH  = .
INCLUDEPATH += ./include
INCLUDEPATH += ./include/canpie-fd
INCLUDEPATH += ./include/hal
INCLUDEPATH += ./include/misc
INCLUDEPATH += ./../../..


#---------------------------------------------------------------
# search path for source files
#
VPATH  = .
VPATH += ./../../..
VPATH += ./include/canpie-fd


#---------------------------------------------------------------
# header files of project
#
HEADERS =   qcan_interface.hpp      \
            qcan_interface_usart.hpp \
            qcan_usart.hpp     \
            qcan_plugin.hpp         \
            qcan_plugin_usart.hpp


#---------------------------------------------------------------
# source files of project
#
SOURCES =   qcan_data.cpp           \
            qcan_frame.cpp          \
            qcan_frame_api.cpp      \
            qcan_frame_error.cpp    \
            qcan_timestamp.cpp      \
            qcan_interface_usart.cpp \
            qcan_usart.cpp     \
            qcan_plugin_usart.cpp


SOURCES += cp_fifo.c    \
           cp_msg.c     \
           cp_usart.c

EXAMPLE_FILES = plugin.json

#---------------------------------------------------------------
# OS specific settings
#
macx {
   message("Building '$$QMAKE_PROJECT_NAME' for Mac OS X ...")
   QMAKE_MAC_SDK = macosx10.12
   QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9
}

win32 {
   CONFIG(debug, debug|release) {
      message("Building '$$QMAKE_PROJECT_NAME' DEBUG version for Windows ...")
   } else {
      message("Building '$$QMAKE_PROJECT_NAME' RELEASE version for Windows ...")
#      DEFINES += QT_NO_WARNING_OUTPUT
#      DEFINES += QT_NO_DEBUG_OUTPUT
#      DEFINES += QT_NO_INFO_OUTPUT
   }
}

#---------------------------------------------------------------
# necessary header file does not exist!
#
#} else {
#   message(" ");
#   message(" '$$QMAKE_PROJECT_NAME' ommited from build, because PCAN-Basic API is not available!");
#   message(" Make sure './include' contains PCAN-Basic API.");
#   message(" Copy or link content of 'PCAN-Basic API/Include' to the './include' folder.");
#   message(" PCAN-Basic API can be downloaded from http://www.peak-system.com/");
#   message(" ");
#}

