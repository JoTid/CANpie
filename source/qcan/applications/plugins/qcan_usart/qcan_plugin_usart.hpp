//============================================================================//
// File:          qcan_plugin_peak.hpp                                        //
// Description:   CAN plugin for PEAK devices                                 //
//                                                                            //
// Copyright (C) MicroControl GmbH & Co. KG                                   //
// 53842 Troisdorf - Germany                                                  //
// www.microcontrol.net                                                       //
//                                                                            //
//----------------------------------------------------------------------------//
// Redistribution and use in source and binary forms, with or without         //
// modification, are permitted provided that the following conditions         //
// are met:                                                                   //
// 1. Redistributions of source code must retain the above copyright          //
//    notice, this list of conditions, the following disclaimer and           //
//    the referenced file 'COPYING'.                                          //
// 2. Redistributions in binary form must reproduce the above copyright       //
//    notice, this list of conditions and the following disclaimer in the     //
//    documentation and/or other materials provided with the distribution.    //
// 3. Neither the name of MicroControl nor the names of its contributors      //
//    may be used to endorse or promote products derived from this software   //
//    without specific prior written permission.                              //
//                                                                            //
// Provided that this notice is retained in full, this software may be        //
// distributed under the terms of the GNU Lesser General Public License       //
// ("LGPL") version 3 as distributed in the 'COPYING' file.                   //
//                                                                            //
//============================================================================//

#ifndef QCAN_PLUGIN_USART_H_
#define QCAN_PLUGIN_USART_H_

#include <QObject>
#include <QtPlugin>
#include <QLibrary>
#include <QCanPlugin>
#include <QtWidgets>

#include "qcan_usart.hpp"
#include "qcan_interface_usart.hpp"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

//----------------------------------------------------------------------------//
// QCanPeakUsb                                                                //
//                                                                            //
//----------------------------------------------------------------------------//
class QCanPluginUsart : public QCanPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QCanPlugin_iid FILE "plugin.json")
    Q_INTERFACES(QCanPlugin)

private:

   QSerialPort    *pclSerialPortP;

   /*!
    * \brief auwPCanChannelP
    * Contains all PCAN Channels that should be handled
    * by this plugin.
    */
   QList<uint16_t> auwPCanChannelP;

   /*!
    * \brief Paramter to indentify an interface
    */
   typedef struct {
      uint16_t uwPCanChannel;
      QCanInterfaceUsart * pclQCanInterfaceUsart;
   } QCanIf_ts;

   /*!
    * \brief atsQCanIfUsartP
    * Contains list of available QCAN Interfaces
    */
   QList<QCanIf_ts> atsQCanIfUsartP;

   /*!
    * \brief pclCpUsartP
    * Reference to the static USART lib
    */
   QCanUsart &pclCpUsartP = QCanUsart::getInstance();

public:
   QCanPluginUsart();
   ~QCanPluginUsart();

   QIcon           icon(void) Q_DECL_OVERRIDE;
   uint8_t         interfaceCount(void) Q_DECL_OVERRIDE;
   QCanInterface * getInterface(uint8_t ubInterfaceV) Q_DECL_OVERRIDE;
   QString         name(void) Q_DECL_OVERRIDE;
};

#endif /*QCAN_PLUGIN_USART_H_*/

