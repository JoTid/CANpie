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

int QCanUsart::open(QString clNameV)
{
   // Releasing of port seem not to work.
   if (pclSerialPortP != NULL)
   {
      pclSerialPortP->close();
      delete(pclSerialPortP);
   }

   pclSerialPortP = new QSerialPort();

   pclSerialPortP->setPortName(clNameV);
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

////----------------------------------------------------------------------------//
//// formatedError()                                                            //
////                                                                            //
////----------------------------------------------------------------------------//
//QString QCanUsart::formatedError(TPCANStatus tvErrorV)
//{
//   TPCANStatus tvStatusT;
//   char aszBufferT[256];
//   QString clResultT;

//   memset(aszBufferT,'\0',256);

//   // Gets the text using the GetErrorText API function
//   // If the function success, the translated error is returned. If it fails,
//   // a text describing the current error is returned.
//   //

//   tvStatusT = pfnCAN_GetErrorTextP(tvErrorV,0x00,aszBufferT);
//   if(tvStatusT != PCAN_ERROR_OK)
//   {
//      clResultT = ("An error ocurred. Error-code's text ("+ QString::number(tvErrorV,16).toUpper() + "h) couldn't be retrieved");
//   } else
//   {
//      clResultT = QString::number(tvErrorV,16).toUpper() + "h : " + QLatin1String(aszBufferT);
//   }

//   return clResultT;
//}

