//============================================================================//
// File:          qcan_interface_usart.cpp                                    //
// Description:   QCan Inteface of USART library                              //
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

#include "qcan_interface_usart.hpp"


//----------------------------------------------------------------------------//
// QCanInterfaceUsart()                                                       //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterfaceUsart::QCanInterfaceUsart(uint16_t uwDeviceNrV, QString clNameV)
{
   if (!pclCpUsartP.isAvailable())
   {
      qCritical() << "QCanInterfaceUsart(): USART interface is available!";
   }

   clDeviceNameP = clNameV;
   uwDeviceNumberP = uwDeviceNrV;

   //----------------------------------------------------------------
   // setup interface variables
   //

   btConnectedP = false;
}

//----------------------------------------------------------------------------//
// ~QCanInterfaceUsart()                                                      //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterfaceUsart::~QCanInterfaceUsart()
{
   qDebug() << "QCanInterfaceUsart::~QCanInterfaceUsart()";

   if (pclCpUsartP.isAvailable())
   {
      if (btConnectedP)
      {
         btConnectedP = false;
         pclCpUsartP.CpUsartDriverRelease(&tsPortP);
      }
   }
}

//----------------------------------------------------------------------------//
// connect()                                                                  //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterface::InterfaceError_e QCanInterfaceUsart::connect(void)
{
   InterfaceError_e teReturnT = eERROR_LIBRARY;
   CpStatus_tv      tvStatusT;

   qDebug() << QString("QCanInterfaceUsart::connect()...");

   //----------------------------------------------------------------
   //
   //
   if (pclCpUsartP.isAvailable())
   {
      pclCpUsartP.setDeviceName(clDeviceNameP);
      tvStatusT = pclCpUsartP.CpUsartDriverInit(uwDeviceNumberP+1,&tsPortP,0);
      if (tvStatusT == eCP_ERR_NONE)
      {
         btConnectedP = true;
         teReturnT = eERROR_NONE;
      }
      else
      {
         qWarning() << QString("QCanInterfaceUsart::connect(0x" +QString::number(tsPortP.ubPhyIf,16)+", "+clDeviceNameP+")") << "fail with error:" << pclCpUsartP.formatedError(tvStatusT);
      }
   }

   return teReturnT;
}

//----------------------------------------------------------------------------//
// connected()                                                                //
//                                                                            //
//----------------------------------------------------------------------------//
bool QCanInterfaceUsart::connected(void)
{
   return btConnectedP;
}


//----------------------------------------------------------------------------//
// disconnect()                                                               //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterface::InterfaceError_e QCanInterfaceUsart::disconnect()
{
   CpStatus_tv tvStatusT;
   InterfaceError_e teReturnT = eERROR_LIBRARY;

   if (pclCpUsartP.isAvailable())
   {
      tvStatusT = pclCpUsartP.CpUsartDriverRelease(&tsPortP);
      if (tvStatusT == eCP_ERR_NONE)
      {
         btConnectedP = false;
         teReturnT = eERROR_NONE;
      }
      else
      {
         qWarning() << QString("QCanInterfaceUsart::disconnect(0x" +QString::number(tsPortP.ubPhyIf,16)+", "+clDeviceNameP+")") << "fail with error:" << pclCpUsartP.formatedError(tvStatusT);
      }
   }

   return teReturnT;
}

//----------------------------------------------------------------------------//
// icon()                                                                     //
//                                                                            //
//----------------------------------------------------------------------------//
QIcon QCanInterfaceUsart::icon(void)
{
   if (pclCpUsartP.isAvailable())
   {
      return QIcon(":/images/usart_if.png");
   }

   return QIcon("images/pcan_fail.ico");
}


//----------------------------------------------------------------------------//
// name()                                                                     //
//                                                                            //
//----------------------------------------------------------------------------//
QString QCanInterfaceUsart::name()
{
   qDebug() << "QCanInterfaceUsart::name()";
   if (pclCpUsartP.isAvailable())
   {
      return clDeviceNameP;
   }

   return QString("PCAN Basic library is not available");
}



