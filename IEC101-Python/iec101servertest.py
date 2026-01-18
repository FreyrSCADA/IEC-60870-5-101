import ctypes 
import time
import struct
import sys
import types
import keyboard
from pyiec101.iec101api import *


# enbale to view traffic
VIEW_TRAFFIC = 1

# print error code and description
def errorcodestring(errorcode):
    sIEC101ErrorCodeDes = sIEC101ErrorCode()
    sIEC101ErrorCodeDes.iErrorCode = errorcode
    iec101_lib.IEC101ErrorCodeString(sIEC101ErrorCodeDes)
    return sIEC101ErrorCodeDes.LongDes.decode("utf-8")

# print error value and description
def errorvaluestring(errorvalue):
    sIEC101ErrorValueDes = sIEC101ErrorValue()
    sIEC101ErrorValueDes.iErrorValue = errorvalue   
    iec101_lib.IEC101ErrorValueString(sIEC101ErrorValueDes)
    return sIEC101ErrorValueDes.LongDes.decode("utf-8")

# print the struct sIEC101DataAttributeID and sIEC101DataAttributeData
def vPrintDataInformation(psIEC101DataAttributeID , psIEC101DataAttributeData ):

    print(f" Data Link Address {psIEC101DataAttributeID.contents.u16DataLinkAddress}")
    print(f" Common Address {psIEC101DataAttributeID.contents.u16CommonAddress}")
    print(f" Typeid ID is {psIEC101DataAttributeID.contents.eTypeID} IOA   {psIEC101DataAttributeID.contents.u32IOA}")
    print(f" Datatype->{psIEC101DataAttributeData.contents.eDataType} Datasize->{ psIEC101DataAttributeData.contents.eDataSize}" )

    if(psIEC101DataAttributeData.contents.tQuality) != eIEC870QualityFlags.GD :
        if(psIEC101DataAttributeData.contents.tQuality & eIEC870QualityFlags.IV) == eIEC870QualityFlags.IV:
            print(" IEC_INVALID_FLAG")
        if(psIEC101DataAttributeData.contents.tQuality & eIEC870QualityFlags.NT) == eIEC870QualityFlags.NT:
             print(" IEC_NONTOPICAL_FLAG")
        if(psIEC101DataAttributeData.contents.tQuality & eIEC870QualityFlags.SB) == eIEC870QualityFlags.SB:
             print(" IEC_SUBSTITUTED_FLAG")
        if(psIEC101DataAttributeData.contents.tQuality & eIEC870QualityFlags.BL) == eIEC870QualityFlags.BL:
             print(" IEC_BLOCKED_FLAG")

    data_type = psIEC101DataAttributeData.contents.eDataType

    if data_type in (eDataTypes.SINGLE_POINT_DATA, eDataTypes.DOUBLE_POINT_DATA, eDataTypes.UNSIGNED_BYTE_DATA):
        data = bytearray(ctypes.string_at(psIEC101DataAttributeData.contents.pvData, 1))
        u8data = struct.unpack('B', data)[0] 
        print(f" Data : {u8data}")

    elif data_type == eDataTypes.SIGNED_BYTE_DATA:
        data = bytearray(ctypes.string_at(psIEC101DataAttributeData.contents.pvData, 1))
        i8data = struct.unpack('b', data)[0]        
        print(f" Data : {i8data}")

    elif data_type == eDataTypes.UNSIGNED_WORD_DATA:
        data = bytearray(ctypes.string_at(psIEC101DataAttributeData.contents.pvData, 2))
        u16data = struct.unpack('H', data)[0]        
        print(f" Data : {u16data}")

    elif data_type == eDataTypes.SIGNED_WORD_DATA:
        data = bytearray(ctypes.string_at(psIEC101DataAttributeData.contents.pvData, 2))
        i16data = struct.unpack('h', data)[0]        
        print(f" Data : {i16data}")

    elif data_type == eDataTypes.UNSIGNED_DWORD_DATA:
        data = bytearray(ctypes.string_at(psIEC101DataAttributeData.contents.pvData, 4))
        u32data = struct.unpack('I', data)[0]        
        print(f" Data : {u32data}")


    elif data_type == eDataTypes.SIGNED_DWORD_DATA:
        data = bytearray(ctypes.string_at(psIEC101DataAttributeData.contents.pvData, 4))
        i32data = struct.unpack('i', data)[0]        
        print(f" Data : {i32data}")

    elif data_type == eDataTypes.FLOAT32_DATA:
        data = bytearray(ctypes.string_at(psIEC101DataAttributeData.contents.pvData, 4))
        f32data = struct.unpack('f', data)[0] 
        print(f" Data : {f32data:.3f}")

    if psIEC101DataAttributeData.contents.sTimeStamp.u16Year != 0:
        print(f" Date : {psIEC101DataAttributeData.contents.sTimeStamp.u8Day:02}-{psIEC101DataAttributeData.contents.sTimeStamp.u8Month:02}-{psIEC101DataAttributeData.contents.sTimeStamp.u16Year:04}  DOW -{psIEC101DataAttributeData.contents.sTimeStamp.u8DayoftheWeek}")
        print(f" Time : {psIEC101DataAttributeData.contents.sTimeStamp.u8Hour:02}:{psIEC101DataAttributeData.contents.sTimeStamp.u8Minute:02}:{psIEC101DataAttributeData.contents.sTimeStamp.u8Seconds:02}:{psIEC101DataAttributeData.contents.sTimeStamp.u16MilliSeconds:03}")

