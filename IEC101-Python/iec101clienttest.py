import ctypes 
import time
import struct
import sys
import keyboard
from pyiec101.iec101api import *


# enbale to view traffic
VIEW_TRAFFIC = 1

# print the struct sIEC101DataAttributeID and sIEC101DataAttributeData
def vPrintDataInformation(psIEC101DataAttributeID , psIEC101DataAttributeData ):
 
    print(f" Link Address {psIEC101DataAttributeID.contents.u16DataLinkAddress}")
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

# update callback
def cbUpdate(u16ObjectId, psIEC101DataAttributeID, psIEC101DataAttributeData, psIEC101UpdateParameters, ptErrorValue):
    i16rErrorCode = ctypes.c_short()
    i16rErrorCode = 0   
    print(" cbUpdate() called ")
    print(" Client ID : %u" % u16ObjectId)
    vPrintDataInformation(psIEC101DataAttributeID, psIEC101DataAttributeData)
    message = f" COT {psIEC101UpdateParameters.contents.eCause}"
    print(message)
    
    return i16rErrorCode

# Client Status Callback
def cbClientStatus(u16ObjectId, psIEC101ClientConnectionID , peSat, ptErrorValue):

    i16rErrorCode = ctypes.c_short()
    i16rErrorCode = 0   
    print(" cbClientStatus called -  from IEC101 client")

    print(" Client ID : %u" % u16ObjectId)
    
    print("  DataLink Address %u  Serial port number %u " % (psIEC101ClientConnectionID.contents.u16DataLinkAddress, psIEC101ClientConnectionID.contents.u16SerialPortNumber))

    if peSat.contents.value == eStatus.CONNECTED:
        print(" Status - Connected")
    else:
        print(" Status - Disconnected")
    
   
    return i16rErrorCode

# Debug callback
def cbDebug(u16ObjectId,  psIEC101DebugData , ptErrorValue):
    
    i16rErrorCode = ctypes.c_short()
    i16rErrorCode = 0 

   # u16nav = ctypes.c_ushort()
    u16nav = 0

    
   
    #print(" cbDebug() called")
    
    print(f" {psIEC101DebugData.contents.sTimeStamp.u8Hour}:{psIEC101DebugData.contents.sTimeStamp.u8Minute}:{psIEC101DebugData.contents.sTimeStamp.u8Seconds} Server ID: {u16ObjectId}", end='')
    
    if (psIEC101DebugData.contents.u32DebugOptions & eDebugOptionsFlag.DEBUG_OPTION_TX) == eDebugOptionsFlag.DEBUG_OPTION_TX:
        print(f" client id {u16ObjectId}  transmit com Port {psIEC101DebugData.contents.u16ComportNumber}", end='')
        print(" ->", end='')      
        u16nav = 0
        for u16nav in range(int(psIEC101DebugData.contents.u16TxCount)):
            #print(f" {psIEC101DebugData.contents.au8TxData[u16nav]:02x}", end='')
            try:
                print(f" {psIEC101DebugData.contents.au8TxData[u16nav]:02x}", end='')
            except TypeError:
                print("TypeError: Check list of indices")
        
    
        
    if (psIEC101DebugData.contents.u32DebugOptions & eDebugOptionsFlag.DEBUG_OPTION_RX) == eDebugOptionsFlag.DEBUG_OPTION_RX:
        print(f" client id {u16ObjectId}  receive com Port {psIEC101DebugData.contents.u16ComportNumber}", end='')
        print(" <-", end='')

        #print(f"u16RxCount - {psIEC101DebugData.contents.u16RxCount} len aaray - {len(psIEC101DebugData.contents.au8RxData)}")

        
        for u16nav in range(int(psIEC101DebugData.contents.u16RxCount)):
            print(f" {psIEC101DebugData.contents.au8RxData[u16nav]:02x}", end='')
      

        
    if (psIEC101DebugData.contents.u32DebugOptions & eDebugOptionsFlag.DEBUG_OPTION_ERROR) == eDebugOptionsFlag.DEBUG_OPTION_ERROR:
        print(f" Error message {psIEC101DebugData.contents.au8ErrorMessage}")
        print(f" ErrorCode {psIEC101DebugData.contents.iErrorCode}")
        print(f" ErrorValue {psIEC101DebugData.contents.tErrorvalue}")  

    print("", flush=True)  
    
    return i16rErrorCode

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