//----------------------------------------------------------------------------//
// read()                                                                     //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterface::InterfaceError_e  QCanInterfaceUsart::read(QByteArray &clDataR)
{
//   qDebug() << "QCanInterfaceUsart::read()";
   if (!pclCpUsartP.isAvailable())
   {
      return eERROR_LIBRARY;
   }

   //----------------------------------------------------------------
   // check channel have been connected
   //
   //   qDebug() << "QCanInterfaceUsart::readCAN()";
   //   TPCANStatus       ulStatusT;
   //   uint8_t           ubCntT;
   //   TPCANMsg          tsCanMsgT;
   //   TPCANTimestamp    tsCanTimeStampT;
   //   uint32_t          ulMicroSecsT;
   //   QCanFrame         clCanFrameT;
   //   QCanFrameError    clErrFrameT;
   //   QCanTimeStamp     clTimeStampT;



   InterfaceError_e  clRetValueT = eERROR_FIFO_RCV_EMPTY;


      //----------------------------------------------------------------
      // get next message from FIFO
      //
   //   ulStatusT = pclCpUsartP.read(&tsCanMsgT, &tsCanTimeStampT);


   //   //----------------------------------------------------------------
   //   // read message structure
   //   //
   //   if (ulStatusT == PCAN_ERROR_OK)
   //   {
   //      //--------------------------------------------------------
   //      // handle data depending on type
   //      //
   //      if((tsCanMsgT.MSGTYPE & PCAN_MESSAGE_STATUS) > 0)
   //      {
   //         //------------------------------------------------
   //         // this is a status message
   //         //
   //         clRetValueT = eERROR_FIFO_RCV_EMPTY;
   //      }
   //      else
   //      {
   //         //------------------------------------------------
   //         // Classical CAN frame with standard or
   //         // extended identifier
   //         //
   //         if (tsCanMsgT.MSGTYPE & PCAN_MESSAGE_EXTENDED)
   //         {
   //            clCanFrameT.setFrameFormat(QCanFrame::eFORMAT_CAN_EXT);
   //         }
   //         else
   //         {
   //            clCanFrameT.setFrameFormat(QCanFrame::eFORMAT_CAN_STD);
   //         }

   //         //------------------------------------------------
   //         // Classical CAN remote frame
   //         //
   //         if (tsCanMsgT.MSGTYPE & PCAN_MESSAGE_RTR)
   //         {
   //            clCanFrameT.setRemote(true);
   //         }

   //         //------------------------------------------------
   //         // copy the identifier
   //         //
   //         clCanFrameT.setIdentifier(tsCanMsgT.ID);

   //         //------------------------------------------------
   //         // copy the DLC
   //         //
   //         clCanFrameT.setDlc(tsCanMsgT.LEN);

   //         //------------------------------------------------
   //         // copy the data
   //         //
   //         for (ubCntT = 0; ubCntT < clCanFrameT.dataSize(); ubCntT++)
   //         {
   //            clCanFrameT.setData(ubCntT, tsCanMsgT.DATA[ubCntT]);
   //         }

   //         //------------------------------------------------
   //         // copy the time-stamp
   //         // the value is a multiple of 1 us and has a
   //         // total time span of 4294,9 secs
   //         //
   //         ulMicroSecsT = tsCanTimeStampT.millis * 1000;
   //         ulMicroSecsT = ulMicroSecsT + tsCanTimeStampT.micros;
   //         clTimeStampT.fromMicroSeconds(ulMicroSecsT);

   //         clCanFrameT.setTimeStamp(clTimeStampT);

   //         //------------------------------------------------
   //         // increase statistic counter
   //         //
   //         clStatisticP.ulRcvCount++;

   //         //------------------------------------------------
   //         // copy the CAN frame to a byte array for transfer
   //         //
   //         clDataR = clCanFrameT.toByteArray();
   //      }
   //   }

   //   //----------------------------------------------------------------
   //   // test for bus error
   //   //
   //   else if ((ulStatusT & (TPCANStatus)PCAN_ERROR_ANYBUSERR) > 0)
   //   {
   //      setupErrorFrame(ulStatusT, clErrFrameT);
   //      //--------------------------------------------------------
   //      // copy the error frame to a byte array
   //      //
   //      clDataR = clErrFrameT.toByteArray();
   //   }

   //   //----------------------------------------------------------------
   //   // the receive queue is empty
   //   //
   //   else if (ulStatusT == PCAN_ERROR_QRCVEMPTY)
   //   {
   //      clRetValueT = eERROR_FIFO_RCV_EMPTY;
   //   }

   //   //----------------------------------------------------------------
   //   // some other error
   //   //
   //   else
   //   {
   //      clRetValueT = eERROR_DEVICE;
   //   }

   return (clRetValueT);
}