# iec101 read callback 
def cbRead(u16ObjectId, psIEC104DataAttributeID, psIEC104DataAttributeData , psReadParams, ptErrorValue):
    i16rErrorCode = ctypes.c_short()
    i16rErrorCode = 0   
    print(" cbRead() called ")
    print(" Server ID : %u" % u16ObjectId)
    vPrintDataInformation(psIEC104DataAttributeID, psIEC104DataAttributeData)
    message = f"Orginator Address {psReadParams.contents.u8OriginatorAddress}"
    print(message)
    return i16rErrorCode

# iec101 write callback 
def cbWrite(u16ObjectId, psIEC101DataAttributeID, psIEC101DataAttributeData, psIEC101WriteParameters, ptErrorValue):
    i16rErrorCode = ctypes.c_short()
    i16rErrorCode = 0   
    print(" cbWrite() called ")
    print(" Server ID : %u" % u16ObjectId)
    vPrintDataInformation(psIEC101DataAttributeID, psIEC101DataAttributeData)
    message = f"Orginator Address {psIEC101WriteParameters.contents.u8OriginatorAddress}"
                                                                    
    print(message)
    return i16rErrorCode

# Freeze Callback
def cbFreeze( u16ObjectId, eCounterFreeze, psIEC101DataAttributeID , psIEC101DataAttributeData , psIEC101WriteParameters , ptErrorValue):

    i16rErrorCode = ctypes.c_short()
    i16rErrorCode = 0   
    print(" cbFreeze() called")  

    print(" Server ID : %u" % u16ObjectId)
    vPrintDataInformation(psIEC101DataAttributeID, psIEC101DataAttributeData)
    message = f"Orginator Address {psIEC101WriteParameters.contents.u8OriginatorAddress}"
    print(message)

    print(f" Command Typeid : {psIEC101DataAttributeID.contents.eTypeID}");
    print(f" COT : {psIEC101WriteParameters.contents.eCause}");
   

    return i16rErrorCode

# Select callback
def cbSelect(u16ObjectId, psIEC101DataAttributeID , psIEC101DataAttributeData ,psIEC101CommandParameters , ptErrorValue):

    i16rErrorCode = ctypes.c_short()
    i16rErrorCode = 0   
    print(" cbSelect() called ")

    print(" Server ID : %u" % u16ObjectId)
    vPrintDataInformation(psIEC101DataAttributeID, psIEC101DataAttributeData)
    message = f"Orginator Address {psIEC101CommandParameters.contents.u8OriginatorAddress}"
    print(message)
    
    print(f" Qualifier : {psIEC101CommandParameters.contents.eQOCQU}" );
    print(f" Pulse Duration : {psIEC101CommandParameters.contents.u32PulseDuration}" );

    return i16rErrorCode

# Operate callback
def cbOperate(u16ObjectId, psIEC101DataAttributeID , psIEC101DataAttributeData ,psIEC101CommandParameters , ptErrorValue):

    i16rErrorCode = ctypes.c_short()
    i16rErrorCode = 0   
    print(" cbOperate() called")

    print(" Server ID : %u" % u16ObjectId)
    vPrintDataInformation(psIEC101DataAttributeID, psIEC101DataAttributeData)
    message = f"Orginator Address {psIEC101CommandParameters.contents.u8OriginatorAddress}"
    print(message)

    print(f" Qualifier : {psIEC101CommandParameters.contents.eQOCQU}")
    print(f" Pulse Duration : {psIEC101CommandParameters.contents.u32PulseDuration}")
   

    return i16rErrorCode

