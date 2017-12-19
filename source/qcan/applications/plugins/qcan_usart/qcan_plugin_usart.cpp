//============================================================================//
// File:          qcan_plugin_peak.cpp                                        //
// Description:   CAN plugin for PCAN Basic library                           //
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

#include "qcan_plugin_usart.hpp"

//----------------------------------------------------------------------------//
// QCanPluginUsart()                                                           //
//                                                                            //
//----------------------------------------------------------------------------//
QCanPluginUsart::QCanPluginUsart()
{
   qDebug() << "QCanPluginUsart::QCanPluginUsart()";

   // reset number of interfaces
//   apclQCanInterfaceUsartP.clear();
   atsQCanIfUsartP.clear();
   auwPCanChannelP.clear();

   QStringList         clPortListT;
   QString             clPortNameT;
   QString             clPortNumberT;


   //----------------------------------------------------------------
   // check PCAN Basic lib is available
   //
   if (!pclCpUsartP.isAvailable())
   {
      qCritical() << "QCanPluginUsart::QCanPluginUsart() CRITICAL: PEAKBasic library is not available or not all functions could be loaded!";
   }
   else
   {



////      btLibFuncLoadP = true;
//      pclSerialPortP = NULL;

//      //----------------------------------------------------------------
//      // Initialise Serial Port with configuration from hw_config
//      //

//      // Releasing of port seem not to work.
//      if (pclSerialPortP != NULL)
//      {
//         pclSerialPortP->close();
//         delete(pclSerialPortP);
//      }

//      //clPortListT.clear();
//      clPortNameT.clear();
//      foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
//      {
//         //clPortListT.append(info.portName());
//         if (clPortNameT.isEmpty())
//         {
//            clPortNameT = info.portName();
//         }
//   //      // check the port is the selected by user
//   //      if ((info.portName().contains(pclPrjParamP->aclHwComInterfaceNameM[0],Qt::CaseInsensitive)) &&
//   //          (info.portName().length() == pclPrjParamP->aclHwComInterfaceNameM[0].length()))
//   //      {
//   //         clPortNameT = info.portName();
//   //         log(McLog::eLOG_DEBUG, (tr("Serial COM Port ")
//   //                                                   + clPortNameT + " for initialisation found"));
//   //      }
//      }

//         qDebug() << "Open serial port " << clPortNameT;

//      pclSerialPortP = new QSerialPort();

//      pclSerialPortP->setPortName(clPortNameT);
//      pclSerialPortP->setBaudRate(115200,QSerialPort::AllDirections);
//      pclSerialPortP->setDataBits(QSerialPort::Data8);
//      pclSerialPortP->setParity(QSerialPort::EvenParity);
//      pclSerialPortP->setStopBits(QSerialPort::OneStop);
//      pclSerialPortP->setFlowControl(QSerialPort::NoFlowControl);
//      if (pclSerialPortP->open(QIODevice::ReadWrite))
//      {
//         qDebug() << "   SUCCESS!!!";
//   //      log(McLog::eLOG_DEBUG, (tr("Serial COM Port: ") + pclSerialPortP->portName() + " opened!"));

//      } else
//      {
//   //       QMessageBox::critical(this, tr("Error"), serial->errorString());

//   //      log(McLog::eLOG_DEBUG, tr("Fail to OPEN ") + pclSerialPortP->portName());
//   //      log(McLog::eLOG_DEBUG, pclSerialPortP->errorString());
//         qDebug() << "   FAIL: " << pclSerialPortP->error();

//   //       ui->statusBar->showMessage(tr("Open error"));
//      }

//      //----------------------------------------------------------------
//      // add in actual version only USB channels
//      //
//      auwPCanChannelP.append(PCAN_USBBUS1);
//      auwPCanChannelP.append(PCAN_USBBUS2);
//      auwPCanChannelP.append(PCAN_USBBUS3);
//      auwPCanChannelP.append(PCAN_USBBUS4);
//      auwPCanChannelP.append(PCAN_USBBUS5);
//      auwPCanChannelP.append(PCAN_USBBUS6);
//      auwPCanChannelP.append(PCAN_USBBUS7);
//      auwPCanChannelP.append(PCAN_USBBUS8);

//      //----------------------------------------------------------------
//      // more than 8 USB channels only suppoted by Windows DLL
//      //
//      #ifdef   Q_OS_WIN32
//      auwPCanChannelP.append(PCAN_USBBUS9);
//      auwPCanChannelP.append(PCAN_USBBUS10);
//      auwPCanChannelP.append(PCAN_USBBUS11);
//      auwPCanChannelP.append(PCAN_USBBUS12);
//      auwPCanChannelP.append(PCAN_USBBUS13);
//      auwPCanChannelP.append(PCAN_USBBUS14);
//      auwPCanChannelP.append(PCAN_USBBUS15);
//      auwPCanChannelP.append(PCAN_USBBUS16);
//      #endif
   }
}

