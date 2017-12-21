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
// QCanInterfaceUsart()                                                        //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterfaceUsart::QCanInterfaceUsart(uint16_t uwDeviceNrV, QString clNameV)
{
   if (!pclCpUsartP.isAvailable())
   {
      qCritical() << "QCanInterfaceUsart(): PEAKBasic library is not available!";
   }

   clDeviceNameP = clNameV;
   uwDeviceNumberP = uwDeviceNrV;

   //----------------------------------------------------------------
   // setup PCAN Channel of this interface
   //
//   uwPCanChannelP = uwPCanChannelV;
//   uwPCanBitrateP = PCAN_BAUD_500K; // initial value
//   teCanModeP = eCAN_MODE_STOP;

   btConnectedP = false;
   btFdUsedP = false;
}

//----------------------------------------------------------------------------//
// ~QCanInterfaceUsart()                                                       //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterfaceUsart::~QCanInterfaceUsart()
{
   qDebug() << "QCanInterfaceUsart::~QCanInterfaceUsart()";

   if (pclCpUsartP.isAvailable())
   {
//      if (btConnectedP)
//      {
//         pclCpUsartP.pfnCAN_UninitializeP(uwPCanChannelP);
//      }
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
      tvStatusT = pclCpUsartP.CpUsartDriverInit(uwDeviceNumberP,&tsPortP,0);
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
   qDebug() << "QCanInterfaceUsart::read()";
   if (!pclCpUsartP.isAvailable())
   {
      return eERROR_LIBRARY;
   }

   //----------------------------------------------------------------
   // check channel have been connected
   //
   #if QCAN_SUPPORT_CAN_FD > 0
   if (btFdUsedP == true)
   {
      return readFD(clDataR);
   }
   #endif

   return readCAN(clDataR);
}

//----------------------------------------------------------------------------//
// readCAN()                                                                  //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterface::InterfaceError_e  QCanInterfaceUsart::readCAN(QByteArray &clDataR)
{
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
// readFD()                                                                   //
//                                                                            //
//----------------------------------------------------------------------------//
#if QCAN_SUPPORT_CAN_FD > 0
QCanInterface::InterfaceError_e  QCanInterfaceUsart::readFD(QByteArray &clDataR)
{
   qDebug() << "QCanInterfaceUsart::readFD()";

   TPCANStatus       ulStatusT;
   uint8_t           ubCntT;
   TPCANMsgFD        tsCanMsgT;
   TPCANTimestampFD  tsCanTimeStampT;
   uint32_t          ulMicroSecsT;
   QCanFrame         clCanFrameT;
   QCanFrameError    clErrFrameT;
   QCanTimeStamp     clTimeStampT;
   InterfaceError_e  clRetValueT = eERROR_NONE;

   //----------------------------------------------------------------
   // get next message from FIFO
   //
   ulStatusT = pclCpUsartP.pfnCAN_ReadFDP(uwPCanChannelP, &tsCanMsgT,
                                            &tsCanTimeStampT);


   //----------------------------------------------------------------
   // read message structure
   //
   if (ulStatusT == PCAN_ERROR_OK)
   {
      //--------------------------------------------------------
      // handle data depending on type
      //
      if((tsCanMsgT.MSGTYPE & PCAN_MESSAGE_STATUS) > 0)
      {
         //------------------------------------------------
         // this is a status message
         //
         clRetValueT = eERROR_FIFO_RCV_EMPTY;
      }
      else
      {
         //------------------------------------------------
         // this is a CAN message
         //
         if (tsCanMsgT.MSGTYPE & PCAN_MESSAGE_FD)
         {
            //----------------------------------------
            // ISO CAN FD frame with standard or
            // extended identifier
            //
            if (tsCanMsgT.MSGTYPE & PCAN_MESSAGE_EXTENDED)
            {
               clCanFrameT.setFrameFormat(QCanFrame::eFORMAT_FD_EXT);
            }
            else
            {
               clCanFrameT.setFrameFormat(QCanFrame::eFORMAT_FD_STD);
            }

            //----------------------------------------
            // Test for BRS bit
            //
            if (tsCanMsgT.MSGTYPE & PCAN_MESSAGE_BRS)
            {
               clCanFrameT.setBitrateSwitch();
            }

            //----------------------------------------
            // Test for ESI bit
            //
            if (tsCanMsgT.MSGTYPE & PCAN_MESSAGE_ESI)
            {
               clCanFrameT.setErrorStateIndicator();
            }
         }
         else
         {
            //----------------------------------------
            // Classical CAN frame with standard or
            // extended identifier
            //
            if (tsCanMsgT.MSGTYPE & PCAN_MESSAGE_EXTENDED)
            {
               clCanFrameT.setFrameFormat(QCanFrame::eFORMAT_CAN_EXT);
            }
            else
            {
               clCanFrameT.setFrameFormat(QCanFrame::eFORMAT_CAN_STD);
            }

            //----------------------------------------
            // Classical CAN remote frame
            //
            if (tsCanMsgT.MSGTYPE & PCAN_MESSAGE_RTR)
            {
               clCanFrameT.setRemote();
            }
         }

         //------------------------------------------------
         // copy the identifier
         //
         clCanFrameT.setIdentifier(tsCanMsgT.ID);

         //------------------------------------------------
         // copy the DLC
         //
         clCanFrameT.setDlc(tsCanMsgT.DLC);

         //------------------------------------------------
         // copy the data
         //
         for (ubCntT = 0; ubCntT < clCanFrameT.dataSize(); ubCntT++)
         {
            clCanFrameT.setData(ubCntT, tsCanMsgT.DATA[ubCntT]);
         }

         //------------------------------------------------
         // copy the time-stamp
         // the value is a multiple of 1 us and has a
         // total time span of 4294,9 secs
         //
         /*
         ulMicroSecsT = tsCanTimeStampT.millis * 1000;
         ulMicroSecsT = ulMicroSecsT + tsCanTimeStampT.micros;
         clTimeStampT.fromMicroSeconds(ulMicroSecsT);

         clCanFrameT.setTimeStamp(clTimeStampT);
         */

         //------------------------------------------------
         // increase statistic counter
         //
         clStatisticP.ulRcvCount++;

         //------------------------------------------------
         // copy the CAN frame to a byte array for transfer
         //
         clDataR = clCanFrameT.toByteArray();
      }
   }
   else
   {
      //--------------------------------------------------------
      // test for bus error
      //
      if ((ulStatusT & (TPCANStatus)PCAN_ERROR_ANYBUSERR) > 0)
      {
         setupErrorFrame(ulStatusT, clErrFrameT);
         //------------------------------------------------
         // copy the error frame to a byte array
         //
         clDataR = clErrFrameT.toByteArray();
      }

      //--------------------------------------------------------
      // the receive queue is empty
      //
      else if (ulStatusT == PCAN_ERROR_QRCVEMPTY)
      {
         clRetValueT = eERROR_FIFO_RCV_EMPTY;
      }
      else
      {
         clRetValueT = eERROR_DEVICE;
      }
   }

   return (clRetValueT);
}
#endif


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

//   //----------------------------------------------------------------
//   // reset device
//   //
//   if (pclCpUsartP.pfnCAN_ResetP(uwPCanChannelP) != PCAN_ERROR_OK)
//   {
//      return eERROR_DEVICE;
//   }

   //----------------------------------------------------------------
   // perform a hardware reset only if
   // it hase been initialised before
   //
   if (btConnectedP)
   {
//      pclCpUsartP.pfnCAN_UninitializeP(uwPCanChannelP);

//      if (pclCpUsartP.pfnCAN_InitializeP(uwPCanChannelP, uwPCanBitrateP, 0, 0, 0) != PCAN_ERROR_OK)
//      {
//         return eERROR_DEVICE;
//      }
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

   if (!pclCpUsartP.isAvailable())
   {
      tvStatusT = pclCpUsartP.CpUsartBitrate(&tsPortP,slNomBitRateV,slDatBitRateV);
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

    qDebug() << "QCanInterfaceUsart::setMode()";

//   //----------------------------------------------------------------
//   // check lib is available
//   //
//   if (!pclCpUsartP.isAvailable())
//   {
//      return eERROR_LIBRARY;
//   }

//   //----------------------------------------------------------------
//   // select mode
//   //
//   switch (teModeV)
//   {
//      case eCAN_MODE_START :

//         //---------------------------------------------------
//         // reset statistic values
//         //
//         clStatisticP.ulErrCount = 0;
//         clStatisticP.ulRcvCount = 0;
//         clStatisticP.ulTrmCount = 0;

//         ubValueBufT = 1;
//         if (pclCpUsartP.pfnCAN_SetValueP(uwPCanChannelP, PCAN_BUSOFF_AUTORESET,&ubValueBufT,sizeof(ubValueBufT)))
//         {
//            qWarning() << "WARNING: Fail to set AutoReset of Device!";
//         }
//         teCanModeP = eCAN_MODE_START;
//         break;

//      case eCAN_MODE_STOP :
//         teCanModeP = eCAN_MODE_STOP;
//         break;

//      default :
//         return eERROR_MODE;
//         break;
//   }

   return eERROR_NONE;
}

////----------------------------------------------------------------------------//
//// setupErrorFrame()                                                           //
////                                                                            //
////----------------------------------------------------------------------------//
//void QCanInterfaceUsart::setupErrorFrame(TPCANStatus ulStatusV,
//                                        QCanFrameError &clFrameR)
//{

//   //---------------------------------------------------------
//   // set frame type and the bus status
//   //
//   clFrameR.setErrorType(QCanFrameError::eERROR_TYPE_NONE);

//   switch (ulStatusV)
//   {
//      case PCAN_ERROR_BUSLIGHT :
//         clFrameR.setErrorState(eCAN_STATE_BUS_WARN);
//         break;
//      case PCAN_ERROR_BUSWARNING :
//         clFrameR.setErrorState(eCAN_STATE_BUS_WARN);
//         break;
//      case PCAN_ERROR_BUSPASSIVE :
//         clFrameR.setErrorState(eCAN_STATE_BUS_PASSIVE);
//         break;
//      case PCAN_ERROR_BUSOFF :
//         clFrameR.setErrorState(eCAN_STATE_BUS_OFF);
//         break;

//      default :
//         clFrameR.setErrorState(eCAN_STATE_BUS_ACTIVE);
//         break;
//   }

//}


//----------------------------------------------------------------------------//
// statistic()                                                                //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterface::InterfaceError_e	QCanInterfaceUsart::statistic(QCanStatistic_ts &clStatisticR)
{
   //! \todo

   clStatisticR.ulErrCount = 0;

   return(eERROR_NONE);
}


//----------------------------------------------------------------------------//
// supportedFeatures()                                                        //
//                                                                            //
//----------------------------------------------------------------------------//
uint32_t QCanInterfaceUsart::supportedFeatures()
{
   qDebug() << "QCanInterfaceUsart::supportedFeatures()";

   uint32_t ulFeaturesT = 0;
   #if QCAN_SUPPORT_CAN_FD > 0
   uint32_t ulBufferT = 0;
   #endif
   if(pclCpUsartP.isAvailable())
   {

      ulFeaturesT = QCAN_IF_SUPPORT_LISTEN_ONLY;

      #if QCAN_SUPPORT_CAN_FD > 0
      TPCANStatus tsStatusT = pclCpUsartP.pfnCAN_GetValueP(uwPCanChannelP, PCAN_CHANNEL_FEATURES, (void*)&ulBufferT, sizeof(ulBufferT));
      if (tsStatusT != PCAN_ERROR_OK)
      {
         qWarning() << QString("QCanInterfaceUsart::supportedFeatures(0x" +QString::number(uwPCanChannelP,16)+")") << "PCAN_CHANNEL_FEATURES fail with error:" << pclCpUsartP.formatedError(tsStatusT);
      }
      qWarning() << QString("QCanInterfaceUsart::supportedFeatures(0x" +QString::number(uwPCanChannelP,16)+")") << "PCAN_CHANNEL_FEATURES:" << QString::number(ulBufferT,16) << "[hex]";

      if (ulBufferT & FEATURE_FD_CAPABLE)
      {
         ulFeaturesT += QCAN_IF_SUPPORT_CAN_FD;
      }
      #endif
   }

   return(ulFeaturesT);
}


//----------------------------------------------------------------------------//
// write()                                                                    //
//                                                                            //
//----------------------------------------------------------------------------//
QCanInterface::InterfaceError_e	QCanInterfaceUsart::write(const QCanFrame &clFrameR)
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