//----------------------------------------------------------------------------//
// reset()                                                                    //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterface::InterfaceError_e  QCanInterfaceUsart::reset()
{
   qDebug() << "QCanInterfaceUsart::reset()";

   //----------------------------------------------------------------
   // check lib is available
   //
   if (!pclCpUsartP.isAvailable())
   {
      return eERROR_LIBRARY;
   }

   //----------------------------------------------------------------
   // reset statistic values
   //
   clStatisticP.ulErrCount = 0;
   clStatisticP.ulRcvCount = 0;
   clStatisticP.ulTrmCount = 0;

   //----------------------------------------------------------------
   // perform a hardware reset only if
   // it hase been initialised before
   //
   if (btConnectedP)
   {
      disconnect();
      connect();
      setBitrate(ulUsartBitrateP,eCP_BITRATE_NONE);
   }

   return setMode(teCanModeP);
}

//----------------------------------------------------------------------------//
// setBitrate()                                                               //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterface::InterfaceError_e QCanInterfaceUsart::setBitrate(int32_t slNomBitRateV,
                                                               int32_t slDatBitRateV)
{
   InterfaceError_e teReturnT = eERROR_LIBRARY;
   CpStatus_tv tvStatusT;

   qDebug() << "QCanInterfaceUsart::setBitrate()";

   if (pclCpUsartP.isAvailable())
   {
      slNomBitRateV = eCP_BITRATE_125K;
      slDatBitRateV = eCP_BITRATE_NONE;

      ulUsartBitrateP = slNomBitRateV;
      tvStatusT = pclCpUsartP.CpUsartBitrate(&tsPortP, slNomBitRateV, slDatBitRateV);
      if (tvStatusT == eCP_ERR_NONE)
      {
         teReturnT = eERROR_NONE;
      }
      else
      {
         qWarning() << QString("QCanInterfaceUsart::disconnect(0x" +QString::number(tsPortP.ubPhyIf,16)+", "+clDeviceNameP+")") << "fail with error:" << pclCpUsartP.formatedError(tvStatusT);
      }
   }

   return teReturnT;
}


//----------------------------------------------------------------------------//
// setMode()                                                                  //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterface::InterfaceError_e	QCanInterfaceUsart::setMode(const CAN_Mode_e teModeV)
{
   uint8_t ubValueBufT;
   CpStatus_tv tvStatusT;

    qDebug() << "QCanInterfaceUsart::setMode()";

   //----------------------------------------------------------------
   // check lib is available
   //
   if (!pclCpUsartP.isAvailable())
   {
      return eERROR_LIBRARY;
   }

   //----------------------------------------------------------------
   // select mode
   //
   switch (teModeV)
   {
      case eCAN_MODE_START :

         //---------------------------------------------------
         // reset statistic values
         //
         clStatisticP.ulErrCount = 0;
         clStatisticP.ulRcvCount = 0;
         clStatisticP.ulTrmCount = 0;

         ubValueBufT = eCP_BUFFER_1;
         tvStatusT = pclCpUsartP.CpUsartCanMode(&tsPortP, eCAN_MODE_START);
         if (tvStatusT == eCP_ERR_NONE)
         {
            teCanModeP = eCAN_MODE_START;
         } else
         {
            qWarning() << QString("QCanInterfaceUsart::setMode(0x" +QString::number(tsPortP.ubPhyIf,16)+", "+clDeviceNameP+")") << "fail with error:" << pclCpUsartP.formatedError(tvStatusT);
         }
         break;

      case eCAN_MODE_STOP :
         teCanModeP = eCAN_MODE_STOP;
         break;

      default :
         return eERROR_MODE;
         break;
   }

   return eERROR_NONE;
}

