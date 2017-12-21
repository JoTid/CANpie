//============================================================================//
// File:          qcan_usart.cpp                                              //
// Description:   QCAN USART library handling                                 //
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

#include "qcan_usart.hpp"
#include "mc_usart.h"

int32_t McUsartInit(uint8_t ubPortV, uint32_t ulBaudV, uint8_t ubModeV)
{
   QCanUsart &pclCanUsartT = QCanUsart::getInstance();

   pclCanUsartT.InitCpUsart();
   
   pclCanUsartT.log("McUsartInit() have been called ");


}

int32_t McUsartSetRcvBufferSize(uint8_t ubPortV, uint32_t ulSizeV)
{

}

int32_t McUsartSetDir(uint8_t ubPortV, uint8_t ubDirV)
{
}

int32_t McUsartRelease(uint8_t ubPortV)
{


}

int32_t McUsartWrite(uint8_t ubPortV, uint8_t *pubBufferV, uint32_t ulSizeV)
{

}

int32_t McUsartSetRcvHandler(uint8_t ubPortV, UsartHandler_fn pfnHandler)
{

}

int32_t McUsartSetTrmHandler(uint8_t ubPortV, UsartHandler_fn pfnHandler)
{

}
void QCanUsart::log(QString clStringV)
{
   qDebug() << ":::::::::::::::::"<< clStringV;
}

QCanUsart::ReleaseCpUsart()
{
   QCanUsart &pclCanUsartT = QCanUsart::getInstance();
   // Releasing of port seem not to work.
   if (pclCanUsartT.pclSerialPortP != NULL)
   {
      pclCanUsartT.pclSerialPortP->close();
      delete(pclCanUsartT.pclSerialPortP);

      pclCanUsartT.pclSerialPortP = NULL;
   }
}