# send command for particular typeid and IOA FROM USER INPUT
def sendCommand(myClient):

    i16ErrorCode = ctypes.c_short()
    tErrorValue =  ctypes.c_short()
    
    print("sendCommand CALLED")
    while True:
        try:
            u32ioa = ctypes.c_uint32(int(input("C_SE_TC_1 command Enter Information object address(IOA) ")))
        except ValueError:
            print("Please enter a number -ioa")
        else:
            break

    while True:
        try:
            f32value = ctypes.c_float(float(input("Enter command float value: ")))
        except ValueError:
            print("Please enter a float number ")
        else:
            break

   
    psDAID = sIEC101DataAttributeID()
    psNewValue  = sIEC101DataAttributeData()
    psIEC104CommandParameters = sIEC101CommandParameters()


    
    psDAID.u16SerialPortNumber   =   2
    psDAID.u16DataLinkAddress=  1
    psDAID.u16CommonAddress=    1
    psIEC104CommandParameters.u8OriginatorAddress  =   1
    psIEC104CommandParameters.eQOCQU   =   eCommandQOCQU.NOADDDEF


    psDAID.eTypeID                              =  eIEC870TypeID.C_SE_TC_1
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
   
    i16ErrorCode = iec101_lib.IEC101Operate(myClient, ctypes.byref(psDAID), ctypes.byref(psNewValue),ctypes.byref(psIEC104CommandParameters),ctypes.byref((tErrorValue)))
    if i16ErrorCode != 0:
        message = f"IEC 60870-5-104 Library API Function - IEC104Operate() failed: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message)     

    else:
        message = f"IEC 60870-5-104 Library API Function - IEC104Operatee() success: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message) 