//----------------------------------------------------------------------------//
// statistic()                                                                //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterface::InterfaceError_e	QCanInterfaceUsart::statistic(QCanStatistic_ts &clStatisticR)
{
   if(pclCpUsartP.isAvailable())
   {
      clStatisticR.ulErrCount = clStatisticP.ulErrCount;
      clStatisticR.ulRcvCount = clStatisticP.ulRcvCount;
      clStatisticR.ulTrmCount = clStatisticP.ulTrmCount;
   }
   else
   {
      return(eERROR_LIBRARY);
   }


   return(eERROR_NONE);
}


//----------------------------------------------------------------------------//
// supportedFeatures()                                                        //
//                                                                            //
//----------------------------------------------------------------------------//
uint32_t QCanInterfaceUsart::supportedFeatures()
{
   uint32_t ulFeaturesT = 0;

   qDebug() << "QCanInterfaceUsart::supportedFeatures()";

   if(pclCpUsartP.isAvailable())
   {
      ulFeaturesT = QCAN_IF_SUPPORT_LISTEN_ONLY;
   }

   return(ulFeaturesT);
}


//----------------------------------------------------------------------------//
// write()                                                                    //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterface::InterfaceError_e QCanInterfaceUsart::write(const QCanFrame &clFrameR)
{
   qDebug() << "QCanInterfaceUsart::write()";

//   TPCANStatus ulStatusT;
//   TPCANMsg    tsCanMsgT;
//   #if QCAN_SUPPORT_CAN_FD > 0
//   TPCANMsgFD  tsCanMsgFdT;
//   #endif
//   int32_t     slByteCntrT;

   if (!pclCpUsartP.isAvailable())
   {
      return eERROR_LIBRARY;
   }

   //----------------------------------------------------------------
   // prepare CAN message
   //
//   if (clFrameR.frameFormat() < QCanFrame::eFORMAT_FD_STD)
//   {
////      // copy all needed parameters to QCanFrame structure
////      if (clFrameR.isExtended())
////      {
////         tsCanMsgT.MSGTYPE = PCAN_MESSAGE_EXTENDED;
////      }
////      else
////      {
////         tsCanMsgT.MSGTYPE = PCAN_MESSAGE_STANDARD;
////      }

////      tsCanMsgT.ID = clFrameR.identifier();

////      tsCanMsgT.LEN= clFrameR.dlc();

////      for (slByteCntrT = 0; slByteCntrT < clFrameR.dlc(); slByteCntrT++)
////      {
////         tsCanMsgT.DATA[slByteCntrT] = clFrameR.data(slByteCntrT);
////      }

////      ulStatusT = pclCpUsartP.pfnCAN_WriteP(uwPCanChannelP, &tsCanMsgT);

//   }
//   else
//   {
//      #if QCAN_SUPPORT_CAN_FD > 0

//      if (clFrameR.isExtended())
//      {
//         tsCanMsgFdT.MSGTYPE = PCAN_MESSAGE_EXTENDED;
//      } else
//      {
//         tsCanMsgFdT.MSGTYPE  = PCAN_MESSAGE_STANDARD;
//         tsCanMsgFdT.MSGTYPE |= PCAN_MESSAGE_FD;
//         tsCanMsgFdT.MSGTYPE |= PCAN_MESSAGE_BRS;
//      }

//      tsCanMsgFdT.ID = clFrameR.identifier();

//      tsCanMsgFdT.DLC= clFrameR.dlc();

//      for (slByteCntrT = 0; slByteCntrT < clFrameR.dataSize(); slByteCntrT++)
//      {
//         tsCanMsgFdT.DATA[slByteCntrT] = clFrameR.data(slByteCntrT);
//      }

//      ulStatusT = pclCpUsartP.pfnCAN_WriteFDP(uwPCanChannelP, &tsCanMsgFdT);
//      #else
//      ulStatusT = 0;
//      #endif
//   }


//   if (ulStatusT == PCAN_ERROR_OK)
//   {
//      clStatisticP.ulTrmCount++;
//      return eERROR_NONE;
//   }
//   else if (ulStatusT != (TPCANStatus)PCAN_ERROR_QRCVEMPTY)
//   {
//      qWarning() << "Fail to call CAN_Write(): " << QString::number(ulStatusT,16);
//      return eERROR_DEVICE;
//   }

   return eERROR_FIFO_TRM_FULL;

}