QCanUsart::InitCpUsart()
{
   // Releasing of port seem not to work.
   if (pclSerialPortP != NULL)
   {
      pclSerialPortP->close();
      delete(pclSerialPortP);
   }

   pclSerialPortP = new QSerialPort();

   pclSerialPortP->setPortName(clNameP);
   pclSerialPortP->setBaudRate(115200,QSerialPort::AllDirections);
   pclSerialPortP->setDataBits(QSerialPort::Data8);
   pclSerialPortP->setParity(QSerialPort::EvenParity);
   pclSerialPortP->setStopBits(QSerialPort::OneStop);
   pclSerialPortP->setFlowControl(QSerialPort::NoFlowControl);
   if (pclSerialPortP->open(QIODevice::ReadWrite))
   {
      qDebug() << "   SUCCESS!!!";
//      log(McLog::eLOG_DEBUG, (tr("Serial COM Port: ") + pclSerialPortP->portName() + " opened!"));
      return 0;

   } else
   {
//       QMessageBox::critical(this, tr("Error"), serial->errorString());

//      log(McLog::eLOG_DEBUG, tr("Fail to OPEN ") + pclSerialPortP->portName());
//      log(McLog::eLOG_DEBUG, pclSerialPortP->errorString());
      qDebug() << "   FAIL: " << pclSerialPortP->error();

//       ui->statusBar->showMessage(tr("Open error"));
      return -1;
   }
}
//----------------------------------------------------------------------------//
// QCanUsart()                                                                //
//                                                                            //
//----------------------------------------------------------------------------//
QCanUsart::QCanUsart()
{
//   QStringList         clPortListT;
//   QString             clPortNameT;
//   QString             clPortNumberT;

   btLibFuncLoadP = true;
   pclSerialPortP = NULL;

   //----------------------------------------------------------------
//   // Initialise Serial Port with configuration from hw_config
//   //

//   // Releasing of port seem not to work.
//   if (pclSerialPortP != NULL)
//   {
//      pclSerialPortP->close();
//      delete(pclSerialPortP);
//   }

//   //clPortListT.clear();
//   clPortNameT.clear();
//   foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
//   {
//      //clPortListT.append(info.portName());
//      if (clPortNameT.isEmpty())
//      {
//         clPortNameT = info.portName();
//      }
////      // check the port is the selected by user
////      if ((info.portName().contains(pclPrjParamP->aclHwComInterfaceNameM[0],Qt::CaseInsensitive)) &&
////          (info.portName().length() == pclPrjParamP->aclHwComInterfaceNameM[0].length()))
////      {
////         clPortNameT = info.portName();
////         log(McLog::eLOG_DEBUG, (tr("Serial COM Port ")
////                                                   + clPortNameT + " for initialisation found"));
////      }
//   }

//      qDebug() << "Open serial port " << clPortNameT;

//   pclSerialPortP = new QSerialPort();

//   pclSerialPortP->setPortName(clPortNameT);
//   pclSerialPortP->setBaudRate(115200,QSerialPort::AllDirections);
//   pclSerialPortP->setDataBits(QSerialPort::Data8);
//   pclSerialPortP->setParity(QSerialPort::EvenParity);
//   pclSerialPortP->setStopBits(QSerialPort::OneStop);
//   pclSerialPortP->setFlowControl(QSerialPort::NoFlowControl);
//   if (pclSerialPortP->open(QIODevice::ReadWrite))
//   {
//      qDebug() << "   SUCCESS!!!";
////      log(McLog::eLOG_DEBUG, (tr("Serial COM Port: ") + pclSerialPortP->portName() + " opened!"));

//   } else
//   {
////       QMessageBox::critical(this, tr("Error"), serial->errorString());

////      log(McLog::eLOG_DEBUG, tr("Fail to OPEN ") + pclSerialPortP->portName());
////      log(McLog::eLOG_DEBUG, pclSerialPortP->errorString());
//      qDebug() << "   FAIL: " << pclSerialPortP->error();

////       ui->statusBar->showMessage(tr("Open error"));
//   }

//   // get file name
//   clCanLibP.setFileName(QCAN_PEAKLIB);

//   if (!clCanLibP.load()) {
//       qCritical() << "QCanUsart(): Failed to load the library:" << qPrintable(clCanLibP.fileName());
//   }

//   else
//   {
//      //----------------------------------------------------------------
//      // Loads API functions
//      //
//      pfnCAN_InitializeP = (QCanUsart::CAN_Initialize_tf) clCanLibP.resolve("CAN_Initialize");
//      #if QCAN_SUPPORT_CAN_FD > 0
//      pfnCAN_InitializeFDP = (QCanUsart::CAN_InitializeFD_tf) clCanLibP.resolve("CAN_InitializeFD");
//      #endif
//      pfnCAN_UninitializeP = (QCanUsart::CAN_Uninitialize_tf)clCanLibP.resolve("CAN_Uninitialize");
//      pfnCAN_ResetP = (QCanUsart::CAN_Reset_tf)clCanLibP.resolve("CAN_Reset");
//      pfnCAN_GetStatusP = (QCanUsart::CAN_GetStatus_tf)clCanLibP.resolve("CAN_GetStatus");
//      pfnCAN_ReadP = (QCanUsart::CAN_Read_tf)clCanLibP.resolve("CAN_Read");
//      #if QCAN_SUPPORT_CAN_FD > 0
//      pfnCAN_ReadFDP = (QCanUsart::CAN_ReadFD_tf)clCanLibP.resolve("CAN_ReadFD");
//      #endif
//      pfnCAN_WriteP = (QCanUsart::CAN_Write_tf)clCanLibP.resolve("CAN_Write");
//      #if QCAN_SUPPORT_CAN_FD > 0
//      pfnCAN_WriteFDP = (QCanUsart::CAN_WriteFD_tf)clCanLibP.resolve("CAN_WriteFD");
//      #endif
//      pfnCAN_FilterMessagesP = (QCanUsart::CAN_FilterMessages_tf)clCanLibP.resolve("CAN_FilterMessages");
//      pfnCAN_GetValueP = (QCanUsart::CAN_GetValue_tf)clCanLibP.resolve("CAN_GetValue");
//      pfnCAN_SetValueP = (QCanUsart::CAN_SetValue_tf)clCanLibP.resolve("CAN_SetValue");
//      pfnCAN_GetErrorTextP = (QCanUsart::CAN_GetErrorText_tf)clCanLibP.resolve("CAN_GetErrorText");


//      //----------------------------------------------------------------
//      // check for success
//      //
//      btLibFuncLoadP =  pfnCAN_InitializeP &&
//                        #if QCAN_SUPPORT_CAN_FD > 0
//                        pfnCAN_InitializeFDP &&
//                        #endif
//                        pfnCAN_UninitializeP &&
//                        pfnCAN_ResetP &&
//                        pfnCAN_GetStatusP &&
//                        pfnCAN_ReadP  &&
//                        pfnCAN_WriteP &&
//                        #if QCAN_SUPPORT_CAN_FD > 0
//                        pfnCAN_FilterMessagesP &&
//                        pfnCAN_ReadFDP &&
//                        pfnCAN_WriteFDP &&
//                        #endif
//                        pfnCAN_GetValueP &&
//                        pfnCAN_SetValueP &&
//                        pfnCAN_GetErrorTextP;

//      //----------------------------------------------------------------
//      // If the API was not loaded (Wrong version), an error message is shown.
//      //
//      if (!btLibFuncLoadP)
//      {
//         qCritical() << "QCanUsart::QCanUsart() CRITICAL: Fail to load some library functions!";
//      } else
//      {
//         qInfo() << "QCanUsart::QCanUsart() INFO: All library functions succesfully loaded!";
//      }
//   }
}