# main program
def main():
    
    print(" \t\t**** IEC 60870-5-101 Protocol Client Library Test ****")
    
    # Check library version against the library header file
    if iec101_lib.IEC101GetLibraryVersion().decode("utf-8") != IEC101_VERSION:
        print(" Error: Version Number Mismatch")
        print(" Library Version is  : {}".format(iec101_lib.IEC101GetLibraryVersion().decode("utf-8")))
        print(" The Header Version used is : {}".format(IEC101_VERSION))
        print("")
        input(" Press Enter to free IEC 101 client object")
        exit(0)

    print(" Library Version is : {}".format(iec101_lib.IEC101GetLibraryVersion().decode("utf-8")))
    print(" Library Build on   : {}".format(iec101_lib.IEC101GetLibraryBuildTime().decode("utf-8")))
    print(" Library License Information   : {}".format(iec101_lib.IEC101GetLibraryLicenseInfo().decode("utf-8")))

    i16ErrorCode = ctypes.c_short()
    tErrorValue =  ctypes.c_short()

    sParameters = sIEC101Parameters()

   

    # Initialize IEC 60870-5-101 Client object parameters
    sParameters.eAppFlag          =  eApplicationFlag.APP_CLIENT        # This is a IEC101 Client      
    sParameters.ptReadCallback    = IEC101ReadCallback(0)               # Read Callback
    sParameters.ptWriteCallback   = IEC101WriteCallback(0)                # Write Callback
    sParameters.ptUpdateCallback  = IEC101UpdateCallback(cbUpdate)                 # Update Callback
    sParameters.ptSelectCallback  = IEC101ControlSelectCallback(0)               # Select Callback
    sParameters.ptOperateCallback = IEC101ControlOperateCallback(0)              # Operate Callback
    sParameters.ptCancelCallback  = IEC101ControlCancelCallback(0)              # Cancel Callback
    sParameters.ptFreezeCallback  = IEC101ControlFreezeCallback(0)              # Freeze Callback
    sParameters.ptDebugCallback   = IEC101DebugMessageCallback(cbDebug)                # Debug Callback
    sParameters.ptPulseEndActTermCallback = IEC101ControlPulseEndActTermCallback(0)    # pulse end callback
    sParameters.ptParameterActCallback = IEC101ParameterActCallback(0)   # Parameter activation callback
    sParameters.ptDirectoryCallback    = IEC101DirectoryCallback(0)              # Directory Callback
    sParameters.ptClientStatusCallback   = IEC101ClientStatusCallback(cbClientStatus)           # client connection status Callback
    sParameters.u32Options        = 0
    sParameters.u16ObjectId				= 1				#Client ID which used in callbacks to identify the iec 101 Client object   


    # Create a CLIENT object

    myClient =  iec101_lib.IEC101Create(ctypes.byref(sParameters), ctypes.byref((i16ErrorCode)), ctypes.byref((tErrorValue)))
    if i16ErrorCode.value != 0:
        message = f"IEC 60870-5-101 Library API Function - IEC101Create() failed: {i16ErrorCode.value} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message)    
        exit(0) 
    else:
        message = f"IEC 60870-5-101 Library API Function - IEC101Create() success: {i16ErrorCode.value} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message) 

    while(True):



        sIEC101Config = sIEC101ConfigurationParameters()
        sIEC101Config.sClientSet.eLink  =   eDataLinkTransmission.UNBALANCED_MODE
        sIEC101Config.sClientSet.benabaleUTCtime    =   False
        
        # Debug option settings
        if  'VIEW_TRAFFIC' in globals():
            sIEC101Config.sClientSet.sDebug.u32DebugOptions   =   (eDebugOptionsFlag.DEBUG_OPTION_RX | eDebugOptionsFlag.DEBUG_OPTION_TX)
        else:
            sIEC101Config.sClientSet.sDebug.u32DebugOptions  =   0
        
        
        sIEC101Config.sClientSet.bAutoGenIEC101DataObjects  = True  # if it true ,the IEC101 Objects created automaticallay, use u16NoofObject = 0, psIEC104Objects = NULL*/
       
        sIEC101Config.sClientSet.u8NoofClient   =   1

        arraypointer = (sIEC101ClientObject * sIEC101Config.sClientSet.u8NoofClient )()
        sIEC101Config.sClientSet.psClientObjects  = ctypes.cast(arraypointer, ctypes.POINTER(sIEC101ClientObject))

        
        
       

        arraypointer[0].sSerialSet.eSerialType   = eSerialTypes.SERIAL_RS232
		# check computer configuration serial com port number,  if server and client application running in same system, we can use com0com
        arraypointer[0].sSerialSet.u16SerialPortNumber   =   2
        arraypointer[0].sSerialSet.eSerialBitRate       =   eSerialBitRate.BITRATE_9600
        arraypointer[0].sSerialSet.eWordLength          =   eSerialWordLength.WORDLEN_8BITS
        arraypointer[0].sSerialSet.eSerialParity        =   eSerialParity.EVEN
        arraypointer[0].sSerialSet.eStopBits            =   eSerialStopBits.STOPBIT_1BIT
       
		#serial port flow control
        arraypointer[0].sSerialSet.sFlowControl.bWinCTSoutputflow         =  False
        arraypointer[0].sSerialSet.sFlowControl.bWinDSRoutputflow         =  False
        arraypointer[0].sSerialSet.sFlowControl.eWinDTR					  =	 eWinDTRcontrol.WIN_DTR_CONTROL_DISABLE
        arraypointer[0].sSerialSet.sFlowControl.eWinRTS					  =  eWinRTScontrol.WIN_RTS_CONTROL_DISABLE
        arraypointer[0].sSerialSet.sFlowControl.eLinuxFlowControl         =  eLinuxSerialFlowControl.FLOW_NONE
	   
		
		
        arraypointer[0].sSerialSet.sRxTimeParam.u16CharacterTimeout     =   1
        arraypointer[0].sSerialSet.sRxTimeParam.u16MessageTimeout       =   0
        arraypointer[0].sSerialSet.sRxTimeParam.u16InterCharacterDelay  =   5
        arraypointer[0].sSerialSet.sRxTimeParam.u16PostDelay            =   1
        arraypointer[0].sSerialSet.sRxTimeParam.u16PreDelay             =   1
        arraypointer[0].sSerialSet.sRxTimeParam.u8CharacterRetries      =   20
        arraypointer[0].sSerialSet.sRxTimeParam.u8MessageRetries        =   0

        

        arraypointer[0].sClientProtSet.eCASize  =   eCommonAddressSize.CA_TWO_BYTE
        arraypointer[0].sClientProtSet.eCOTsize =   eCauseofTransmissionSize.COT_TWO_BYTE
        arraypointer[0].sClientProtSet.u8OriginatorAddress  =   1
        arraypointer[0].sClientProtSet.eIOAsize =   eInformationObjectAddressSize.IOA_THREE_BYTE
        arraypointer[0].sClientProtSet.elinkAddrSize    =   eDataLinkAddressSize.DL_TWO_BYTE
        arraypointer[0].sClientProtSet.u16DataLinkAddress   =   1
        arraypointer[0].sClientProtSet.u8TotalNumberofStations  =   1
        arraypointer[0].sClientProtSet.au16CommonAddress[0]     =   1
        arraypointer[0].sClientProtSet.au16CommonAddress[1]     =   0
        arraypointer[0].sClientProtSet.au16CommonAddress[2]     =   0
        arraypointer[0].sClientProtSet.au16CommonAddress[3]     =   0
        arraypointer[0].sClientProtSet.au16CommonAddress[4]     =   0
        
        arraypointer[0].sClientProtSet.u32LinkLayerTimeout  =   5000
        arraypointer[0].sClientProtSet.u32PollInterval  =   100

        arraypointer[0].sClientProtSet.u32GeneralInterrogationInterval  =   5    # in sec if 0 , gi will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group1InterrogationInterval   =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group2InterrogationInterval   =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group3InterrogationInterval   =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group4InterrogationInterval   =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group5InterrogationInterval   =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group6InterrogationInterval   =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group7InterrogationInterval   =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group8InterrogationInterval   =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group9InterrogationInterval   =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group10InterrogationInterval  =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group11InterrogationInterval  =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group12InterrogationInterval  =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group13InterrogationInterval  =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group14InterrogationInterval  =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group15InterrogationInterval  =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group16InterrogationInterval  =   0    # in sec if 0 , group 1 interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32CounterInterrogationInterval  =   5    # in sec if 0 , ci will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group1CounterInterrogationInterval    =   0    # in sec if 0 , group 1 counter interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group2CounterInterrogationInterval    =   0    # in sec if 0 , group 1 counter interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group3CounterInterrogationInterval    =   0    # in sec if 0 , group 1 counter interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32Group4CounterInterrogationInterval    =   0    # in sec if 0 , group 1 counter interrogation will not send in particular interval*/
        arraypointer[0].sClientProtSet.u32ClockSyncInterval =   5              # in sec if 0 , clock sync, will not send in particular interval */


        arraypointer[0].sClientProtSet.u32CommandTimeout    =   10000
        arraypointer[0].sClientProtSet.bCommandResponseActtermUsed  =   True

        # File transfer protocol configuration parameters
        arraypointer[0].sClientProtSet.bEnableFileTransfer  =   False
        arraypointer[0].sClientProtSet.u32FileTransferTimeout           = 1000000
        arraypointer[0].sClientProtSet.ai8FileTransferDirPath = "//FileTest//".encode('utf-8')


        arraypointer[0].u16NoofObject           = 0;        # Define number of objects
        arraypointer[0].psIEC101Objects = None



        # client 1 configuration ends

       
        i16ErrorCode =  iec101_lib.IEC101LoadConfiguration(myClient, ctypes.byref(sIEC101Config), ctypes.byref((tErrorValue)))
        if i16ErrorCode != 0:
            message = f"IEC 60870-5-101 Library API Function - IEC101LoadConfiguration() failed: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
            print(message)    
            break

        else:
            message = f"IEC 60870-5-101 Library API Function - IEC101LoadConfiguration() success: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
            print(message) 



        i16ErrorCode =  iec101_lib.IEC101Start(myClient, ctypes.byref((tErrorValue)))
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
            elif keyboard.is_pressed('s'):
                print("u pressed, send command called")
                keyboard.release('s')
                time.sleep(0.1)
                sendCommand(myClient)

            #Xprint("sleep called")
            time.sleep(0.1)

        break
            
            

      



    i16ErrorCode =  iec101_lib.IEC101Stop(myClient, ctypes.byref((tErrorValue)))
    if i16ErrorCode != 0:
        message = f"IEC 60870-5-101 Library API Function - IEC101Stop() failed: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message)        
    else:
        message = f"IEC 60870-5-101 Library API Function - IEC101Stop() success: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message) 



    i16ErrorCode =  iec101_lib.IEC101Free(myClient, ctypes.byref((tErrorValue)))
    if i16ErrorCode != 0:
        message = f"IEC 60870-5-101 Library API Function - IEC101Free() failed: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message)    
    else:
        message = f"IEC 60870-5-101 Library API Function - IEC101Free() success: {i16ErrorCode} - {errorcodestring(i16ErrorCode)}, {tErrorValue.value} - {errorvaluestring(tErrorValue)}"
        print(message) 


    print("Exiting the program...")
    
    

if __name__ == "__main__":
    main()