# Operate pulse end callback
def cbpulseend(u16ObjectId, psIEC101DataAttributeID , psIEC101DataAttributeData ,psIEC101CommandParameters , ptErrorValue):

    i16rErrorCode = ctypes.c_short()
    i16rErrorCode = 0   
    print(" cbpulseend() called ")


    print(" Server ID : %u" % u16ObjectId)
    vPrintDataInformation(psIEC101DataAttributeID, psIEC101DataAttributeData)
    message = f"Orginator Address {psIEC101CommandParameters.contents.u8OriginatorAddress}"
    print(message)

    print(f" Qualifier : {psIEC101CommandParameters.contents.eQOCQU}")
    print(f" Pulse Duration : {psIEC101CommandParameters.contents.u32PulseDuration}")
   

    return i16rErrorCode

# Cancel callback
def cbCancel(u16ObjectId, eOperation, psIEC101DataAttributeID , psIEC101DataAttributeData ,psIEC101CommandParameters , ptErrorValue):

    i16rErrorCode = ctypes.c_short()
    i16rErrorCode = 0   
    print(" cbCancel() called from IEC101 client")

    print(" Server ID : %u" % u16ObjectId)
    vPrintDataInformation(psIEC101DataAttributeID, psIEC101DataAttributeData)
    message = f"Orginator Address {psIEC101CommandParameters.contents.u8OriginatorAddress}"
    print(message)


    if eOperation   ==  eOperationFlag.OPERATE:
        print(" Operate operation to be cancel")
    elif eOperation   ==  eOperationFlag.SELECT:
        print(" Select operation to cancel")

    print(f" Qualifier : {psIEC101CommandParameters.contents.eQOCQU}")
    print(f" Pulse Duration :{psIEC101CommandParameters.contents.u32PulseDuration}")
    

    return i16rErrorCode

# Parameteract callback
def cbParameterAct(u16ObjectId, psIEC101DataAttributeID , psIEC101DataAttributeData , psIEC101ParameterActParameters , ptErrorValue):

    i16rErrorCode = ctypes.c_short()
    i16rErrorCode = 0   
    print(" cbParameterAct called from IEC101 client")

    print(" Server ID : %u" % u16ObjectId)
    vPrintDataInformation(psIEC101DataAttributeID, psIEC101DataAttributeData)
    message = f"Orginator Address {psIEC101ParameterActParameters.contents.u8OriginatorAddress}"
    print(message)

    print(f" Qualifier of Parameter Activation/Kind of Parameter - {psIEC101ParameterActParameters.contents.u8QPA}")
    

    return i16rErrorCode

# Debug callback
def cbDebug(u16ObjectId,  psIEC101DebugData , ptErrorValue):
    i16rErrorCode = ctypes.c_short()
    i16rErrorCode = 0 

    u16nav = ctypes.c_ushort()
    u16nav = 0
   
    #printf(" cbDebug() called");
    
    print(f" {psIEC101DebugData.contents.sTimeStamp.u8Hour}:{psIEC101DebugData.contents.sTimeStamp.u8Minute}:{psIEC101DebugData.contents.sTimeStamp.u8Seconds} Server ID: {u16ObjectId}", end='')

    if (psIEC101DebugData.contents.u32DebugOptions & eDebugOptionsFlag.DEBUG_OPTION_TX) == eDebugOptionsFlag.DEBUG_OPTION_TX:
        print(f" Serial Port {psIEC101DebugData.contents.u16ComportNumber} ", end='')
        print(" ->", end='')      
       
        for u16nav in range(psIEC101DebugData.contents.u16TxCount):
            print(f" {psIEC101DebugData.contents.au8TxData[u16nav]:02x}", end='')
        

        
    if (psIEC101DebugData.contents.u32DebugOptions & eDebugOptionsFlag.DEBUG_OPTION_RX) == eDebugOptionsFlag.DEBUG_OPTION_RX:
         print(f" Serial Port {psIEC101DebugData.contents.u16ComportNumber} ", end='')
         print(" <-", end='')

         for u16nav in range(psIEC101DebugData.contents.u16RxCount):
            print(f" {psIEC101DebugData.contents.au8RxData[u16nav]:02x}", end='')
        

        
    if (psIEC101DebugData.contents.u32DebugOptions & eDebugOptionsFlag.DEBUG_OPTION_ERROR) == eDebugOptionsFlag.DEBUG_OPTION_ERROR:
        print(f" Error message {psIEC101DebugData.contents.au8ErrorMessage}")
        print(f" ErrorCode {psIEC101DebugData.contents.iErrorCode}")
        print(f" ErrorValue {psIEC101DebugData.contents.tErrorvalue}")

    print("", flush=True)

    return i16rErrorCode

