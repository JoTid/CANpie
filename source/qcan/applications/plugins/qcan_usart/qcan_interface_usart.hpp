//============================================================================//
// File:          qcan_interface_usart.hpp                                    //
// Description:   CAN plugin for USART device                                 //
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

#ifndef QCAN_INTERFACE_USART_H_
#define QCAN_INTERFACE_USART_H_

#include <QObject>
#include <QtPlugin>
#include <QLibrary>
#include <QCanInterface>
#include <QIcon>
#include "qcan_usart.hpp"

#include "canpie.h"

//----------------------------------------------------------------------------//
// QCanPeakUsb                                                                //
//                                                                            //
//----------------------------------------------------------------------------//
class QCanInterfaceUsart : public QCanInterface
{
    Q_OBJECT

private:

   /*!
    * \brief clStatisticP
    */
   QCanStatistic_ts clStatisticP;

   /*!
    * \brief readCAN
    * \param clFrameR
    * \param ubChannelV
    * \return
    *
    * Read CAN message from peak USB device
    */
   InterfaceError_e  readCAN(QByteArray &clDataR);

   /*!
    * \brief readFD
    * \param clFrameR
    * \param ubChannelV
    * \return
    *
    * Read CAN FD message from peak USB device
    */
   InterfaceError_e  readFD(QByteArray &clDataR);

   /*!
    * \brief ubChannelP
    * This value holds channel number of interface
    */
   uint16_t uwPCanChannelP;
   uint16_t uwPCanBitrateP;
   CAN_Mode_e teCanModeP;

   QString  clDeviceNameP;
   uint16_t uwDeviceNumberP;
   CpPort_ts tsPortP;


   //----------------------------------------------------------------
   // Reference to the static PCAN Basic lib
   //
   QCanUsart &pclCpUsartP = QCanUsart::getInstance();

   /*!
    * \brief btConnectedP
    */
   bool btConnectedP;

   bool btFdUsedP;

//   void setupErrorFrame(TPCANStatus ulStatusV, QCanFrameError &clFrameR);

public:

   QCanInterfaceUsart(uint16_t uwDevNrV, QString clNameV);
   ~QCanInterfaceUsart();

   InterfaceError_e  connect(void) Q_DECL_OVERRIDE;

   bool              connected(void) Q_DECL_OVERRIDE;

   InterfaceError_e  disconnect(void) Q_DECL_OVERRIDE;

   QIcon             icon(void) Q_DECL_OVERRIDE;

   QString           name(void) Q_DECL_OVERRIDE;

   InterfaceError_e  read( QByteArray &clDataR) Q_DECL_OVERRIDE;

   InterfaceError_e  reset(void) Q_DECL_OVERRIDE;

   InterfaceError_e  setBitrate( int32_t slBitrateV,
                                 int32_t slBrsClockV) Q_DECL_OVERRIDE;

   InterfaceError_e  setMode( const CAN_Mode_e teModeV) Q_DECL_OVERRIDE;

   InterfaceError_e  statistic(QCanStatistic_ts &clStatisticR) Q_DECL_OVERRIDE;

   uint32_t          supportedFeatures(void) Q_DECL_OVERRIDE;

   InterfaceError_e  write(const QCanFrame &clFrameR) Q_DECL_OVERRIDE;

Q_SIGNALS:
    void errorOccurred(int32_t slCanBusErrorV);
};

#endif /*QCAN_INTERFACE_USART_H_*/
