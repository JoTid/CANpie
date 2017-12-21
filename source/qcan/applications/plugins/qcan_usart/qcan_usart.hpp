//============================================================================//
// File:          qcan_usart.hpp                                              //
// Description:   QCAN USART library API                                      //
//                                                                            //
// Copyright (C) MicroControl GmbH & Co. KG                                   //
// 53844 Troisdorf - Germany                                                  //
// www.microcontrol.net                                                       //
//                                                                            //
//----------------------------------------------------------------------------//
// Redistribution and use in source and binary forms, with or without         //
// modification, are permitted provided that the following conditions         //
// are met:                                                                   //
// 1. Redistributions of source code must retain the above copyright          //
//    notice, this list of conditions, the following disclaimer and           //
//    the referenced file 'LICENSE'.                                          //
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

#ifndef QCAN_USART_H_
#define QCAN_USART_H_

#include <QObject>


#include <QLibrary>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "cp_core.h"
#include "cp_fifo.h"
#include "cp_msg.h"


//----------------------------------------------------------------------------//
// QCanPeakUsb                                                                //
//                                                                            //
//----------------------------------------------------------------------------//
class QCanUsart
{

private:

   QLibrary clCanLibP;
   bool btLibFuncLoadP;

   QCanUsart();
   QCanUsart(const QCanUsart &);
   QSerialPort    *pclSerialPortP;

   QString clNameP;

public:
   ~QCanUsart();

   InitCpUsart();
   ReleaseCpUsart();

   int open(QString name);
   int close();

   CpStatus_tv CpUsartBitrate(CpPort_ts *ptsPortV, int32_t slNomBitRateV,
                              int32_t slDatBitRateV);

   CpStatus_tv CpUsartBufferConfig(CpPort_ts *ptsPortV,
                                  uint8_t   ubBufferIdxV,
                                  uint32_t  ulIdentifierV,
                                  uint32_t  ulAcceptMaskV,
                                  uint8_t   ubFormatV,
                                  uint8_t   ubDirectionV);

   CpStatus_tv CpUsartBufferEnable(CpPort_ts *ptsPortV, uint8_t ubBufferIdxV,
                                  uint8_t ubEnableV);
   CpStatus_tv CpUsartBufferGetData(CpPort_ts *ptsPortV, uint8_t ubBufferIdxV,
                                   uint8_t *pubDestDataV,
                                   uint8_t   ubStartPosV,
                                   uint8_t   ubSizeV);
   CpStatus_tv CpUsartBufferGetDlc(CpPort_ts *ptsPortV, uint8_t ubBufferIdxV,
                                  uint8_t *pubDlcV);
   CpStatus_tv CpUsartBufferRelease(CpPort_ts *ptsPortV, uint8_t ubBufferIdxV);
   CpStatus_tv CpUsartBufferSend(CpPort_ts *ptsPortV, uint8_t ubBufferIdxV);
   CpStatus_tv CpUsartBufferSetData(CpPort_ts *ptsPortV, uint8_t ubBufferIdxV,
                                   uint8_t *pubSrcDataV,
                                   uint8_t   ubStartPosV,
                                   uint8_t   ubSizeV);
   CpStatus_tv CpUsartBufferSetDlc(CpPort_ts *ptsPortV, uint8_t ubBufferIdxV,
                                  uint8_t ubDlcV);
   CpStatus_tv CpUsartCanMode(CpPort_ts *ptsPortV, uint8_t ubModeV);
   CpStatus_tv CpUsartCanState(CpPort_ts *ptsPortV, CpState_ts *ptsStateV);
   CpStatus_tv CpUsartDriverInit(uint8_t ubPhyIfV, CpPort_ts *ptsPortV,
                                uint8_t ubConfigV);

   CpStatus_tv CpUsartDriverRelease(CpPort_ts *ptsPortV);
   CpStatus_tv CpUsartFifoConfig(CpPort_ts *ptsPortV, uint8_t ubBufferIdxV,
                                CpFifo_ts *ptsFifoV);

   void        CpUsartFifoEvent(CpPort_ts *ptsPortV, uint8_t ubBufferIdxV);
   CpStatus_tv CpUsartFifoRead(CpPort_ts *ptsPortV, uint8_t ubBufferIdxV,
                              CpCanMsg_ts *ptsCanMsgV,
                              uint32_t *pulMsgCntV);

   CpStatus_tv CpUsartFifoRelease(CpPort_ts *ptsPortV, uint8_t ubBufferIdxV);
   CpStatus_tv CpUsartFifoWrite(CpPort_ts *ptsPortV, uint8_t ubBufferIdxV,
                               CpCanMsg_ts *ptsCanMsgV,
                               uint32_t *pulMsgCntV);

   CpStatus_tv CpUsartHDI(CpPort_ts *ptsPortV, CpHdi_ts *ptsHdiV);

   CpStatus_tv CpUsartIntFunctions(CpPort_ts *ptsPortV,
                                  CpRcvHandler_Fn pfnRcvHandlerV,
                                  CpTrmHandler_Fn pfnTrmHandlerV,
                                  CpErrHandler_Fn pfnErrHandlerV);
   CpStatus_tv CpUsartStatistic(CpPort_ts *ptsPortV, CpStatistic_ts *ptsStatsV);


   // allow only one instance of PCAN Basic
   static QCanUsart & getInstance()
   {
      static QCanUsart clInstanceS;
      return clInstanceS;
   }

   void log(QString);
   // helper functions
   bool isAvailable (void);
   QString formatedError(CpStatus_tv tvErrorV);
};

#endif /*QCAN_USART_H_*/
