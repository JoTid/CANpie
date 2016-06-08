//============================================================================//
// File:          qcan_ixxatusb.cpp                                           //
// Description:   CAN plugin for IXXAT USB device                             //
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

#include <QtWidgets>
#include <qcan_ixxatusb.hpp>

QString QCanIxxatUsb::echo(const QString &message)
{
    return ("ixxat: " + message);
}

int32_t QCanIxxatUsb::setBitrate(uint32_t ulBitrateV, uint32_t ulBrsClockV)
{
    return 0;
}

int32_t	QCanIxxatUsb::setMode(const uint32_t ulModeV)
{
   return 0;
}

int32_t	QCanIxxatUsb::state(void)
{
   return 0;
}

int32_t	QCanIxxatUsb::statistic(QCanStatistic_ts &clStatisticR)
{
   return 0;
}

int32_t	QCanIxxatUsb::read(QCanFrame &clFrameR)
{
   return 0;
}

int32_t	QCanIxxatUsb::write(const QCanFrame &clFrameR)
{
   return 0;
}

int32_t QCanIxxatUsb::connect(void)
{
   return 0;
}

int32_t QCanIxxatUsb::disconnect(void)
{
   return 0;
}
