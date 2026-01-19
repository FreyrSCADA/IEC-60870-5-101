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
/*! \file       iec101clienttest-nuget.cs
 *  \brief      C# Source code file, IEC 60870-5-101 Client library test program for https://www.nuget.org/packages/iec60870_5_101/
 *
 *  \par        FreyrSCADA Embedded Solution Pvt Ltd
 *              Email   : tech.support@freyrscada.com
 */
/*****************************************************************************/


/*! \brief - In a loop simulate issue command - for particular IOA , value changes - issue a command to server  */
//#define SIMULATE_COMMAND 

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
        * Update callback
        ******************************************************************************/
        static short cbUpdate(ushort u16ObjectId, ref iec60870_5_101.iec101types.sIEC101DataAttributeID ptUpdateID, ref iec60870_5_101.iec101types.sIEC101DataAttributeData ptUpdateValue, ref iec60870_5_101.iec101types.sIEC101UpdateParameters ptUpdateParams, ref short ptErrorValue)
        {
            Console.WriteLine("\n\r\ncbUpdate() called");
            Console.WriteLine("Client ID " + u16ObjectId);
            Console.WriteLine("Data Link Address "+ ptUpdateID.u16DataLinkAddress);
            Console.WriteLine("Station Address "+ ptUpdateID.u16CommonAddress);

            Console.WriteLine("Data Attribute ID is  {0:D} IOA {1:D} ", ptUpdateID.eTypeID, ptUpdateID.u32IOA);
            Console.WriteLine("Data is  datatype->{0:D} datasize->{1:D}  ", ptUpdateValue.eDataType, ptUpdateValue.eDataSize);

            if ((ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_EP_TB_1) || (ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_EP_TE_1))
            {
                byte u8data = unchecked((byte)System.Runtime.InteropServices.Marshal.ReadByte(ptUpdateValue.pvData));

                if ((u8data & (byte)iec60870_5_101.iec60870common.eStartEventsofProtFlags.GS) == (byte)iec60870_5_101.iec60870common.eStartEventsofProtFlags.GS)
                {
                    Console.WriteLine("General start of operation");
                }

                if ((u8data & (byte)iec60870_5_101.iec60870common.eStartEventsofProtFlags.SL1) == (byte)iec60870_5_101.iec60870common.eStartEventsofProtFlags.SL1)
                {
                    Console.WriteLine("Start of operation phase L1");
                }

                if ((u8data & (byte)iec60870_5_101.iec60870common.eStartEventsofProtFlags.SL2) == (byte)iec60870_5_101.iec60870common.eStartEventsofProtFlags.SL2)
                {
                    Console.WriteLine("Start of operation phase L2");
                }

                if ((u8data & (byte)iec60870_5_101.iec60870common.eStartEventsofProtFlags.SL3) == (byte)iec60870_5_101.iec60870common.eStartEventsofProtFlags.SL3)
                {
                    Console.WriteLine("Start of operation phase L3");
                }

                if ((u8data & (byte)iec60870_5_101.iec60870common.eStartEventsofProtFlags.SIE) == (byte)iec60870_5_101.iec60870common.eStartEventsofProtFlags.SIE)
                {
                    Console.WriteLine("Start of operation IE");
                }

                if ((u8data & (byte)iec60870_5_101.iec60870common.eStartEventsofProtFlags.SRD) == (byte)iec60870_5_101.iec60870common.eStartEventsofProtFlags.SRD)
                {
                    Console.WriteLine("Start of operation in reverse direction");
                }
            }
            else if ((ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_EP_TC_1) || (ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_EP_TF_1))
                {

                    byte u8data = unchecked((byte)System.Runtime.InteropServices.Marshal.ReadByte(ptUpdateValue.pvData));


                    if ((u8data & (byte)iec60870_5_101.iec60870common.ePackedOutputCircuitInfoofProtFlags.GC) == (byte)iec60870_5_101.iec60870common.ePackedOutputCircuitInfoofProtFlags.GC)
                    {
                        Console.WriteLine("General command to output circuit ");
                    }

                    if ((u8data & (byte)iec60870_5_101.iec60870common.ePackedOutputCircuitInfoofProtFlags.CL1) == (byte)iec60870_5_101.iec60870common.ePackedOutputCircuitInfoofProtFlags.CL1)
                    {
                        Console.WriteLine("Command to output circuit phase L1");
                    }

                    if ((u8data & (byte)iec60870_5_101.iec60870common.ePackedOutputCircuitInfoofProtFlags.CL2) == (byte)iec60870_5_101.iec60870common.ePackedOutputCircuitInfoofProtFlags.CL2)
                    {
                        Console.WriteLine("Command to output circuit phase L2");
                    }

                    if ((u8data & (byte)iec60870_5_101.iec60870common.ePackedOutputCircuitInfoofProtFlags.CL3) == (byte)iec60870_5_101.iec60870common.ePackedOutputCircuitInfoofProtFlags.CL3)
                    {
                        Console.WriteLine("Command to output circuit phase L3");
                    }

                }
                else
                {

                    switch (ptUpdateValue.eDataType)
                    {
                        case iec60870_5_101.tgtcommon.eDataTypes.SINGLE_POINT_DATA:
                        case iec60870_5_101.tgtcommon.eDataTypes.DOUBLE_POINT_DATA:
                        case iec60870_5_101.tgtcommon.eDataTypes.UNSIGNED_BYTE_DATA:
                            Console.WriteLine("Data : {0:D}", System.Runtime.InteropServices.Marshal.ReadByte(ptUpdateValue.pvData));
                            break;

                        case iec60870_5_101.tgtcommon.eDataTypes.SIGNED_BYTE_DATA:
                            sbyte i8data = unchecked((sbyte)System.Runtime.InteropServices.Marshal.ReadByte(ptUpdateValue.pvData));
                            Console.WriteLine(i8data);
                            break;

                        case iec60870_5_101.tgtcommon.eDataTypes.UNSIGNED_WORD_DATA:
                            ushort u16data = unchecked((ushort)System.Runtime.InteropServices.Marshal.ReadInt16(ptUpdateValue.pvData));
                            Console.WriteLine(u16data);
                            break;

                        case iec60870_5_101.tgtcommon.eDataTypes.SIGNED_WORD_DATA:
                            Console.WriteLine("Data : {0:D}", System.Runtime.InteropServices.Marshal.ReadInt16(ptUpdateValue.pvData));
                            break;

                        case iec60870_5_101.tgtcommon.eDataTypes.UNSIGNED_DWORD_DATA:
                            uint u32data = unchecked((uint)System.Runtime.InteropServices.Marshal.ReadInt32(ptUpdateValue.pvData));
                            Console.WriteLine(u32data);
                            break;

                        case iec60870_5_101.tgtcommon.eDataTypes.SIGNED_DWORD_DATA:
                            Console.WriteLine("Data : {0:D}", System.Runtime.InteropServices.Marshal.ReadInt32(ptUpdateValue.pvData));
                            break;

                        case iec60870_5_101.tgtcommon.eDataTypes.FLOAT32_DATA:
                            SingleInt32Union f32data;
                            f32data.f = 0;
                            f32data.i = System.Runtime.InteropServices.Marshal.ReadInt32(ptUpdateValue.pvData);
                            //Console.WriteLine("Data : {0:F}", f32data.f);
                            Console.WriteLine(string.Format("Data : {0:0.00#}", f32data.f));
                            break;

                        default:
                            break;
                    }

                }


            if (ptUpdateValue.tQuality != (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.GD)
                {

                    /* Now for the Status */
                    if ((ptUpdateValue.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.IV) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.IV)
                    {
                        Console.WriteLine("IEC_INVALID_FLAG");
                    }

                    if ((ptUpdateValue.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.NT) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.NT)
                    {
                        Console.WriteLine("IEC_NONTOPICAL_FLAG");
                    }

                    if ((ptUpdateValue.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.SB) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.SB)
                    {
                        Console.WriteLine("IEC_SUBSTITUTED_FLAG");
                    }

                    if ((ptUpdateValue.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.BL) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.BL)
                    {
                        Console.WriteLine("IEC_BLOCKED_FLAG");
                    }

                    if ((ptUpdateValue.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.OV) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.OV)
                    {
                        Console.WriteLine("IEC_OV_FLAG");
                    }

                    if ((ptUpdateValue.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.EI) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.EI)
                    {
                        Console.WriteLine("IEC_EI_FLAG");
                    }

                    if ((ptUpdateValue.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.TR) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.TR)
                    {
                        Console.WriteLine("IEC_TR_FLAG");
                    }

                    if ((ptUpdateValue.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.CA) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.CA)
                    {
                        Console.WriteLine("IEC_CA_FLAG");
                    }

                    if ((ptUpdateValue.tQuality & (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.CR) == (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.CR)
                    {
                        Console.WriteLine("IEC_CR_FLAG");
                    }


                }

            if ((ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_EP_TA_1) ||
                    (ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_EP_TB_1) ||
                    (ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_EP_TC_1) ||
                    (ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_EP_TD_1) ||
                    (ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_EP_TE_1) ||
                    (ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_EP_TF_1))
                {
                    Console.WriteLine(" Elapsed time {0:D}", ptUpdateValue.u16ElapsedTime);
                }



            Console.WriteLine(" COT:" + ptUpdateParams.eCause);


            if (ptUpdateValue.sTimeStamp.u8Seconds != 0)
            {

                Console.WriteLine("Date : {0:D}-{1:D}-{2:D}  DOW -{3:D}", ptUpdateValue.sTimeStamp.u8Day, ptUpdateValue.sTimeStamp.u8Month, ptUpdateValue.sTimeStamp.u16Year, ptUpdateValue.sTimeStamp.u8DayoftheWeek);

                Console.WriteLine("Time : {0:D}:{1:D2}:{2:D2}:{3:D4}", ptUpdateValue.sTimeStamp.u8Hour, ptUpdateValue.sTimeStamp.u8Minute, ptUpdateValue.sTimeStamp.u8Seconds, ptUpdateValue.sTimeStamp.u16MilliSeconds);
            }

            if ((ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_IT_NA_1) ||
                   (ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_IT_TA_1) ||
                   (ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_IT_TB_1))
            {
                Console.WriteLine("Elapsed time {0:D}", ptUpdateValue.u8Sequence);
            }

            if ((ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_ST_NA_1) ||
                    (ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_ST_TA_1) ||
                    (ptUpdateID.eTypeID == iec60870_5_101.iec60870common.eIEC870TypeID.M_ST_TB_1))
            {
                if (ptUpdateValue.bTRANSIENT == 1)
                    Console.WriteLine("transient  - true");
                else
                    Console.WriteLine("transient  - false");
            }



            return (short)iec60870_5_101.tgterrorcodes.eTgtErrorCodes.EC_NONE;
        }

        /******************************************************************************
        * client status callback
        ******************************************************************************/
        static short cbClientStatus(ushort u16ObjectId, ref  iec60870_5_101.iec101types.sIEC101DataAttributeID psDAID, ref iec60870_5_101.iec60870common.eStatus peSat, ref short ptErrorValue)
        {
            Console.WriteLine("\r\r\ncbClientstatus() called");
            Console.WriteLine("Client ID " + u16ObjectId);

            if (peSat == iec60870_5_101.iec60870common.eStatus.CONNECTED)
            {
                Console.WriteLine("Status - Connected");
            }
            else
            {
                Console.WriteLine("Status - Disconnected");
            }

            Console.WriteLine("Data Link address " + psDAID.u16DataLinkAddress);
            Console.WriteLine("Server Common Address " + psDAID.u16CommonAddress);
            Console.WriteLine("Serial port number " + psDAID.u16SerialPortNumber);



            return (short)iec60870_5_101.tgterrorcodes.eTgtErrorCodes.EC_NONE;
        }


        /******************************************************************************
        * Debug callback
        ******************************************************************************/
        static short cbDebug(ushort u16ObjectId, ref iec60870_5_101.iec101types.sIEC101DebugData ptDebugData, ref short ptErrorValue)
        {
            //Console.Write("\r\ncbDebug() called");
            Console.Write("\r\nClient ID :{0:D} ", u16ObjectId);

            Console.Write(" {0:D}-{1:D}-{2:D}", ptDebugData.sTimeStamp.u8Day, ptDebugData.sTimeStamp.u8Month, ptDebugData.sTimeStamp.u16Year);

            Console.Write(" {0:D}:{1:D2}:{2:D2}", ptDebugData.sTimeStamp.u8Hour, ptDebugData.sTimeStamp.u8Minute, ptDebugData.sTimeStamp.u8Seconds);

            if ((ptDebugData.u32DebugOptions & (uint)iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_RX) == (uint)iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_RX)
            {

                Console.Write("Rx " + " Serial port " + ptDebugData.u16ComportNumber + " <- ");

                for (ushort i = 0; i < ptDebugData.u16RxCount; i++)
                    Console.Write("{0:X2} ", ptDebugData.au8RxData[i]);
                
            }

            if ((ptDebugData.u32DebugOptions & (uint)iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_TX) == (uint)iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_TX)
            {
                Console.Write("Tx " + " Serial port " + ptDebugData.u16ComportNumber + " -> ");

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
            System.IntPtr iec101clienthandle;       // IEC 60870-5-101 Client object
            iec60870_5_101.iec101types.sIEC101Parameters sParameters;    // IEC101 Client object callback paramters 
            iec60870_5_101.iec101types.sIEC101DataAttributeID sWriteDAID;       // Command data identification parameters
            iec60870_5_101.iec101types.sIEC101DataAttributeData sWriteValue;    // Command data value parameters
            iec60870_5_101.iec101types.sIEC101CommandParameters sCommandParams; // Command data parameters

            System.Console.WriteLine(" \n\t\t**** FreyrSCADA - IEC 60870-5-101 Client Library Test ****");

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


            iec101clienthandle = System.IntPtr.Zero;
            sParameters = new iec60870_5_101.iec101types.sIEC101Parameters();

            // Initialize IEC 60870-5-101 Server object parameters
            sParameters.eAppFlag = iec60870_5_101.tgtcommon.eApplicationFlag.APP_CLIENT;                      // This is a IEC101 Server
            sParameters.ptReadCallback = null;                                              // Read Callback
            sParameters.ptWriteCallback = null;                                             // Write Callback
            sParameters.ptUpdateCallback = cbUpdate;                                        // Update Callback
            sParameters.ptSelectCallback = null;                                            // Select commands
            sParameters.ptOperateCallback = null;                                           // Operate commands
            sParameters.ptCancelCallback = null;                                            // Cancel commands
            sParameters.ptFreezeCallback = null;                                            // Freeze Callback
            sParameters.ptPulseEndActTermCallback = null;                                   // pulse end callback
            sParameters.ptParameterActCallback = null;                                      // Parameter activation callback
            sParameters.ptDebugCallback = cbDebug;   // Debug Callback
            sParameters.ptClientStatusCallback = cbClientStatus;                            // client connection status callback
            sParameters.ptDirectoryCallback = null;                                         // client Directory callback
            sParameters.u16ObjectId = 1;
            sParameters.u32Options = 0;
            short eErrorCode = 0;                                                              // API Function return error paramter
            short ptErrorValue = 0;                                                          // API Function return addtional error paramter


            do
            {
                // Create a Client object
                iec101clienthandle = iec60870_5_101.iec101api.IEC101Create(ref sParameters, ref eErrorCode, ref ptErrorValue);
                if (iec101clienthandle == System.IntPtr.Zero)
                {
                    System.Console.WriteLine("IEC 60870-5-101 Library API Function - IEC101Create failed");
					System.Console.WriteLine("ErrorCode {0:D}: {1}", eErrorCode, errorcodestring(eErrorCode));
                    System.Console.WriteLine("ErrorValue {0:D}: {1}", ptErrorValue, errorvaluestring(ptErrorValue));
                    break;
                }

                iec60870_5_101.iec101types.sIEC101ConfigurationParameters sIEC101Config;
                sIEC101Config = new iec60870_5_101.iec101types.sIEC101ConfigurationParameters();
                // Client load configuration - communication and protocol configuration parameters         


                sIEC101Config.sClientSet.benabaleUTCtime = 0;

#if VIEW_TRAFFIC
				sIEC101Config.sClientSet.sDebug.u32DebugOptions = (uint)( iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_TX | iec60870_5_101.tgtcommon.eDebugOptionsFlag.DEBUG_OPTION_RX);
         
#else
				sIEC101Config.sClientSet.sDebug.u32DebugOptions = 0;
#endif					
				

                //client 1 configuration Starts                
                sIEC101Config.sClientSet.u8NoofClient = 1;
                iec60870_5_101.iec101types.sIEC101ClientObject[] psClientObjects = new iec60870_5_101.iec101types.sIEC101ClientObject[sIEC101Config.sClientSet.u8NoofClient];
                sIEC101Config.sClientSet.psClientObjects = System.Runtime.InteropServices.Marshal.AllocHGlobal(
                sIEC101Config.sClientSet.u8NoofClient * System.Runtime.InteropServices.Marshal.SizeOf(psClientObjects[0]));

                sIEC101Config.sClientSet.eLink = iec60870_5_101.iec101types.eDataLinkTransmission.UNBALANCED_MODE;          // Data Link Mode 
                psClientObjects[0].sSerialSet.eSerialType = iec60870_5_101.tgtserialtypes.eSerialTypes.SERIAL_RS232;
                // check computer configuration serial com port number,  if server and client application running in same system, we can use com0com
                psClientObjects[0].sSerialSet.u16SerialPortNumber = 2;
                psClientObjects[0].sSerialSet.eSerialBitRate = iec60870_5_101.tgtserialtypes.eSerialBitRate.BITRATE_9600;
                psClientObjects[0].sSerialSet.eWordLength = iec60870_5_101.tgtserialtypes.eSerialWordLength.WORDLEN_8BITS;
                psClientObjects[0].sSerialSet.eSerialParity = iec60870_5_101.tgtserialtypes.eSerialParity.EVEN;
                psClientObjects[0].sSerialSet.eStopBits = iec60870_5_101.tgtserialtypes.eSerialStopBits.STOPBIT_1BIT;

                //windows serial port flow control
                psClientObjects[0].sSerialSet.sFlowControl.bWinCTSoutputflow = 0;
                psClientObjects[0].sSerialSet.sFlowControl.bWinDSRoutputflow = 0;
                psClientObjects[0].sSerialSet.sFlowControl.eWinDTR = iec60870_5_101.tgtserialtypes.eWinDTRcontrol.WIN_DTR_CONTROL_DISABLE;
                psClientObjects[0].sSerialSet.sFlowControl.eWinRTS = iec60870_5_101.tgtserialtypes.eWinRTScontrol.WIN_RTS_CONTROL_DISABLE;

                psClientObjects[0].sSerialSet.sFlowControl.eLinuxFlowControl = iec60870_5_101.tgtserialtypes.eLinuxSerialFlowControl.FLOW_NONE;

                psClientObjects[0].sSerialSet.sRxTimeParam.u16CharacterTimeout = 1;
                psClientObjects[0].sSerialSet.sRxTimeParam.u16MessageTimeout = 0;
                psClientObjects[0].sSerialSet.sRxTimeParam.u16InterCharacterDelay = 5;
                psClientObjects[0].sSerialSet.sRxTimeParam.u16PostDelay = 0;
                psClientObjects[0].sSerialSet.sRxTimeParam.u16PreDelay = 0;
                psClientObjects[0].sSerialSet.sRxTimeParam.u8CharacterRetries = 20;
                psClientObjects[0].sSerialSet.sRxTimeParam.u8MessageRetries = 0;



                psClientObjects[0].sClientProtSet.eCASize = iec60870_5_101.iec101types.eCommonAddressSize.CA_TWO_BYTE;
                psClientObjects[0].sClientProtSet.eCOTsize = iec60870_5_101.iec60870common.eCauseofTransmissionSize.COT_TWO_BYTE;
                psClientObjects[0].sClientProtSet.u8OriginatorAddress = 1;
                psClientObjects[0].sClientProtSet.eIOAsize = iec60870_5_101.iec101types.eInformationObjectAddressSize.IOA_THREE_BYTE;
                psClientObjects[0].sClientProtSet.elinkAddrSize = iec60870_5_101.iec101types.eDataLinkAddressSize.DL_TWO_BYTE;
                psClientObjects[0].sClientProtSet.u8TotalNumberofStations = 1;
                
                
                psClientObjects[0].sClientProtSet.au16CommonAddress = new ushort[iec60870_5_101.iec60870common.MAX_CA];
                psClientObjects[0].sClientProtSet.u8TotalNumberofStations = 1;
                psClientObjects[0].sClientProtSet.au16CommonAddress[0] = 1;
                psClientObjects[0].sClientProtSet.au16CommonAddress[1] = 0;
                psClientObjects[0].sClientProtSet.au16CommonAddress[2] = 0;
                psClientObjects[0].sClientProtSet.au16CommonAddress[3] = 0;
                psClientObjects[0].sClientProtSet.au16CommonAddress[4] = 0;


                psClientObjects[0].sClientProtSet.u16DataLinkAddress = 1;
                psClientObjects[0].sClientProtSet.u32LinkLayerTimeout = 5000;
                psClientObjects[0].sClientProtSet.u32PollInterval = 1000;

                psClientObjects[0].sClientProtSet.u32GeneralInterrogationInterval = 60;    /*!< in sec if 0 , gi will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group1InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group2InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group3InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group4InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group5InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group6InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group7InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group8InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group9InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group10InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group11InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group12InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group13InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group14InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group15InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group16InterrogationInterval = 0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32CounterInterrogationInterval = 60;    /*!< in sec if 0 , ci will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group1CounterInterrogationInterval = 0;    /*!< in sec if 0 , group 1 counter interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group2CounterInterrogationInterval = 0;    /*!< in sec if 0 , group 1 counter interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group3CounterInterrogationInterval = 0;    /*!< in sec if 0 , group 1 counter interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32Group4CounterInterrogationInterval = 0;    /*!< in sec if 0 , group 1 counter interrogation will not send in particular interval*/
                psClientObjects[0].sClientProtSet.u32ClockSyncInterval = 60;              /*!< in sec if 0 , clock sync, will not send in particular interval */


                psClientObjects[0].sClientProtSet.u32CommandTimeout = 10000;
                psClientObjects[0].sClientProtSet.bCommandResponseActtermUsed = 1;

                // File transfer protocol configuration parameters
                psClientObjects[0].sClientProtSet.bEnableFileTransfer = 0;
                psClientObjects[0].sClientProtSet.u32FileTransferTimeout = 1000000;
                psClientObjects[0].sClientProtSet.ai8FileTransferDirPath= "//FileTest//";
                


                sIEC101Config.sClientSet.bAutoGenIEC101DataObjects = 1;

                psClientObjects[0].u16NoofObject = 0;        // Define number of objects
#if false             
                // Allocate memory for objects
                iec60870_5_101.iec101types.sIEC101Object[] psIEC101Objects = new iec60870_5_101.iec101types.sIEC101Object[psClientObjects[0].u16NoofObject];
                psClientObjects[0].psIEC101Objects = System.Runtime.InteropServices.Marshal.AllocHGlobal(
                    psClientObjects[0].u16NoofObject * System.Runtime.InteropServices.Marshal.SizeOf(psIEC101Objects[0]));


                for (int i = 0; i < psClientObjects[0].u16NoofObject; ++i)
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
                    IntPtr tmp = new IntPtr(psClientObjects[0].psIEC101Objects.ToInt64() + i * System.Runtime.InteropServices.Marshal.SizeOf(psIEC101Objects[0]));
                    System.Runtime.InteropServices.Marshal.StructureToPtr(psIEC101Objects[i], tmp, true);
                }

#endif

                IntPtr tmp1 = new IntPtr(sIEC101Config.sClientSet.psClientObjects.ToInt64());
                System.Runtime.InteropServices.Marshal.StructureToPtr(psClientObjects[0], tmp1, true);



                // Load configuration
                eErrorCode = iec60870_5_101.iec101api.IEC101LoadConfiguration(iec101clienthandle, ref sIEC101Config, ref ptErrorValue);
                if (eErrorCode != 0)
                {
                    System.Console.WriteLine("IEC 60870-5-101 Library API Function - IEC101LoadConfiguration failed");
					System.Console.WriteLine("ErrorCode {0:D}: {1}", eErrorCode, errorcodestring(eErrorCode));
                    System.Console.WriteLine("ErrorValue {0:D}: {1}", ptErrorValue, errorvaluestring(ptErrorValue));
                    break;
                }

                // Start server
                eErrorCode = iec60870_5_101.iec101api.IEC101Start(iec101clienthandle, ref ptErrorValue);
                if (eErrorCode != 0)
                {
                    System.Console.WriteLine("IEC 60870-5-101 Library API Function - IEC101Start failed");
					System.Console.WriteLine("ErrorCode {0:D}: {1}", eErrorCode, errorcodestring(eErrorCode));
                    System.Console.WriteLine("ErrorValue {0:D}: {1}", ptErrorValue, errorvaluestring(ptErrorValue));
                    break;
                }  
                
 #if SIMULATE_COMMAND               
                // command data
                sWriteDAID = new iec60870_5_101.iec101types.sIEC101DataAttributeID();               // Command data identification parameters
                sWriteValue = new iec60870_5_101.iec101types.sIEC101DataAttributeData();            // Command data value parameters
                sCommandParams = new iec60870_5_101.iec101types.sIEC101CommandParameters();         // Command data parameters


                sWriteDAID.u16SerialPortNumber = 2;
                sWriteDAID.u16DataLinkAddress = 1;                
                sWriteDAID.eTypeID = iec60870_5_101.iec60870common.eIEC870TypeID.C_SE_TC_1;
                sWriteDAID.u32IOA = 100;
                sWriteDAID.u16CommonAddress = 1;

                sWriteValue.tQuality = (ushort)iec60870_5_101.iec60870common.eIEC870QualityFlags.GD;


                sWriteValue.pvData = System.Runtime.InteropServices.Marshal.AllocHGlobal((int)tgttypes.eDataSizes.FLOAT32_SIZE);
                sWriteValue.eDataType = iec60870_5_101.tgtcommon.eDataTypes.FLOAT32_DATA;
                sWriteValue.eDataSize = tgttypes.eDataSizes.FLOAT32_SIZE;

                SingleInt32Union f32data;
                f32data.i = 0;
                f32data.f = 1;
#endif

                System.Console.WriteLine("Enter CTRL-X to Exit");
               
                Thread.Sleep(3000);

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

#if SIMULATE_COMMAND  
                        date = DateTime.Now;
                        //current date 
                        sWriteValue.sTimeStamp.u8Day = (byte)date.Day;
                        sWriteValue.sTimeStamp.u8Month = (byte)date.Month;
                        sWriteValue.sTimeStamp.u16Year = (ushort)date.Year;

                        //time
                        sWriteValue.sTimeStamp.u8Hour = (byte)date.Hour;
                        sWriteValue.sTimeStamp.u8Minute = (byte)date.Minute;
                        sWriteValue.sTimeStamp.u8Seconds = (byte)date.Second;
                        sWriteValue.sTimeStamp.u16MilliSeconds = (ushort)date.Millisecond;
                        sWriteValue.sTimeStamp.u16MicroSeconds = 0;
                        sWriteValue.sTimeStamp.i8DSTTime = 0; //No Day light saving time
                        sWriteValue.sTimeStamp.u8DayoftheWeek = (byte)date.DayOfWeek;



                        f32data.f += 1.0f;


                        Console.WriteLine("Command Measured Value {0:F}", f32data.f);

                        System.Runtime.InteropServices.Marshal.WriteInt32(sWriteValue.pvData, f32data.i);

                        // operate command
                        eErrorCode = iec60870_5_101.iec101api.IEC101Operate(iec101clienthandle, ref sWriteDAID, ref sWriteValue, ref sCommandParams, ref ptErrorValue);
                        if (eErrorCode != 0)
                        {
                            Console.WriteLine("IEC 60870-5-101 Library API Function - IEC101Operate() failed: {0:D} {1:D}", eErrorCode, ptErrorValue);
							System.Console.WriteLine("ErrorCode {0:D}: {1}", eErrorCode, errorcodestring(eErrorCode));
							System.Console.WriteLine("ErrorValue {0:D}: {1}", ptErrorValue, errorvaluestring(ptErrorValue));
						}

#endif
//Sending Command data - time interval
                        Thread.Sleep(5000);
                    }
                }

                // Stop Client
                eErrorCode = iec60870_5_101.iec101api.IEC101Stop(iec101clienthandle, ref ptErrorValue);
                if (eErrorCode != 0)
                {
                    System.Console.WriteLine("IEC 60870-5-101 Library API Function - IEC101Stop failed");
					System.Console.WriteLine("ErrorCode {0:D}: {1}", eErrorCode, errorcodestring(eErrorCode));
                    System.Console.WriteLine("ErrorValue {0:D}: {1}", ptErrorValue, errorvaluestring(ptErrorValue));
                    break;
                }

                // Free Client
                eErrorCode = iec60870_5_101.iec101api.IEC101Free(iec101clienthandle, ref ptErrorValue);
                if (eErrorCode != 0)
                {
                    System.Console.WriteLine("IEC 60870-5-101 Library API Function - IEC101Free failed");
					System.Console.WriteLine("ErrorCode {0:D}: {1}", eErrorCode, errorcodestring(eErrorCode));
                    System.Console.WriteLine("ErrorValue {0:D}: {1}", ptErrorValue, errorvaluestring(ptErrorValue));
                    break;
                }

                

            } while (false);



            System.Console.Write("Press <Enter> to Exit... ");
            while (Console.ReadKey().Key != ConsoleKey.Enter) { }

        }        
    }            
}
