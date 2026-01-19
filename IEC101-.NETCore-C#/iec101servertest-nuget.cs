/******************************************************************************
*
* (c) 2026 by FreyrSCADA Embedded Solution Pvt Ltd
*
********************************************************************************
*
* Disclaimer: This program is an example and should be used as such.
*             If you wish to use this program or parts of it in your application,
*             you must validate the code yourself.  FreyrSCADA Embedded Solution Pvt Ltd
*             can not be held responsible for the correct functioning
*             or coding of this example
*******************************************************************************/

/*****************************************************************************/
/*! \file       iec101servertest-nuget.cs
 *  \brief      C# Source code file, IEC 60870-5-101 Server library test program for https://www.nuget.org/packages/iec60870_5_101/
 *
 *  \par        FreyrSCADA Embedded Solution Pvt Ltd
 *              Email   : tech.support@freyrscada.com
 */
/*****************************************************************************/

/*! \brief - in a loop simulate update - for particular IOA , value changes - generates a event  */
#define SIMULATE_UPDATE 

/*! \brief - Enable traffic flags to show transmit and receive signal  */
#define VIEW_TRAFFIC 

using System;
using System.Threading;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace iec101test
{
    class Program
    {

        [System.Runtime.InteropServices.StructLayout(System.Runtime.InteropServices.LayoutKind.Explicit)]
        struct SingleInt32Union
        {
            [System.Runtime.InteropServices.FieldOffset(0)]
            public float f;
            [System.Runtime.InteropServices.FieldOffset(0)]
            public int i;
        }

/******************************************************************************
* Print information
******************************************************************************/
        static void vPrintDataInformation(ref iec60870_5_101.iec101types.sIEC101DataAttributeID psPrintID, ref iec60870_5_101.iec101types.sIEC101DataAttributeData psData)
        {

            Console.WriteLine(" Data Link Address " + psPrintID.u16DataLinkAddress);
            Console.WriteLine(" Station Address " + psPrintID.u16CommonAddress);


            Console.WriteLine("Data Attribute ID is  {0:D} IOA {1:D} ", psPrintID.eTypeID, psPrintID.u32IOA);
            Console.WriteLine("Data is  datatype->{0:D} datasize->{1:D}  ", psData.eDataType, psData.eDataSize);


            if (psData.tQuality != (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.GD)
            {

                /* Now for the Status */
                if ((psData.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.IV) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.IV)
                {
                    Console.WriteLine("IEC_INVALID_FLAG");
                }

                if ((psData.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.NT) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.NT)
                {
                    Console.WriteLine("IEC_NONTOPICAL_FLAG");
                }

                if ((psData.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.SB) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.SB)
                {
                    Console.WriteLine("IEC_SUBSTITUTED_FLAG");
                }

                if ((psData.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.BL) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.BL)
                {
                    Console.WriteLine("IEC_BLOCKED_FLAG");
                }

            }

            switch (psData.eDataType)
            {
                case iec60870_5_101.tgtcommon.eDataTypes.SINGLE_POINT_DATA:
                case iec60870_5_101.tgtcommon.eDataTypes.DOUBLE_POINT_DATA:
                case iec60870_5_101.tgtcommon.eDataTypes.UNSIGNED_BYTE_DATA:
                    Console.WriteLine("Data : {0:D}", System.Runtime.InteropServices.Marshal.ReadByte(psData.pvData));
                    break;

                case iec60870_5_101.tgtcommon.eDataTypes.SIGNED_BYTE_DATA:
                    sbyte i8data = unchecked((sbyte)System.Runtime.InteropServices.Marshal.ReadByte(psData.pvData));
                    Console.WriteLine(i8data);
                    break;

                case iec60870_5_101.tgtcommon.eDataTypes.UNSIGNED_WORD_DATA:
                    ushort u16data = unchecked((ushort)System.Runtime.InteropServices.Marshal.ReadInt16(psData.pvData));
                    Console.WriteLine(u16data);
                    break;

                case iec60870_5_101.tgtcommon.eDataTypes.SIGNED_WORD_DATA:
                    Console.WriteLine("Data : {0:D}", System.Runtime.InteropServices.Marshal.ReadInt16(psData.pvData));
                    break;

                case iec60870_5_101.tgtcommon.eDataTypes.UNSIGNED_DWORD_DATA:
                    uint u32data = unchecked((uint)System.Runtime.InteropServices.Marshal.ReadInt32(psData.pvData));
                    Console.WriteLine(u32data);
                    break;

                case iec60870_5_101.tgtcommon.eDataTypes.SIGNED_DWORD_DATA:
                    Console.WriteLine("Data : {0:D}", System.Runtime.InteropServices.Marshal.ReadInt32(psData.pvData));
                    break;

                case iec60870_5_101.tgtcommon.eDataTypes.FLOAT32_DATA:
                    SingleInt32Union f32data;
                    f32data.f = 0;
                    f32data.i = System.Runtime.InteropServices.Marshal.ReadInt32(psData.pvData);
                   // Console.WriteLine("Data : {0:F}", f32data.f);
                    Console.WriteLine(string.Format("Data : {0:0.00#}", f32data.f));
                    break;

                default:
                    break;
            }


            if (psData.sTimeStamp.u8Seconds != 0)
            {
                Console.WriteLine("Date : {0:D}-{1:D}-{2:D}  DOW -{3:D}", psData.sTimeStamp.u8Day, psData.sTimeStamp.u8Month, psData.sTimeStamp.u16Year, psData.sTimeStamp.u8DayoftheWeek);
                Console.WriteLine("Time : {0:D}:{1:D2}:{2:D2}:{3:D4}", psData.sTimeStamp.u8Hour, psData.sTimeStamp.u8Minute, psData.sTimeStamp.u8Seconds, psData.sTimeStamp.u16MilliSeconds);
            }
        }


        /******************************************************************************
        * Read callback
        ******************************************************************************/
        static short cbRead(ushort u16ObjectId, ref iec60870_5_101.iec101types.sIEC101DataAttributeID ptReadID, ref iec60870_5_101.iec101types.sIEC101DataAttributeData ptReadValue, ref iec60870_5_101.iec101types.sIEC101ReadParameters ptReadParams, ref short ptErrorValue)
        {
            Console.WriteLine("\n\r\n cbRead() called");
            Console.WriteLine("Server ID " + u16ObjectId);
            vPrintDataInformation(ref ptReadID, ref ptReadValue);
            Console.WriteLine("Orginator Address " + ptReadParams.u8OriginatorAddress);
            return (short)iec60870_5_101.tgterrorcodes.eTgtErrorCodes.EC_NONE;
        }

        /******************************************************************************
        * Write callback
        ******************************************************************************/
        static short cbWrite(ushort u16ObjectId, ref iec60870_5_101.iec101types.sIEC101DataAttributeID ptWriteID, ref iec60870_5_101.iec101types.sIEC101DataAttributeData ptWriteValue, ref iec60870_5_101.iec101types.sIEC101WriteParameters ptWriteParams, ref short ptErrorValue)
        {
            Console.WriteLine("\n\r\n cbWrite() called-clock sync command from iec101 client");
            Console.WriteLine("Server ID " + u16ObjectId);
            vPrintDataInformation(ref ptWriteID, ref ptWriteValue);
            Console.WriteLine("Orginator Address " + ptWriteParams.u8OriginatorAddress);
            return (short)iec60870_5_101.tgterrorcodes.eTgtErrorCodes.EC_NONE;
        }


        /******************************************************************************
        * Select callback
        ******************************************************************************/
        static short cbSelect(ushort u16ObjectId, ref iec60870_5_101.iec101types.sIEC101DataAttributeID ptSelectID, ref iec60870_5_101.iec101types.sIEC101DataAttributeData ptSelectValue, ref iec60870_5_101.iec101types.sIEC101CommandParameters ptSelectParams, ref short ptErrorValue)
        {
            Console.WriteLine("\n\r\n cbSelect() called");
            Console.WriteLine("Server ID " + u16ObjectId);
            vPrintDataInformation(ref ptSelectID, ref ptSelectValue);
            Console.WriteLine("Orginator Address " + ptSelectParams.u8OriginatorAddress);
            Console.WriteLine("Qualifier " + ptSelectParams.eQOCQU);
            Console.WriteLine("Pulse Duration " + ptSelectParams.u32PulseDuration);

            return (short)iec60870_5_101.tgterrorcodes.eTgtErrorCodes.EC_NONE;

        }

        /******************************************************************************
        * Operate callback
        ******************************************************************************/
        static short cbOperate(ushort u16ObjectId, ref iec60870_5_101.iec101types.sIEC101DataAttributeID ptOperateID, ref iec60870_5_101.iec101types.sIEC101DataAttributeData ptOperateValue, ref iec60870_5_101.iec101types.sIEC101CommandParameters ptOperateParams, ref short ptErrorValue)
        {
            Console.WriteLine("\n\r\n cbOperate() called");
            Console.WriteLine("Server ID " + u16ObjectId);
            vPrintDataInformation(ref ptOperateID, ref ptOperateValue);
            Console.WriteLine("orginator Address " + ptOperateParams.u8OriginatorAddress);
            Console.WriteLine("Qualifier " + ptOperateParams.eQOCQU);
            Console.WriteLine("Pulse Duration " + ptOperateParams.u32PulseDuration);

            return (short)iec60870_5_101.tgterrorcodes.eTgtErrorCodes.EC_NONE;
        }

        /******************************************************************************
        * Cancel callback
        ******************************************************************************/
        static short cbCancel(ushort u16ObjectId, iec60870_5_101.iec60870common.eOperationFlag eOperation, ref iec60870_5_101.iec101types.sIEC101DataAttributeID ptCancelID, ref iec60870_5_101.iec101types.sIEC101DataAttributeData ptCancelValue, ref iec60870_5_101.iec101types.sIEC101CommandParameters ptCancelParams, ref short ptErrorValue)
        {
            Console.WriteLine("\n\r\n cbCancel() called");
            Console.WriteLine("Server ID " + u16ObjectId);

            if (eOperation == iec60870_5_101.iec60870common.eOperationFlag.OPERATE)
                Console.WriteLine("Operate operation to be cancel");

            if (eOperation == iec60870_5_101.iec60870common.eOperationFlag.SELECT)
                Console.WriteLine("Select operation to cancel");

            vPrintDataInformation(ref ptCancelID, ref ptCancelValue);

            Console.WriteLine("Qualifier " + ptCancelParams.eQOCQU);
            Console.WriteLine("Pulse Duration " + ptCancelParams.u32PulseDuration);
            Console.WriteLine("Orginator Address " + ptCancelParams.u8OriginatorAddress);

            return (short)iec60870_5_101.tgterrorcodes.eTgtErrorCodes.EC_NONE;
        }

        /******************************************************************************
        * Operate pulse end callback
        ******************************************************************************/
        static short cbpulseend(ushort u16ObjectId, ref iec60870_5_101.iec101types.sIEC101DataAttributeID ptOperateID, ref iec60870_5_101.iec101types.sIEC101DataAttributeData ptOperateValue, ref iec60870_5_101.iec101types.sIEC101CommandParameters ptOperateParams, ref short ptErrorValue)
        {
            Console.WriteLine("\n\r\n cbOperatepulse end() called");
            Console.WriteLine("Server ID " + u16ObjectId);
            vPrintDataInformation(ref ptOperateID, ref ptOperateValue);
            Console.WriteLine("orginator Address " + ptOperateParams.u8OriginatorAddress);
            Console.WriteLine("Qualifier " + ptOperateParams.eQOCQU);
            Console.WriteLine("pulse Duration " + ptOperateParams.u32PulseDuration);


            return (short)iec60870_5_101.tgterrorcodes.eTgtErrorCodes.EC_NONE;
        }

        /******************************************************************************
        * Parameteract callback
        ******************************************************************************/
        static short cbParameterAct(ushort u16ObjectId, ref iec60870_5_101.iec101types.sIEC101DataAttributeID ptOperateID, ref iec60870_5_101.iec101types.sIEC101DataAttributeData ptOperateValue, ref iec60870_5_101.iec101types.sIEC101ParameterActParameters ptParameterActParams, ref short ptErrorValue)
        {
            Console.WriteLine("\n\r\n cbParameterAct() called");
            Console.WriteLine("Server ID " + u16ObjectId);
            vPrintDataInformation(ref ptOperateID, ref ptOperateValue);
            Console.WriteLine("Orginator Address " + ptParameterActParams.u8OriginatorAddress);
            Console.WriteLine("Qualifier of parameter activation/kind of parameter " + ptParameterActParams.u8QPA);
            return (short)iec60870_5_101.tgterrorcodes.eTgtErrorCodes.EC_NONE;
        }

        /******************************************************************************
        * Freeze Callback
        ******************************************************************************/
        static short cbFreeze( ushort u16ObjectId, iec60870_5_101.iec60870common.eCounterFreezeFlags eCounterFreeze, ref iec60870_5_101.iec101types.sIEC101DataAttributeID ptFreezeID, ref iec60870_5_101.iec101types.sIEC101DataAttributeData ptFreezeValue, ref iec60870_5_101.iec101types.sIEC101WriteParameters ptFreezeCmdParams, ref short ptErrorValue)
        {
            Console.WriteLine("\n\r\n cbFreeze() called");
            Console.WriteLine("Server ID " + u16ObjectId);
            Console.WriteLine("Command ID " + ptFreezeID.eTypeID);
            Console.WriteLine("COT " + ptFreezeCmdParams.eCause);
            Console.WriteLine("Orginator Address " + ptFreezeCmdParams.u8OriginatorAddress);

            return (short)iec60870_5_101.tgterrorcodes.eTgtErrorCodes.EC_NONE;
        }


        /******************************************************************************
        * Debug callback
        ******************************************************************************/
        static short cbDebug(ushort u16ObjectId, ref iec60870_5_101.iec101types.sIEC101DebugData ptDebugData, ref short ptErrorValue)
        {
            //Console.WriteLine("\r\n cbDebug() called");
            Console.Write("\r\nServer ID :{0:D} ", u16ObjectId);

            Console.Write(" {0:D}-{1:D}-{2:D}", ptDebugData.sTimeStamp.u8Day, ptDebugData.sTimeStamp.u8Month, ptDebugData.sTimeStamp.u16Year);

            Console.Write(" {0:D}:{1:D2}:{2:D2}", ptDebugData.sTimeStamp.u8Hour, ptDebugData.sTimeStamp.u8Minute, ptDebugData.sTimeStamp.u8Seconds);

            if ((ptDebugData.u32DebugOptions & (uint)iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_RX) == (uint)iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_RX)
            {

                Console.Write(" Rx " + " Serial port " + ptDebugData.u16ComportNumber + " <- ");

                for (ushort i = 0; i < ptDebugData.u16RxCount; i++)
                    Console.Write("{0:X2} ", ptDebugData.au8RxData[i]);
                
            }

            if ((ptDebugData.u32DebugOptions & (uint)iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_TX) == (uint)iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_TX)
            {
                Console.Write(" Tx " + " Serial port " + ptDebugData.u16ComportNumber + " -> ");

                for (ushort i = 0; i < ptDebugData.u16TxCount; i++)
                    Console.Write("{0:X2} ", ptDebugData.au8TxData[i]);
               
            }

            if ((ptDebugData.u32DebugOptions & (uint)iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_ERROR) == (uint)iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_ERROR)
            {
                Console.WriteLine("Error message " + ptDebugData.au8ErrorMessage);
                Console.WriteLine("ErrorCode " + ptDebugData.i16ErrorCode);
                Console.WriteLine("ErrorValue " + ptDebugData.tErrorvalue);
            }

            if ((ptDebugData.u32DebugOptions & (uint)iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_WARNING) == (uint)iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_WARNING)
            {
                Console.WriteLine("Warning message " + ptDebugData.au8WarningMessage);
                Console.WriteLine("ErrorCode " + ptDebugData.i16ErrorCode);
                Console.WriteLine("ErrorValue " + ptDebugData.tErrorvalue);
            }

            return (short)iec60870_5_101.tgterrorcodes.eTgtErrorCodes.EC_NONE;
        }

        /******************************************************************************
        * Error code - Print information
        ******************************************************************************/
        static string errorcodestring(short errorcode)
        {
            iec60870_5_101.iec101types.sIEC101ErrorCode sIEC101ErrorCodeDes;
            sIEC101ErrorCodeDes = new iec60870_5_101.iec101types.sIEC101ErrorCode();

            sIEC101ErrorCodeDes.iErrorCode = errorcode;
            
            iec60870_5_101.iec101api.IEC101ErrorCodeString( ref sIEC101ErrorCodeDes);

            string returnmessage = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(sIEC101ErrorCodeDes.LongDes);

            return returnmessage;
        }

        /******************************************************************************
        * Error value - Print information
        ******************************************************************************/
        static string  errorvaluestring(short errorvalue)
        {
            iec60870_5_101.iec101types.sIEC101ErrorValue sIEC101ErrorValueDes;
            sIEC101ErrorValueDes = new iec60870_5_101.iec101types.sIEC101ErrorValue(); 

             sIEC101ErrorValueDes.iErrorValue = errorvalue;

             iec60870_5_101.iec101api.IEC101ErrorValueString(ref sIEC101ErrorValueDes);

             string returnmessage = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(sIEC101ErrorValueDes.LongDes);

             return returnmessage;
        }

        /******************************************************************************
        * main()
        ******************************************************************************/
        static void Main(string[] args)
        {
            System.DateTime date;                   // update date and time structute
            System.IntPtr iec101serverhandle;       // IEC 60870-5-101 Server object
            iec60870_5_101.iec101types.sIEC101Parameters sParameters;    // IEC101 Server object callback paramters 

            System.Console.WriteLine(" \n\t\t**** FreyrSCADA - IEC 60870-5-101 Server Library Test ****");

            try
            {
                if (String.Compare(System.Runtime.InteropServices.Marshal.PtrToStringAnsi(iec60870_5_101.iec101api.IEC101GetLibraryVersion()), iec60870_5_101.iec101api.IEC101_VERSION, true) != 0)
                {
                    System.Console.WriteLine("\r\nError: Version Number Mismatch");
                    System.Console.WriteLine("Library Version is : {0:D}", System.Runtime.InteropServices.Marshal.PtrToStringAnsi(iec60870_5_101.iec101api.IEC101GetLibraryVersion()));
                    System.Console.WriteLine("The Version used is : {0:D}", iec60870_5_101.iec101api.IEC101_VERSION);
                    System.Console.Write("Press <Enter> to exit... ");
                    while (Console.ReadKey().Key != ConsoleKey.Enter) { }
                    return;
                }
            }
            catch (DllNotFoundException e)
            {
                System.Console.WriteLine(e.ToString());
                System.Console.Write("Press <Enter> to exit... ");
                while (Console.ReadKey().Key != ConsoleKey.Enter) { }
                return;
            }

            System.Console.WriteLine("Library Version is : {0:D}", System.Runtime.InteropServices.Marshal.PtrToStringAnsi(iec60870_5_101.iec101api.IEC101GetLibraryVersion()));
            System.Console.WriteLine("Library Build on   : {0:D}", System.Runtime.InteropServices.Marshal.PtrToStringAnsi(iec60870_5_101.iec101api.IEC101GetLibraryBuildTime()));
            System.Console.WriteLine("Library Licence Information  : {0:D}", System.Runtime.InteropServices.Marshal.PtrToStringAnsi(iec60870_5_101.iec101api.IEC101GetLibraryLicenseInfo()));

            iec101serverhandle = System.IntPtr.Zero;
            sParameters = new iec60870_5_101.iec101types.sIEC101Parameters();

            // Initialize IEC 60870-5-101 Server object parameters
            sParameters.eAppFlag = iec60870_5_101.tgtcommon.eApplicationFlag.APP_SERVER;                                          // This is a IEC101 Server
            sParameters.ptReadCallback = new iec60870_5_101.iec101types.IEC101ReadCallback(cbRead);                                 // Read Callback
            sParameters.ptWriteCallback = new iec60870_5_101.iec101types.IEC101WriteCallback(cbWrite);                              // Write Callback
            sParameters.ptUpdateCallback = null;                                                                // Update Callback
            sParameters.ptSelectCallback = new iec60870_5_101.iec101types.IEC101ControlSelectCallback(cbSelect);                    // Select commands
            sParameters.ptOperateCallback = new iec60870_5_101.iec101types.IEC101ControlOperateCallback(cbOperate);                 // Operate commands
            sParameters.ptCancelCallback = new iec60870_5_101.iec101types.IEC101ControlCancelCallback(cbCancel);                    // Cancel commands
            sParameters.ptFreezeCallback = new iec60870_5_101.iec101types.IEC101ControlFreezeCallback(cbFreeze);                    // Freeze Callback
            sParameters.ptPulseEndActTermCallback = new iec60870_5_101.iec101types.IEC101ControlPulseEndActTermCallback(cbpulseend);      // pulse end callback
            sParameters.ptParameterActCallback = new iec60870_5_101.iec101types.IEC101ParameterActCallback(cbParameterAct);         // Parameter activation callback
            sParameters.ptDebugCallback = new iec60870_5_101.iec101types.IEC101DebugMessageCallback(cbDebug);                       // Debug Callback
            sParameters.ptClientStatusCallback = null;                                                          // server connection status callback
            sParameters.ptDirectoryCallback = null;                                                             // server Directory callback
            sParameters.u16ObjectId = 1;                                                                        // Server ID which uded in callbacks to identify the iec 104 server object         
            sParameters.u32Options = 0;
            short eErrorCode = 0;                                                                                 // API Function return error paramter
            short ptErrorValue = 0;                                                                             // API Function return addtional error paramter


            do
            {
                // Create a server object
                iec101serverhandle = iec60870_5_101.iec101api.IEC101Create(ref sParameters, ref eErrorCode, ref ptErrorValue);
                if (iec101serverhandle == System.IntPtr.Zero)
                {
                    System.Console.WriteLine("IEC 60870-5-101 Library API Function - IEC101Create failed");
					System.Console.WriteLine("ErrorCode {0:D}: {1}", eErrorCode, errorcodestring(eErrorCode));
                    System.Console.WriteLine("ErrorValue {0:D}: {1}", ptErrorValue, errorvaluestring(ptErrorValue));
                    break;
                }

                // Server load configuration - communication and protocol configuration parameters
                iec60870_5_101.iec101types.sIEC101ConfigurationParameters sIEC101Config;
                sIEC101Config = new iec60870_5_101.iec101types.sIEC101ConfigurationParameters();
                sIEC101Config.sServerSet.u8NumberofSerialPortConnections = 1;

                iec60870_5_101.tgtserialtypes.sSerialCommunicationSettings[] psSerialSet = new iec60870_5_101.tgtserialtypes.sSerialCommunicationSettings[sIEC101Config.sServerSet.u8NumberofSerialPortConnections];
                sIEC101Config.sServerSet.psSerialSet = System.Runtime.InteropServices.Marshal.AllocHGlobal(
                sIEC101Config.sServerSet.u8NumberofSerialPortConnections * System.Runtime.InteropServices.Marshal.SizeOf(psSerialSet[0]));

                // check computer configuration serial com port number,  if server and client application running in same system, we can use com0com
                psSerialSet[0].u16SerialPortNumber = 1;
                psSerialSet[0].eSerialType = iec60870_5_101.tgtserialtypes.eSerialTypes.SERIAL_RS232;
                psSerialSet[0].eSerialBitRate = iec60870_5_101.tgtserialtypes.eSerialBitRate.BITRATE_9600;
                psSerialSet[0].eWordLength = iec60870_5_101.tgtserialtypes.eSerialWordLength.WORDLEN_8BITS;
                psSerialSet[0].eSerialParity = iec60870_5_101.tgtserialtypes.eSerialParity.EVEN;
                psSerialSet[0].eStopBits = iec60870_5_101.tgtserialtypes.eSerialStopBits.STOPBIT_1BIT;

                //windows serial port flow control
                psSerialSet[0].sFlowControl.bWinCTSoutputflow = 0;
                psSerialSet[0].sFlowControl.bWinDSRoutputflow = 0;
                psSerialSet[0].sFlowControl.eWinDTR = iec60870_5_101.tgtserialtypes.eWinDTRcontrol.WIN_DTR_CONTROL_DISABLE;
                psSerialSet[0].sFlowControl.eWinRTS = iec60870_5_101.tgtserialtypes.eWinRTScontrol.WIN_RTS_CONTROL_DISABLE;

                psSerialSet[0].sFlowControl.eLinuxFlowControl = iec60870_5_101.tgtserialtypes.eLinuxSerialFlowControl.FLOW_NONE;

                psSerialSet[0].sRxTimeParam.u16CharacterTimeout = 1;
                psSerialSet[0].sRxTimeParam.u16MessageTimeout = 0;
                psSerialSet[0].sRxTimeParam.u16InterCharacterDelay = 5;
                psSerialSet[0].sRxTimeParam.u16PostDelay = 0;
                psSerialSet[0].sRxTimeParam.u16PreDelay = 0;
                psSerialSet[0].sRxTimeParam.u8CharacterRetries = 20;
                psSerialSet[0].sRxTimeParam.u8MessageRetries = 0;

                IntPtr tmp1 = new IntPtr(sIEC101Config.sServerSet.psSerialSet.ToInt64());
                System.Runtime.InteropServices.Marshal.StructureToPtr(psSerialSet[0], tmp1, true);

                sIEC101Config.sServerSet.sServerProtSet.eDataLink = iec60870_5_101.iec101types.eDataLinkTransmission.UNBALANCED_MODE;
                sIEC101Config.sServerSet.sServerProtSet.eCASize = iec60870_5_101.iec101types.eCommonAddressSize.CA_TWO_BYTE;
                sIEC101Config.sServerSet.sServerProtSet.eCOTsize = iec60870_5_101.iec60870common.eCauseofTransmissionSize.COT_TWO_BYTE;
                sIEC101Config.sServerSet.sServerProtSet.eIOAsize = iec60870_5_101.iec101types.eInformationObjectAddressSize.IOA_THREE_BYTE;
                sIEC101Config.sServerSet.sServerProtSet.elinkAddrSize = iec60870_5_101.iec101types.eDataLinkAddressSize.DL_TWO_BYTE;
                sIEC101Config.sServerSet.sServerProtSet.u16DataLinkAddress = 1;
                sIEC101Config.sServerSet.sServerProtSet.eNegACK = iec60870_5_101.iec101types.eNegativeACK.FIXED_FRAME_NACK;
                sIEC101Config.sServerSet.sServerProtSet.ePosACK = iec60870_5_101.iec101types.ePositiveACK.FIXED_FRAME_ACK;

                sIEC101Config.sServerSet.sServerProtSet.u16Class1EventBufferSize = 5000;
                sIEC101Config.sServerSet.sServerProtSet.u16Class2EventBufferSize = 5000;

                sIEC101Config.sServerSet.sServerProtSet.u8Class1BufferOverFlowPercentage = 90;
                sIEC101Config.sServerSet.sServerProtSet.u8Class2BufferOverFlowPercentage = 90;
                sIEC101Config.sServerSet.sServerProtSet.u8MaxAPDUSize = 253;
                sIEC101Config.sServerSet.sServerProtSet.u16ShortPulseTime = 5000;
                sIEC101Config.sServerSet.sServerProtSet.u16LongPulseTime = 10000;
                sIEC101Config.sServerSet.sServerProtSet.u32ClockSyncPeriod = 0;
                sIEC101Config.sServerSet.sServerProtSet.bGenerateACTTERMrespond = 1;


                
                sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress = new ushort[iec60870_5_101.iec60870common.MAX_CA];
                sIEC101Config.sServerSet.sServerProtSet.u8TotalNumberofStations = 1;
                sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[0] = 1;
                sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[1] = 0;
                sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[2] = 0;
                sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[3] = 0;
                sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[4] = 0;



                sIEC101Config.sServerSet.sServerProtSet.u32BalancedModeTestConnectionSignalInterval = 60;

                sIEC101Config.sServerSet.sServerProtSet.bEnableFileTransfer = 0;
                sIEC101Config.sServerSet.sServerProtSet.ai8FileTransferDirPath = "//FileTransferServer//";
                sIEC101Config.sServerSet.sServerProtSet.u16MaxFilesInDirectory = 10;
				
#if VIEW_TRAFFIC
				sIEC101Config.sServerSet.sDebug.u32DebugOptions = (uint)( iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_TX | iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_RX);
#else
				sIEC101Config.sServerSet.sDebug.u32DebugOptions = 0;
#endif				

                sIEC101Config.sServerSet.sServerProtSet.bTransmitSpontMeasuredValue = 1;
                sIEC101Config.sServerSet.sServerProtSet.bTranmitInterrogationMeasuredValue = 1;
                sIEC101Config.sServerSet.sServerProtSet.bTransmitBackScanMeasuredValue = 1;

                sIEC101Config.sServerSet.sServerProtSet.u8InitialdatabaseQualityFlag = (byte)(iec60870_5_101.iec60870common.eIEC870QualityFlags.GD); /*!< 0- good/valid, 1 BIT- iv, 2 BIT-nt,  MAX VALUE -3   */
                sIEC101Config.sServerSet.sServerProtSet.bUpdateCheckTimestamp = 0; /*!< if it true ,the timestamp change also generate event  during the iec104update */

                
                
                sIEC101Config.sServerSet.u16NoofObject = 2;        // Define number of objects


                // Allocate memory for objects
                iec60870_5_101.iec101types.sIEC101Object[] psIEC101Objects = new iec60870_5_101.iec101types.sIEC101Object[sIEC101Config.sServerSet.u16NoofObject];
                sIEC101Config.sServerSet.psIEC101Objects = System.Runtime.InteropServices.Marshal.AllocHGlobal(
                    sIEC101Config.sServerSet.u16NoofObject * System.Runtime.InteropServices.Marshal.SizeOf(psIEC101Objects[0]));


                for (int i = 0; i < sIEC101Config.sServerSet.u16NoofObject; ++i)
                {
                    switch (i)
                    {

                        case 0:
                            psIEC101Objects[i].ai8Name = "M_ME_TF_1";
                            psIEC101Objects[i].eTypeID = iec60870_5_101.iec60870common.eIEC870TypeID.M_ME_TF_1;
                            psIEC101Objects[i].u32IOA = 100;
                            psIEC101Objects[i].eIntroCOT = iec60870_5_101.iec60870common.eIEC870COTCause.INRO1;
                            psIEC101Objects[i].u16Range = 10;
                            psIEC101Objects[i].eControlModel = iec60870_5_101.iec60870common.eControlModelConfig.STATUS_ONLY;
                            psIEC101Objects[i].u32SBOTimeOut = 0;
                            psIEC101Objects[i].eClass = iec60870_5_101.iec101types.eIECClass.IEC_CLASS1;
                            psIEC101Objects[i].u16CommonAddress = 1;
                            break;

                        case 1:
                            psIEC101Objects[i].ai8Name = "C_SE_TC_1";
                            psIEC101Objects[i].eTypeID = iec60870_5_101.iec60870common.eIEC870TypeID.C_SE_TC_1;
                            psIEC101Objects[i].u32IOA = 100;
                            psIEC101Objects[i].eIntroCOT = iec60870_5_101.iec60870common.eIEC870COTCause.NOTUSED;
                            psIEC101Objects[i].u16Range = 10;
                            psIEC101Objects[i].eControlModel = iec60870_5_101.iec60870common.eControlModelConfig.DIRECT_OPERATE;
                            psIEC101Objects[i].u32SBOTimeOut = 0;
                            psIEC101Objects[i].eClass = iec60870_5_101.iec101types.eIECClass.IEC_NO_CLASS;
                            psIEC101Objects[i].u16CommonAddress = 1;
                            break;
                    }
                    IntPtr tmp = new IntPtr(sIEC101Config.sServerSet.psIEC101Objects.ToInt64() + i * System.Runtime.InteropServices.Marshal.SizeOf(psIEC101Objects[0]));
                    System.Runtime.InteropServices.Marshal.StructureToPtr(psIEC101Objects[i], tmp, true);
                }


                // Load configuration
                eErrorCode = iec60870_5_101.iec101api.IEC101LoadConfiguration(iec101serverhandle, ref sIEC101Config, ref ptErrorValue);
                if (eErrorCode != 0)
                {
                    System.Console.WriteLine("IEC 60870-5-101 Library API Function - IEC101LoadConfiguration failed");
					System.Console.WriteLine("ErrorCode {0:D}: {1}", eErrorCode, errorcodestring(eErrorCode));
                    System.Console.WriteLine("ErrorValue {0:D}: {1}", ptErrorValue, errorvaluestring(ptErrorValue));
                    break;
                }

                // Start server
                eErrorCode = iec60870_5_101.iec101api.IEC101Start(iec101serverhandle, ref ptErrorValue);
                if (eErrorCode != 0)
                {
                    System.Console.WriteLine("IEC 60870-5-101 Library API Function - IEC101Start failed");
					System.Console.WriteLine("ErrorCode {0:D}: {1}", eErrorCode, errorcodestring(eErrorCode));
                    System.Console.WriteLine("ErrorValue {0:D}: {1}", ptErrorValue, errorvaluestring(ptErrorValue));
                    break;
                }

#if SIMULATE_UPDATE
                // update id & parameters        
                ushort uiCount = 1;
                iec60870_5_101.iec101types.sIEC101DataAttributeID[] psDAID = new iec60870_5_101.iec101types.sIEC101DataAttributeID[uiCount];
                iec60870_5_101.iec101types.sIEC101DataAttributeData[] psNewValue = new iec60870_5_101.iec101types.sIEC101DataAttributeData[uiCount];

                psDAID[0].u16SerialPortNumber = 1;
                psDAID[0].u16DataLinkAddress = 1;
                psDAID[0].eTypeID = iec60870_5_101.iec60870common.eIEC870TypeID.M_ME_TF_1;
                psDAID[0].u32IOA = 100;
                psDAID[0].pvUserData = IntPtr.Zero;
                psNewValue[0].tQuality = (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.GD;
                psDAID[0].u16CommonAddress = 1;

                psNewValue[0].pvData = System.Runtime.InteropServices.Marshal.AllocHGlobal((int)iec60870_5_101.tgttypes.eDataSizes.FLOAT32_SIZE);
                psNewValue[0].eDataType = iec60870_5_101.tgtcommon.eDataTypes.FLOAT32_DATA;
                psNewValue[0].eDataSize = iec60870_5_101.tgttypes.eDataSizes.FLOAT32_SIZE;


                SingleInt32Union f32data;
                f32data.i = 0;
                f32data.f = 1;
#endif

                System.Console.WriteLine("\r\n Enter CTRL-X to Exit");
                System.Console.WriteLine("\r\n");

                while (true)
                {
                    if (Console.KeyAvailable) // since .NET 2.0
                    {
                        char c = Console.ReadKey().KeyChar;
                        if (c == 24)
                        {
                            break;
                        }
                    }
                    else
                    {
#if SIMULATE_UPDATE
                        date = DateTime.Now;
                        //current date 
                        psNewValue[0].sTimeStamp.u8Day = (byte)date.Day;
                        psNewValue[0].sTimeStamp.u8Month = (byte)date.Month;
                        psNewValue[0].sTimeStamp.u16Year = (ushort)date.Year;

                        //time
                        psNewValue[0].sTimeStamp.u8Hour = (byte)date.Hour;
                        psNewValue[0].sTimeStamp.u8Minute = (byte)date.Minute;
                        psNewValue[0].sTimeStamp.u8Seconds = (byte)date.Second;
                        psNewValue[0].sTimeStamp.u16MilliSeconds = (ushort)date.Millisecond;
                        psNewValue[0].sTimeStamp.u16MicroSeconds = 0;
                        psNewValue[0].sTimeStamp.i8DSTTime = 0; //No Day light saving time
                        psNewValue[0].sTimeStamp.u8DayoftheWeek = (byte)date.DayOfWeek;


                        f32data.f += 1;


                        //Console.WriteLine("Update Measured Float Value {0:F}", f32data.f);

                        System.Runtime.InteropServices.Marshal.WriteInt32(psNewValue[0].pvData, f32data.i);

                        // Update server
                        eErrorCode = iec60870_5_101.iec101api.IEC101Update(iec101serverhandle, (byte)1, ref psDAID[0], ref psNewValue[0], uiCount, ref ptErrorValue);
                        if (eErrorCode != 0)
                        {
                            Console.WriteLine("IEC 60870-5-101 Library API Function - IEC101Update() failed: {0:D} {1:D}", eErrorCode, ptErrorValue);
							System.Console.WriteLine("ErrorCode {0:D}: {1}", eErrorCode, errorcodestring(eErrorCode));
							System.Console.WriteLine("ErrorValue {0:D}: {1}", ptErrorValue, errorvaluestring(ptErrorValue));
                        }

#endif
                        // update - time interval
                        Thread.Sleep(1000);
                    }


                }

                // Stop server
                eErrorCode = iec60870_5_101.iec101api.IEC101Stop(iec101serverhandle, ref ptErrorValue);
                if (eErrorCode != 0)
                {
                    System.Console.WriteLine("IEC 60870-5-101 Library API Function - IEC101Stop failed");
					System.Console.WriteLine("ErrorCode {0:D}: {1}", eErrorCode, errorcodestring(eErrorCode));
                    System.Console.WriteLine("ErrorValue {0:D}: {1}", ptErrorValue, errorvaluestring(ptErrorValue));
                    break;
                }


                // Free server
                eErrorCode = iec60870_5_101.iec101api.IEC101Free(iec101serverhandle, ref ptErrorValue);
                if (eErrorCode != 0)
                {
                    System.Console.WriteLine("IEC 60870-5-101 Library API Function - IEC101Free failed");
					System.Console.WriteLine("ErrorCode {0:D}: {1}", eErrorCode, errorcodestring(eErrorCode));
                    System.Console.WriteLine("ErrorValue {0:D}: {1}", ptErrorValue, errorvaluestring(ptErrorValue));
                    break;
                }

            } while (false);



            System.Console.Write("\nPress <Enter> to exit... ");
            while (Console.ReadKey().Key != ConsoleKey.Enter) { }

        }        
    }            
}