//----------------------------------------------------------------------------//
// ~QCanUsart()                                                           //
//                                                                            //
//----------------------------------------------------------------------------//
QCanUsart::~QCanUsart()
{
   qDebug() << "QCanUsart::~QCanUsart()";

//   //----------------------------------------------------------------
//   // Unload library
//   //
//   if (clCanLibP.isLoaded())
//   {
//      //--------------------------------------------------------
//      // release all devices
//      //
//      if (isAvailable())
//      {
//         pfnCAN_UninitializeP(PCAN_NONEBUS);
//         btLibFuncLoadP = false;
//      }

//      //--------------------------------------------------------
//      // unload library
//      //
//      clCanLibP.unload();
//   }

//   //----------------------------------------------------------------
//   // remove all API functions
//   //
//   pfnCAN_InitializeP = NULL;
//   pfnCAN_UninitializeP = NULL;
//   pfnCAN_ResetP = NULL;
//   pfnCAN_GetStatusP = NULL;
//   pfnCAN_ReadP = NULL;
//   pfnCAN_WriteP = NULL;
//   pfnCAN_FilterMessagesP = NULL;
//   pfnCAN_GetValueP = NULL;
//   pfnCAN_SetValueP = NULL;
//   pfnCAN_GetErrorTextP = NULL;

//   #if QCAN_SUPPORT_CAN_FD > 0
//   pfnCAN_InitializeFDP = NULL;
//   pfnCAN_ReadFDP = NULL;
//   pfnCAN_WriteFDP = NULL;
//   #endif
}

//----------------------------------------------------------------------------//
// isAvailable()                                                              //
//                                                                            //
//----------------------------------------------------------------------------//
bool QCanUsart::isAvailable()
{
   return btLibFuncLoadP;

}

int QCanUsart::close()
{
   // Releasing of port seem not to work.
   if (pclSerialPortP != NULL)
   {
      pclSerialPortP->close();
      delete(pclSerialPortP);

      pclSerialPortP = NULL;
   }
}

CpPort_ts tsCpPortG;

CpStatus_tv QCanUsart::CpUsartBitrate(CpPort_ts *ptsPortV, int32_t slNomBitRateV,
                           int32_t slDatBitRateV)
{
//   return (CpCoreBitrate(ptsPortV, eCP_BITRATE_125K, eCP_BITRATE_NONE));
   return eCP_ERR_NONE;
}

CpStatus_tv QCanUsart::CpUsartDriverInit(uint8_t ubPhyIfV, CpPort_ts *ptsPortV, uint8_t ubConfigV)
{
//   clNameP = clNameV;
   qDebug() << "...........................................QCanUsart::open: "<< QString::number(ubPhyIfV,10);
   qDebug() << "CpCoreDriverInit() => " << QString::number(CpCoreDriverInit(ubPhyIfV+1, ptsPortV, ubConfigV),16);
   qDebug() << "CpCoreBitrate() => " << QString::number(CpCoreBitrate(ptsPortV,eCP_BITRATE_125K, eCP_BITRATE_NONE),16);
   return eCP_ERR_NONE;

}

CpStatus_tv QCanUsart::CpUsartDriverRelease(CpPort_ts *ptsPortV)
{
   return (CpCoreDriverRelease(ptsPortV));
}


//----------------------------------------------------------------------------//
// formatedError()                                                            //
//                                                                            //
//----------------------------------------------------------------------------//
QString QCanUsart::formatedError(CpStatus_tv tvErrorV)
{
   QString clResultT;

   clResultT = ("An error ocurred. Error-code's text ("+ QString::number(tvErrorV,16).toUpper() + "h) couldn't be retrieved");

   return clResultT;
}