# update particular typeid and IOA FROM USER INPUT
def update(myServer):

    i16ErrorCode = ctypes.c_short()
    tErrorValue =  ctypes.c_short()
    
    print("UPDATE CALLED")
    while True:
        try:
            u32ioa = ctypes.c_uint32(int(input("MeasuredFloat(M_ME_TF_1) Enter Information object address(IOA)- 100 to 109 ")))
        except ValueError:
            print("Please enter a number 100 to 109")
        else:
            break

    while True:
        try:
            f32value = ctypes.c_float(float(input("Enter update float value: ")))
        except ValueError:
            print("Please enter a float number ")
        else:
            break

   
    psDAID = sIEC101DataAttributeID()
    psNewValue  = sIEC101DataAttributeData()

    psDAID.u16SerialPortNumber    =   1
    psDAID.u16DataLinkAddress    =   1
    psDAID.u16CommonAddress                     =  1
    psDAID.eTypeID                              =  eIEC870TypeID.M_ME_TF_1
    psDAID.u32IOA                               =   u32ioa
    psDAID.pvUserData                           =   None
    psNewValue.tQuality                         =   eIEC870QualityFlags.GD

    psNewValue.pvData                           =   ctypes.cast(ctypes.pointer(f32value),ctypes.c_void_p)
    psNewValue.eDataType                        =   eDataTypes.FLOAT32_DATA
    psNewValue.eDataSize                        =   eDataSizes.FLOAT32_SIZE

    now = time.time()
    timeinfo = time.localtime(now)
    
    #current date
    psNewValue.sTimeStamp.u8Day = timeinfo.tm_mday
    psNewValue.sTimeStamp.u8Month = timeinfo.tm_mon
    psNewValue.sTimeStamp.u16Year = timeinfo.tm_year 

    psNewValue.sTimeStamp.u8Hour = timeinfo.tm_hour
    psNewValue.sTimeStamp.u8Minute = timeinfo.tm_min
    psNewValue.sTimeStamp.u8Seconds = timeinfo.tm_sec
    psNewValue.sTimeStamp.u16MilliSeconds = 0
    psNewValue.sTimeStamp.u16MicroSeconds = 0
    psNewValue.sTimeStamp.i8DSTTime = 0
    psNewValue.sTimeStamp.u8DayoftheWeek = 4
    psNewValue.bTimeInvalid = False

    #printf(" update float value %f",f32data);
    # Update server
   
    i16ErrorCode = iec101_lib.IEC101Update(myServer, True,ctypes.byref(psDAID),ctypes.byref(psNewValue),1,ctypes.byref((tErrorValue)))
    if i16ErrorCode != 0:
        message = f"IEC 60870-5-101 Library API Function - IEC101Update() failed: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message)     

    else:
        message = f"IEC 60870-5-101 Library API Function - IEC101Update() success: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message) 