//----------------------------------------------------------------------------//
// ~QCanPeakUsb()                                                             //
//                                                                            //
//----------------------------------------------------------------------------//
QCanPluginUsart::~QCanPluginUsart()
{
   qDebug() << "QCanPluginUsart::~QCanPluginUsart()";

   //----------------------------------------------------------------
   // disconnect all connected interfaces and delete objects
   //
   foreach (QCanIf_ts tsCanIfEntryT, atsQCanIfUsartP)
   {
      if (tsCanIfEntryT.pclQCanInterfaceUsart->connected())
      {
         tsCanIfEntryT.pclQCanInterfaceUsart->disconnect();
      }
      tsCanIfEntryT.pclQCanInterfaceUsart->deleteLater();
      tsCanIfEntryT.pclQCanInterfaceUsart = NULL;
   }

   atsQCanIfUsartP.clear();
}

//----------------------------------------------------------------------------//
// interfaceCount()                                                           //
//                                                                            //
//----------------------------------------------------------------------------//
uint8_t QCanPluginUsart::interfaceCount()
{
   //----------------------------------------------------------------
   // check conditions of each channel
   //
//   TPCANStatus    tsStatusT;
   uint32_t       ulParmBufferT;
   QCanIf_ts      tsCanIfEntryT;
   bool           btIfIsInListT;

   qDebug() << "QCanPluginUsart::interfaceCount()";

   if (!pclCpUsartP.isAvailable())
   {
      return 0;
   }

   QString clPortNameT;
//   QclPortNameT.clear();
   QSerialPort *pclSerialPort;
   foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
   {
      //clPortListT.append(info.portName());
      if (clPortNameT.isEmpty() != 0)
      {
         clPortNameT = info.portName();
         qDebug() << "Found USART interface: " << clPortNameT;

      pclSerialPort = new QSerialPort(info);

//      tsStatusT = pclCpUsartP.pfnCAN_GetValueP(auwPCanChannelP[ubPCanChnT], PCAN_CHANNEL_CONDITION,
//                                         (void*)&ulParmBufferT, sizeof(ulParmBufferT));
      if (pclSerialPort->error() != 0)
      {
         qDebug() << "QCanPluginUsart::QCanPluginUsart(): " << QString::number(pclSerialPort->error(),16);//pclCpUsartP.formatedError(tsStatusT);
         qDebug() << "Error: " << pclSerialPort->errorString();
      } else //if ((ulParmBufferT & PCAN_CHANNEL_AVAILABLE) == PCAN_CHANNEL_AVAILABLE)
      {
         // -----------------------------------------------
         // check this channel is already in the atsQCanIfUsartP list
         // if so, than do nothing
         // if not, than append this channel and interface to atsQCanIfUsartP
         //
         btIfIsInListT = false;
         foreach (tsCanIfEntryT, atsQCanIfUsartP)
         {
            if (tsCanIfEntryT.pclQCanInterfaceUsart->name() == clPortNameT)
            {
               btIfIsInListT = true;
               break;
            }
         }

         //------------------------------------------------
         // if new interface is not in the list,
         // than append new entry
         if (btIfIsInListT == false)
         {
            tsCanIfEntryT.uwPCanChannel = 0;
            tsCanIfEntryT.pclQCanInterfaceUsart = new QCanInterfaceUsart(clPortNameT);
            atsQCanIfUsartP.append(tsCanIfEntryT);

            qInfo() << "QCanPluginUsart::QCanPluginUsart() INFO: Add Interface" <<
                       QString::number(atsQCanIfUsartP.length()) <<
                       "with channel value" <<
                       QString::number(auwPCanChannelP[0],16) <<
                       "[hex].";
         }

      }
//      else
//      {
//         // Device with given PCAN Channel value is not available or is ocupied

//         //------------------------------------------------
//         // if this channel is in atsQCanIfUsartP
//         //
//         for (uint8_t ubCntrT = 0; ubCntrT < (uint8_t)atsQCanIfUsartP.length(); ubCntrT++)
//         {
//            if (atsQCanIfUsartP.at(ubCntrT).uwPCanChannel == auwPCanChannelP[ubPCanChnT])
//            {

//               qInfo() << "QCanPluginUsart::QCanPluginUsart() INFO: Remove Interface" <<
//                          QString::number(ubCntrT) <<
//                          "with channel value" <<
//                          QString::number(atsQCanIfUsartP.at(ubCntrT).uwPCanChannel,16) <<
//                          "[hex] from available list.";

//               atsQCanIfUsartP.removeAt(ubCntrT);
//               break;
//            }
//         }
//      }
            }
   }

//   //----------------------------------------------------------------
//   // remove all not connected devices and add new
//   //
//   for (uint8_t ubPCanChnT = 0; ubPCanChnT < (uint8_t)auwPCanChannelP.length(); ubPCanChnT++)
//   {
//      tsStatusT = pclCpUsartP.pfnCAN_GetValueP(auwPCanChannelP[ubPCanChnT], PCAN_CHANNEL_CONDITION,
//                                         (void*)&ulParmBufferT, sizeof(ulParmBufferT));
//      if (tsStatusT != PCAN_ERROR_OK)
//      {
//         qDebug() << "QCanPluginUsart::QCanPluginUsart()" << pclCpUsartP.formatedError(tsStatusT);
//      } else if ((ulParmBufferT & PCAN_CHANNEL_AVAILABLE) == PCAN_CHANNEL_AVAILABLE)
//      {
//         // -----------------------------------------------
//         // check this channel is already in the atsQCanIfUsartP list
//         // if so, than do nothing
//         // if not, than append this channel and interface to atsQCanIfUsartP
//         //
//         btIfIsInListT = false;
//         foreach (tsCanIfEntryT, atsQCanIfUsartP)
//         {
//            if (tsCanIfEntryT.uwPCanChannel == auwPCanChannelP[ubPCanChnT])
//            {
//               btIfIsInListT = true;
//               break;
//            }
//         }

//         //------------------------------------------------
//         // if new interface is not in the list,
//         // than append new entry
//         if (btIfIsInListT == false)
//         {
//            tsCanIfEntryT.uwPCanChannel = auwPCanChannelP[ubPCanChnT];
//            tsCanIfEntryT.pclQCanInterfaceUsart = new QCanInterfaceUsart(auwPCanChannelP[ubPCanChnT]);
//            atsQCanIfUsartP.append(tsCanIfEntryT);

//            qInfo() << "QCanPluginUsart::QCanPluginUsart() INFO: Add Interface" <<
//                       QString::number(atsQCanIfUsartP.length()) <<
//                       "with channel value" <<
//                       QString::number(auwPCanChannelP[ubPCanChnT],16) <<
//                       "[hex].";
//         }

//      } else
//      {
//         // Device with given PCAN Channel value is not available or is ocupied

//         //------------------------------------------------
//         // if this channel is in atsQCanIfUsartP
//         //
//         for (uint8_t ubCntrT = 0; ubCntrT < (uint8_t)atsQCanIfUsartP.length(); ubCntrT++)
//         {
//            if (atsQCanIfUsartP.at(ubCntrT).uwPCanChannel == auwPCanChannelP[ubPCanChnT])
//            {

//               qInfo() << "QCanPluginUsart::QCanPluginUsart() INFO: Remove Interface" <<
//                          QString::number(ubCntrT) <<
//                          "with channel value" <<
//                          QString::number(atsQCanIfUsartP.at(ubCntrT).uwPCanChannel,16) <<
//                          "[hex] from available list.";

//               atsQCanIfUsartP.removeAt(ubCntrT);
//               break;
//            }
//         }
//      }
//   }

   //----------------------------------------------------------------
   // Length of apclQCanInterfaceUsartP corresponds always to
   // the actual available interface number
   //
   qDebug() << "return number of interfaces" << QString::number((uint8_t)atsQCanIfUsartP.length(),10);
   return (uint8_t)atsQCanIfUsartP.length();
}

//----------------------------------------------------------------------------//
// getInterface()                                                             //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterface * QCanPluginUsart::getInterface(uint8_t ubInterfaceV)
{
   qDebug() << "QCanPluginUsart::getInterface(" + QString::number(ubInterfaceV,10) +")";
   if (ubInterfaceV < atsQCanIfUsartP.length())
   {
      qDebug() << "QCanPluginUsart::getInterface() INFO: return pointer to interface" << QString::number(ubInterfaceV);

      return (atsQCanIfUsartP.at(ubInterfaceV).pclQCanInterfaceUsart);
   }

   qDebug() << "QCanPluginUsart::getInterface() CRITICAL: interface" << QString::number(ubInterfaceV) << "is not available!";

   return NULL;
}


//----------------------------------------------------------------------------//
// icon()                                                                     //
//                                                                            //
//----------------------------------------------------------------------------//
QIcon QCanPluginUsart::icon()
{
   return QIcon(":/images/usart.png");
}


//----------------------------------------------------------------------------//
// name()                                                                     //
//                                                                            //
//----------------------------------------------------------------------------//
QString QCanPluginUsart::name()
{
   return QString("USART CANpie");
}


