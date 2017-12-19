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
QCanInterfaceUsart::QCanInterfaceUsart(QString clNameV)
{
   if (!pclCpUsartP.isAvailable())
   {
      qCritical() << "QCanInterfaceUsart(): PEAKBasic library is not available!";
   }

   clNameP = clNameV;
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
//   uint8_t          ubValueT;
//   TPCANStatus      tsStatusT;
   qDebug() << QString("QCanInterfaceUsart::connect()...");

   //----------------------------------------------------------------
   //
   //
   if (pclCpUsartP.isAvailable())
   {
      if (pclCpUsartP.open(clNameP) == 0)
      {
         btConnectedP = true;
         teReturnT = eERROR_NONE;
      }

//      //--------------------------------------------------------
//      // get channel condition
//      //
//      tsStatusT = pclCpUsartP.pfnCAN_GetValueP(uwPCanChannelP, PCAN_CHANNEL_CONDITION, (void*)&ubValueT, 1);
//      if (tsStatusT != PCAN_ERROR_OK)
//      {
//         qWarning() << QString("QCanInterfaceUsart::connect(0x" +QString::number(uwPCanChannelP,16)+")") << "fail with error:" << pclCpUsartP.formatedError(tsStatusT);
//      }

//      //--------------------------------------------------------
//      // channel is not available, quit here
//      //
//      else if (ubValueT == PCAN_CHANNEL_UNAVAILABLE)
//      {
//         qDebug() << QString("QCanInterfaceUsart::connect(0x" +QString::number(uwPCanChannelP,16)+")") << " is not available " << pclCpUsartP.formatedError(tsStatusT);
//         teReturnT = eERROR_CHANNEL;
//      }

//      //--------------------------------------------------------
//      // channel is ocupied, quit here
//      //
//      else if (ubValueT == 0)
//      {
//         qWarning() << QString("QCanInterfaceUsart::connect(0x" +QString::number(uwPCanChannelP,16)+")") << " is ouccupied " << pclCpUsartP.formatedError(tsStatusT);
//         teReturnT = eERROR_USED;
//      }

//      //--------------------------------------------------------
//      // channel is available, get other parameters
//      //
//      else
//      {
//         //-------------------------------------------------
//         // release can channel before init it
//         //
//         if (btConnectedP)
//         {
//            pclCpUsartP.pfnCAN_UninitializeP(uwPCanChannelP);
//            btConnectedP = false;
//         }

//         //-------------------------------------------------
//         // initialise selected channel it again
//         //
//         tsStatusT = pclCpUsartP.pfnCAN_InitializeP(uwPCanChannelP, uwPCanBitrateP, 0, 0, 0);

//         if (tsStatusT != PCAN_ERROR_OK)
//         {
//            qCritical() << QString("QCanInterfaceUsart::connect(0x" +QString::number(uwPCanChannelP,16)+")") << "fail with error:" << pclCpUsartP.formatedError(tsStatusT);
//            teReturnT = eERROR_USED;
//         }

//         else
//         {
//            btConnectedP = true;
//            teReturnT = eERROR_NONE;
//         }
//      }
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
   InterfaceError_e teReturnT = eERROR_LIBRARY;

   if (pclCpUsartP.isAvailable())
   {
      if (pclCpUsartP.close() == 0)
      {
         btConnectedP = false;
         teReturnT = eERROR_NONE;
      }

//      TPCANStatus tsStatusT = pclCpUsartP.pfnCAN_UninitializeP(uwPCanChannelP);
//      if (tsStatusT == PCAN_ERROR_OK)
//      {
//         btConnectedP = false;
//         return eERROR_NONE;
//      }
//      qWarning() << QString("QCanInterfaceUsart::disconnect(0x" +QString::number(uwPCanChannelP,16)+")") << "fail with error:" << pclCpUsartP.formatedError(tsStatusT);
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
      return clNameP;
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
QCanInterface::InterfaceError_e QCanInterfaceUsart::setBitrate( int32_t slNomBitRateV,
                                                               int32_t slDatBitRateV)
{
   qDebug() << "QCanInterfaceUsart::setBitrate()";

   if (!pclCpUsartP.isAvailable())
   {
      return eERROR_LIBRARY;
   }

//   WORD uwBtr0Btr1T = 0;
//   TPCANStatus ulStatusT;
//   #if QCAN_SUPPORT_CAN_FD > 0
//   QString clTxtBitrateNomT;
//   QString clTxtBitrateDataT;
//   QByteArray clTxtBitrateT ;
//   #endif
//   //----------------------------------------------------------------
//   // Check bit-rate value
//   //
//   if (slNomBitRateV >= eCAN_BITRATE_AUTO)
//   {
//      // maybe we get a value in Hz, normalise it to kHz
//      slNomBitRateV = slNomBitRateV / 1000;
//   }

//   #if QCAN_SUPPORT_CAN_FD > 0
//   //----------------------------------------------------------------
//   // Check data bit rate  value for CAN-FD
//   //
//   if (slDatBitRateV != eCAN_BITRATE_NONE)
//   {
//      //--------------------------------------------------------
//      // FD Bit-rate: all settings for 80 MHz clock
//      //

//      //--------------------------------------------------------
//      // select corresponding PEAK configuration for
//      // nominal bit rate
//      //
//      switch(slNomBitRateV)
//      {
//         case eCAN_BITRATE_125K:
//            clTxtBitrateNomT = "f_clock_mhz=80, nom_brp=2, nom_tseg1=255, nom_tseg2=64, nom_sjw=64";
//            break;

//         case eCAN_BITRATE_250K:
//            clTxtBitrateNomT = "f_clock_mhz=80, nom_brp=2, nom_tseg1=127, nom_tseg2=32, nom_sjw=32";
//            break;

//         case eCAN_BITRATE_500K:
//            clTxtBitrateNomT = "f_clock_mhz=80, nom_brp=2, nom_tseg1=63, nom_tseg2=16, nom_sjw=16";
//            break;

//         case eCAN_BITRATE_1M:
//            clTxtBitrateNomT = "f_clock_mhz=80, nom_brp=2, nom_tseg1=31, nom_tseg2=8, nom_sjw=8";
//            break;

//         default:
//            return eERROR_BITRATE;
//            break;
//      }

//      //--------------------------------------------------------
//      // select corresponding PEAK configuration for
//      // data bit rate
//      //
//      slDatBitRateV = slDatBitRateV / 1000000;
//      switch(slDatBitRateV)
//      {
//         case 1:     // 1 MBit/s
//            clTxtBitrateDataT = ", data_brp=2, data_tseg1=31, data_tseg2=8, data_sjw=8";
//            break;

//         case 2:     // 2 MBit/s
//            clTxtBitrateDataT = ", data_brp=2, data_tseg1=15, data_tseg2=4, data_sjw=4";
//            break;

//         case 4:     // 4 MBit/s
//            clTxtBitrateDataT = ", data_brp=2, data_tseg1=7, data_tseg2=2, data_sjw=2";
//            break;

//         default:
//            return eERROR_BITRATE;
//            break;
//      }

//      clTxtBitrateNomT.append(clTxtBitrateDataT);
//      clTxtBitrateT = clTxtBitrateNomT.toUtf8();
//   }
//   else
//   #endif
//   {

//      //----------------------------------------------------------------
//      // select corresponding PEAK baud rate value
//      //
//      switch(slNomBitRateV)
//      {
//         // value from CANpie enumeration
//         case eCAN_BITRATE_10K:
//            uwBtr0Btr1T = PCAN_BAUD_10K;
//            break;
//         case eCAN_BITRATE_20K:
//            uwBtr0Btr1T = PCAN_BAUD_20K;
//            break;
//         case eCAN_BITRATE_50K:
//            uwBtr0Btr1T = PCAN_BAUD_50K;
//            break;
//         case eCAN_BITRATE_100K:
//            uwBtr0Btr1T = PCAN_BAUD_100K;
//            break;
//         case eCAN_BITRATE_125K:
//            uwBtr0Btr1T = PCAN_BAUD_125K;
//            break;
//         case eCAN_BITRATE_250K:
//            uwBtr0Btr1T = PCAN_BAUD_250K;
//            break;
//         case eCAN_BITRATE_500K:
//            uwBtr0Btr1T = PCAN_BAUD_500K;
//            break;
//         case eCAN_BITRATE_800K:
//            uwBtr0Btr1T = PCAN_BAUD_800K;
//            break;
//         case eCAN_BITRATE_1M:
//            uwBtr0Btr1T = PCAN_BAUD_1M;
//            break;

//         // value normalized to kHz
//         case 10:
//            uwBtr0Btr1T = PCAN_BAUD_10K;
//            break;
//         case 20:
//            uwBtr0Btr1T = PCAN_BAUD_20K;
//            break;
//         case 50:
//            uwBtr0Btr1T = PCAN_BAUD_50K;
//            break;
//         case 100:
//            uwBtr0Btr1T = PCAN_BAUD_100K;
//            break;
//         case 125:
//            uwBtr0Btr1T = PCAN_BAUD_125K;
//            break;
//         case 250:
//            uwBtr0Btr1T = PCAN_BAUD_250K;
//            break;
//         case 500:
//            uwBtr0Btr1T = PCAN_BAUD_500K;
//            break;
//         case 800:
//            uwBtr0Btr1T = PCAN_BAUD_800K;
//            break;
//         case 1000:
//            uwBtr0Btr1T = PCAN_BAUD_1M;
//            break;

//         default:
//            return eERROR_BITRATE;
//            break;
//      }
//   }

//   //----------------------------------------------------------------
//   // perform releasing of CAN Interface
//   //
//   pclCpUsartP.pfnCAN_UninitializeP(uwPCanChannelP);

//   if (slDatBitRateV != eCAN_BITRATE_NONE)
//   {

//      qDebug() << QString("QCanInterfaceUsart::setBitrate(0x" +QString::number(uwPCanChannelP,16)+")") << " : FD Mode with bitrate adapting";

//      #if QCAN_SUPPORT_CAN_FD > 0
//      uint8_t ubValueBufT = PCAN_PARAMETER_ON;
//      if (pclCpUsartP.pfnCAN_SetValueP(uwPCanChannelP,PCAN_BITRATE_ADAPTING,&ubValueBufT,sizeof(ubValueBufT)))
//      {
//         qWarning() << "WARNING: Fail to set adaptive bitrate!";
//      }

//      ulStatusT = pclCpUsartP.pfnCAN_InitializeFDP(uwPCanChannelP, clTxtBitrateT.data());
//      btFdUsedP = true;

//      #else
//      ulStatusT = PCAN_ERROR_ILLPARAMVAL;
//      #endif
//   }
//   else
//   {
//      uwPCanBitrateP = uwBtr0Btr1T;
//      qDebug() << QString("QCanInterfaceUsart::setBitrate(0x" +QString::number(uwPCanChannelP,16)+  ", " + QString::number(uwPCanBitrateP,10)+ ")") << " : Standard Mode";
//      ulStatusT = pclCpUsartP.pfnCAN_InitializeP(uwPCanChannelP, uwPCanBitrateP, 0, 0, 0);
//      btFdUsedP = false;
//   }

//   if (ulStatusT != PCAN_ERROR_OK)
//   {
//      // get default description string of error code
//      qCritical() << pclCpUsartP.formatedError(ulStatusT);

//      return eERROR_DEVICE;
//   }

   return eERROR_NONE;
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