# main program
def main():
    print(" \t\t**** IEC 60870-5-101 Protocol Server Library Test ****")
    # Check library version against the library header file
    if iec101_lib.IEC101GetLibraryVersion().decode("utf-8") != IEC101_VERSION:
        print(" Error: Version Number Mismatch")
        print(" Library Version is  : {}".format(iec101_lib.IEC101GetLibraryVersion().decode("utf-8")))
        print(" The Header Version used is : {}".format(IEC101_VERSION))
        print("")
        input(" Press Enter to free IEC 101 Server object")
        exit(0)

    print(" Library Version is : {}".format(iec101_lib.IEC101GetLibraryVersion().decode("utf-8")))
    print(" Library Build on   : {}".format(iec101_lib.IEC101GetLibraryBuildTime().decode("utf-8")))
    print(" Library License Information   : {}".format(iec101_lib.IEC101GetLibraryLicenseInfo().decode("utf-8")))

    i16ErrorCode = ctypes.c_short()
    tErrorValue =  ctypes.c_short()

    sParameters = sIEC101Parameters()

   

    # Initialize IEC 60870-5-104 Server object parameters
    sParameters.eAppFlag          =  eApplicationFlag.APP_SERVER        # This is a IEC104 Server      
    sParameters.ptReadCallback    = IEC101ReadCallback(cbRead)               # Read Callback
    sParameters.ptWriteCallback   = IEC101WriteCallback(cbWrite)                # Write Callback
    sParameters.ptUpdateCallback  = ctypes.cast(None,IEC101UpdateCallback) #IEC104UpdateCallback(0)                 # Update Callback
    sParameters.ptSelectCallback  = IEC101ControlSelectCallback(cbSelect)               # Select Callback
    sParameters.ptOperateCallback = IEC101ControlOperateCallback(cbOperate)              # Operate Callback
    sParameters.ptCancelCallback  = IEC101ControlCancelCallback(cbCancel)              # Cancel Callback
    sParameters.ptFreezeCallback  = IEC101ControlFreezeCallback(cbFreeze)              # Freeze Callback
    sParameters.ptDebugCallback   = IEC101DebugMessageCallback(cbDebug)                # Debug Callback
    sParameters.ptPulseEndActTermCallback = IEC101ControlPulseEndActTermCallback(cbpulseend)    # pulse end callback
    sParameters.ptParameterActCallback = IEC101ParameterActCallback(cbParameterAct)   # Parameter activation callback
    sParameters.ptDirectoryCallback    = IEC101DirectoryCallback(0)              # Directory Callback
    sParameters.ptClientStatusCallback   = IEC101ClientStatusCallback(0)           # client connection status Callback
    sParameters.u32Options        = 0
    sParameters.u16ObjectId				= 1				#Server ID which used in callbacks to identify the iec 104 server object   


    # Create a server object

    myServer =  iec101_lib.IEC101Create(ctypes.byref(sParameters), ctypes.byref((i16ErrorCode)), ctypes.byref((tErrorValue)))
    if i16ErrorCode.value != 0:
        message = f"IEC 60870-5-101 Library API Function - IEC101Create() failed: {i16ErrorCode.value} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message)    
        exit(0) 
    else:
        message = f"IEC 60870-5-101 Library API Function - IEC101Create() success: {i16ErrorCode.value} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message) 


    while(True):

        sIEC101Config = sIEC101ConfigurationParameters()       


        sIEC101Config.sServerSet.u8NumberofSerialPortConnections    =   1
        # Allocate memory for objects
        
        

        arraypointer = (sSerialCommunicationSettings  * sIEC101Config.sServerSet.u8NumberofSerialPortConnections )()
        sIEC101Config.sServerSet.psSerialSet = ctypes.cast(arraypointer, ctypes.POINTER(sSerialCommunicationSettings))

        arraypointer[0].eSerialType   =  eSerialTypes.SERIAL_RS232
        # check computer configuration serial com port number,  if server and client application running in same system, we can use com0com
        arraypointer[0].u16SerialPortNumber   =   1
        arraypointer[0].eSerialBitRate       =   eSerialBitRate.BITRATE_9600
        arraypointer[0].eWordLength          =   eSerialWordLength.WORDLEN_8BITS
        arraypointer[0].eSerialParity        =   eSerialParity.EVEN
        arraypointer[0].eStopBits            =   eSerialStopBits.STOPBIT_1BIT

        #serial port flow control
        arraypointer[0].sFlowControl.bWinCTSoutputflow         =  False
        arraypointer[0].sFlowControl.bWinDSRoutputflow         =  False
        arraypointer[0].sFlowControl.eWinDTR					  =	 eWinDTRcontrol.WIN_DTR_CONTROL_DISABLE
        arraypointer[0].sFlowControl.eWinRTS					  =   eWinRTScontrol.WIN_RTS_CONTROL_DISABLE
        arraypointer[0].sFlowControl.eLinuxFlowControl         = eLinuxSerialFlowControl.FLOW_NONE

        arraypointer[0].sRxTimeParam.u16CharacterTimeout     =   1
        arraypointer[0].sRxTimeParam.u16MessageTimeout       =   0
        arraypointer[0].sRxTimeParam.u16InterCharacterDelay  =   5
        arraypointer[0].sRxTimeParam.u16PostDelay            =   0
        arraypointer[0].sRxTimeParam.u16PreDelay             =   0
        arraypointer[0].sRxTimeParam.u8CharacterRetries      =   20
        arraypointer[0].sRxTimeParam.u8MessageRetries        =   0

        sIEC101Config.sServerSet.sServerProtSet.eDataLink                =   eDataLinkTransmission.UNBALANCED_MODE

        sIEC101Config.sServerSet.sServerProtSet.elinkAddrSize            =   eDataLinkAddressSize.DL_TWO_BYTE
        sIEC101Config.sServerSet.sServerProtSet.u16DataLinkAddress       =   1
        sIEC101Config.sServerSet.sServerProtSet.eCOTsize                 =   eCauseofTransmissionSize.COT_TWO_BYTE
        sIEC101Config.sServerSet.sServerProtSet.eIOAsize                 =   eInformationObjectAddressSize.IOA_THREE_BYTE
        sIEC101Config.sServerSet.sServerProtSet.eCASize                  =   eCommonAddressSize.CA_TWO_BYTE
        sIEC101Config.sServerSet.sServerProtSet.u8TotalNumberofStations  =   1
        sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[0]     =   1
        sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[1]     =   0
        sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[2]     =   0
        sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[3]     =   0
        sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[4]     =   0



        sIEC101Config.sServerSet.sServerProtSet.eNegACK  = eNegativeACK.FIXED_FRAME_NACK
        sIEC101Config.sServerSet.sServerProtSet.ePosACK  =   ePositiveACK.SINGLE_CHAR_ACK_E5

        sIEC101Config.sServerSet.sServerProtSet.u16Class1EventBufferSize =   5000
        sIEC101Config.sServerSet.sServerProtSet.u16Class2EventBufferSize =   5000

        sIEC101Config.sServerSet.sServerProtSet.u8Class1BufferOverFlowPercentage     =   90
        sIEC101Config.sServerSet.sServerProtSet.u8Class2BufferOverFlowPercentage     =   90
        sIEC101Config.sServerSet.sServerProtSet.u8MaxAPDUSize                        =   253
        sIEC101Config.sServerSet.sServerProtSet.u16ShortPulseTime                    =   5000
        sIEC101Config.sServerSet.sServerProtSet.u16LongPulseTime                     =   10000
        sIEC101Config.sServerSet.sServerProtSet.u32ClockSyncPeriod                   =   0
        sIEC101Config.sServerSet.sServerProtSet.bGenerateACTTERMrespond              =   True


        sIEC101Config.sServerSet.sServerProtSet.u32BalancedModeTestConnectionSignalInterval  = 60

        # File transfer protocol configuration parameters
        sIEC101Config.sServerSet.sServerProtSet.bEnableFileTransfer = False
        sIEC101Config.sServerSet.sServerProtSet.ai8FileTransferDirPath =  "//FileTransferServer//".encode('utf-8')
        sIEC101Config.sServerSet.sServerProtSet.u16MaxFilesInDirectory    = 10



        sIEC101Config.sServerSet.sDebug.u32DebugOptions     =   (eDebugOptionsFlag.DEBUG_OPTION_RX | eDebugOptionsFlag.DEBUG_OPTION_TX)


        # Debug option settings
        if  'VIEW_TRAFFIC' in globals():
            sIEC101Config.sServerSet.sDebug.u32DebugOptions   =   (eDebugOptionsFlag.DEBUG_OPTION_RX | eDebugOptionsFlag.DEBUG_OPTION_TX)
        else:
            sIEC101Config.sServerSet.sDebug.u32DebugOptions  =   0

        sIEC101Config.sServerSet.sServerProtSet.bTransmitSpontMeasuredValue = True
        sIEC101Config.sServerSet.sServerProtSet.bTransmitInterrogationMeasuredValue = True
        sIEC101Config.sServerSet.sServerProtSet.bTransmitBackScanMeasuredValue = True

        sIEC101Config.sServerSet.sServerProtSet.u8InitialdatabaseQualityFlag = eIEC870QualityFlags.GD  # 0- good/valid, 1 BIT- iv, 2 BIT-nt,  MAX VALUE -3   */
        sIEC101Config.sServerSet.sServerProtSet.bUpdateCheckTimestamp = True # if it true ,the timestamp change also generate event  during the iec104update */

        # Allocate memory for objects
        sIEC101Config.sServerSet.u16NoofObject           = 2;       # Define number of objects





        sIEC101Config.sServerSet.psIEC101Objects  = ( sIEC101Object * sIEC101Config.sServerSet.u16NoofObject)()




        sIEC101Config.sServerSet.psIEC101Objects[0].ai8Name = "M_ME_TF_1 100-109".encode('utf-8')
        sIEC101Config.sServerSet.psIEC101Objects[0].eTypeID     =  eIEC870TypeID.M_ME_TF_1
        sIEC101Config.sServerSet.psIEC101Objects[0].u32IOA          = 100
        sIEC101Config.sServerSet.psIEC101Objects[0].u16Range        = 10
        sIEC101Config.sServerSet.psIEC101Objects[0].eIntroCOT       = eIEC870COTCause.INRO6
        sIEC101Config.sServerSet.psIEC101Objects[0].eControlModel   =   eControlModelConfig.STATUS_ONLY
        sIEC101Config.sServerSet.psIEC101Objects[0].u32SBOTimeOut   =   0
        sIEC101Config.sServerSet.psIEC101Objects[0].u16CommonAddress    =   1
        sIEC101Config.sServerSet.psIEC101Objects[0].eClass          =   eIECClass.IEC_CLASS1

        #Second object detail
        sIEC101Config.sServerSet.psIEC101Objects[1].ai8Name = "C_SE_TC_1".encode('utf-8')
        sIEC101Config.sServerSet.psIEC101Objects[1].eTypeID     =  eIEC870TypeID.C_SE_TC_1
        sIEC101Config.sServerSet.psIEC101Objects[1].u32IOA          = 100
        sIEC101Config.sServerSet.psIEC101Objects[1].eIntroCOT       = eIEC870COTCause.NOTUSED
        sIEC101Config.sServerSet.psIEC101Objects[1].u16Range        = 10
        sIEC101Config.sServerSet.psIEC101Objects[1].eControlModel  = eControlModelConfig.DIRECT_OPERATE
        sIEC101Config.sServerSet.psIEC101Objects[1].u32SBOTimeOut   = 0
        sIEC101Config.sServerSet.psIEC101Objects[1].u16CommonAddress    =   1
        sIEC101Config.sServerSet.psIEC101Objects[1].eClass          =   eIECClass.IEC_NO_CLASS

            

        i16ErrorCode =  iec101_lib.IEC101LoadConfiguration(myServer, ctypes.byref(sIEC101Config), ctypes.byref((tErrorValue)))
        if i16ErrorCode != 0:
            message = f"IEC 60870-5-101 Library API Function - IEC101LoadConfiguration() failed: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
            print(message)    
            break

        else:
            message = f"IEC 60870-5-101 Library API Function - IEC101LoadConfiguration() success: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
            print(message) 



        i16ErrorCode =  iec101_lib.IEC101Start(myServer, ctypes.byref((tErrorValue)))
        if i16ErrorCode != 0:
            message = f"IEC 60870-5-101 Library API Function - IEC101Start() failed: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
            print(message)    
            break

        else:
            message = f"IEC 60870-5-101 Library API Function - IEC101Start() success: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
            print(message) 

        print("press x to exit")

        while(True):
            if keyboard.is_pressed('x'):
                print("x pressed, exiting loop")
                keyboard.release('x')
                time.sleep(0.1)
                break
            elif keyboard.is_pressed('u'):
                print("u pressed, update called")
                keyboard.release('u')
                time.sleep(0.1)
                update(myServer)

            #Xprint("sleep called")
            time.sleep(50 /1000)

        break
            
            

      



    i16ErrorCode =  iec101_lib.IEC101Stop(myServer, ctypes.byref((tErrorValue)))
    if i16ErrorCode != 0:
        message = f"IEC 60870-5-101 Library API Function - IEC101Stop() failed: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message)        
    else:
        message = f"IEC 60870-5-101 Library API Function - IEC101Stop() success: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message) 



    i16ErrorCode =  iec101_lib.IEC101Free(myServer, ctypes.byref((tErrorValue)))
    if i16ErrorCode != 0:
        message = f"IEC 60870-5-101 Library API Function - IEC101Free() failed: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message)    
    else:
        message = f"IEC 60870-5-101 Library API Function - IEC101Free() success: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message) 




    print("Exiting the program...")
    

if __name__ == "__main__":
    main()