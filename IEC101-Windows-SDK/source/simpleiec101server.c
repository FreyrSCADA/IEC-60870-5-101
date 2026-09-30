/******************************************************************************
*
* (c) 2026, 2027 by FreyrSCADA Embedded Solution Pvt Ltd
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
/*! \file       simpleiec101server.c
 *  \brief      C Source code file, IEC 60870-5-101 Server library test program
 *
 *  \par        FreyrSCADA Embedded Solution Pvt Ltd
 *              Email   : tech.support@freyrscada.com
 */
/*****************************************************************************/

/******************************************************************************
* Includes
******************************************************************************/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <process.h>

#include "tgttypes.h"
#include "iec101api.h"

/*! \brief - in a loop simulate update - for particular IOA , value changes - generates a event  */
#define SIMULATE_UPDATE 1

/*! \brief -  check computer configuration serial com port number,  if server and client application running in same system, we can use com0com */      
#define SERIAL_PORT_NUMBER 1

/*! \brief - Enable traffic flags to show transmit and receive signal  */
#define VIEW_TRAFFIC 1


/******************************************************************************
* Error code - Print information
******************************************************************************/
const char *  errorcodestring(int errorcode)
{
     struct sIEC101ErrorCode sIEC101ErrorCodeDes  = {0};
     const char *i8ReturnedMessage = " ";

     sIEC101ErrorCodeDes.iErrorCode = errorcode;

     IEC101ErrorCodeString(&sIEC101ErrorCodeDes);

     i8ReturnedMessage = sIEC101ErrorCodeDes.LongDes;

     return (i8ReturnedMessage);
}

/******************************************************************************
* Error value - Print information
******************************************************************************/
const char *  errorvaluestring(int errorvalue)
{
    struct sIEC101ErrorValue sIEC101ErrorValueDes  = {0};
     const char *i8ReturnedMessage = " ";

     sIEC101ErrorValueDes.iErrorValue = errorvalue;

     IEC101ErrorValueString(&sIEC101ErrorValueDes);

     i8ReturnedMessage = sIEC101ErrorValueDes.LongDes;

     return (i8ReturnedMessage);
}

/******************************************************************************
* Print information
******************************************************************************/
void vPrintDataInformation(struct sIEC101DataAttributeID * psPrintID, struct sIEC101DataAttributeData * psData)
{

    Unsigned8 u8data        = 0;
    Integer8 i8data         = 0;
    Unsigned16 u16data      = 0;
    Integer16 i16data       = 0;
    Float32   f32data       = 0;
    Integer32 i32data       = 0;
    Unsigned32 u32data      = 0;

  if(psPrintID == NULL)
  {
    printf("\r\n Data Attribute ID is NULL");
    return;
  }

  if(psData == NULL)
  {
    printf("\r\n Data is NULL");
    return;
  }

  printf("\r\n Data Link Address %u",psPrintID->u16DataLinkAddress);
  printf("\r\n Station Address %u",psPrintID->u16CommonAddress);

  printf("\r\n Data Attribute Type ID -  %u, IOA - %u ", psPrintID->eTypeID, psPrintID->u32IOA);
  printf("\r\n Data is Datatype->%u Datasize->%u ", psData->eDataType, psData->eDataSize );


  if(psData->tQuality != GD)
    {

        /* Now for the Status */
        if((psData->tQuality & IV) == IV)
        {
            printf("\r\nIEC_INVALID_FLAG");
        }

        if((psData->tQuality & NT) == NT)
        {
            printf("\r\n IEC_NONTOPICAL_FLAG");
        }

        if((psData->tQuality & SB) == SB)
        {
            printf("\r\n IEC_SUBSTITUTED_FLAG");
        }

        if((psData->tQuality & BL) == BL)
        {
            printf("\r\nIEC_BLOCKED_FLAG");
        }

    }

    switch(psData->eDataType)
    {
        case SINGLE_POINT_DATA:
        case DOUBLE_POINT_DATA:
        case UNSIGNED_BYTE_DATA:

            memcpy(&u8data,psData->pvData,sizeof(Unsigned8));
            printf("\r\n Data : %u",u8data);
            break;

        case SIGNED_BYTE_DATA :
            memcpy(&i8data,psData->pvData,sizeof(Unsigned8));
            printf("\r\n Data : %d",i8data);
            break;

        case UNSIGNED_WORD_DATA:
            memcpy(&u16data,psData->pvData,sizeof(Unsigned16));
            printf("\r\n Data : %u",u16data);
            break;

        case SIGNED_WORD_DATA :
            memcpy(&i16data,psData->pvData,sizeof(Unsigned16));
            printf("\r\n Data : %d",i16data);
            break;

        case  UNSIGNED_DWORD_DATA :
            memcpy(&u32data,psData->pvData,sizeof(Unsigned32));
            printf("\r\n Data : %u",u32data);
            break;

        case SIGNED_DWORD_DATA :
            memcpy(&i32data,psData->pvData,sizeof(Unsigned32));
            printf("\r\n Data : %d",i32data);
            break;

        case  FLOAT32_DATA :
            memcpy(&f32data,psData->pvData,sizeof(Unsigned32));
            printf("\r\n Data : %0.3f",f32data);
            break;

        default:
            break;
    }

   if( psData->sTimeStamp.u16Year != 0 )
    {
        printf( "\r\n Date : %02u-%02u-%04u  DOW -%02u",psData->sTimeStamp.u8Day,psData->sTimeStamp.u8Month, psData->sTimeStamp.u16Year,psData->sTimeStamp.u8DayoftheWeek);

        printf( "\r\n Time : %02u:%02u:%02u:%04u", psData->sTimeStamp.u8Hour, psData->sTimeStamp.u8Minute, psData->sTimeStamp.u8Seconds, psData->sTimeStamp.u16MilliSeconds );
    }
}

/******************************************************************************
* Read callback
******************************************************************************/
Integer16 cbRead(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID * psReadID, struct sIEC101DataAttributeData * psReadValue, struct sIEC101ReadParameters * psReadParams, tErrorValue * ptErrorValue)
{
    Integer16 i16ErrorCode = EC_NONE;

    printf("\n\r\n cbRead() called");
	printf("\r\n Server ID : %u", u16ObjectId);
	vPrintDataInformation(psReadID, psReadValue);
    printf("\r\n Orginator Address %u",psReadParams->u8OriginatorAddress);

 

    return i16ErrorCode;
}


/******************************************************************************
* Write callback
******************************************************************************/

Integer16 cbWrite(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID * ptWriteID, struct sIEC101DataAttributeData * psWriteValue, struct sIEC101WriteParameters * psWriteParams, tErrorValue *ptErrorValue)
{
    Integer16 i16ErrorCode = EC_NONE;

    printf("\n\r\n cbWrite() called - clock sync command from IEC101 Client");
	printf("\r\n Server ID : %u", u16ObjectId);    
    vPrintDataInformation(ptWriteID, psWriteValue);
	printf("\r\n Orginator Address %u",psWriteParams->u8OriginatorAddress);

    return i16ErrorCode;
}

/******************************************************************************
* Select callback
******************************************************************************/
Integer16 cbSelect(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID * psSelectID, struct sIEC101DataAttributeData * psSelectValue, struct sIEC101CommandParameters * psSelectParams, tErrorValue * ptErrorValue)
{
    Integer16 i16ErrorCode = EC_NONE;


    printf("\n\r\n cbSelect() called");
	printf("\r\n Server ID : %u", u16ObjectId);
    vPrintDataInformation(psSelectID, psSelectValue);
    printf("\r\nOrginator Address  %u",psSelectParams->u8OriginatorAddress );
    printf("\r\nQualifier %u",psSelectParams->eQOCQU );
    printf("\r\nPulse Duration %u",psSelectParams->u32PulseDuration );


    return i16ErrorCode;
}

/******************************************************************************
* Operate callback
******************************************************************************/
Integer16 cbOperate(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID * psOperateID, struct sIEC101DataAttributeData * psOperateValue, struct sIEC101CommandParameters * psOperateParams, tErrorValue * ptErrorValue)
{
    Integer16 i16ErrorCode = EC_NONE;


    printf("\n\r\n cbOperate() called");
	printf("\r\n Server ID : %u", u16ObjectId);
    vPrintDataInformation(psOperateID, psOperateValue);

    printf("\r\nQualifier %u",psOperateParams->eQOCQU );
    printf("\r\nPulse duration %u",psOperateParams->u32PulseDuration );
    printf("\r\nOrginator Address %u",psOperateParams->u8OriginatorAddress );
    return i16ErrorCode;
}

/******************************************************************************
* Cancel callback
******************************************************************************/
Integer16 cbCancel(Unsigned16 u16ObjectId, enum eOperationFlag eOperation,struct sIEC101DataAttributeID * psCancelID, struct sIEC101DataAttributeData * psCancelValue, struct sIEC101CommandParameters * psCancelParams, tErrorValue * ptErrorValue)
{
    Integer16 i16ErrorCode = EC_NONE;


    printf("\n\r\n cbCancel() called");
	printf("\r\n Server ID : %u", u16ObjectId);

    if(eOperation   ==  OPERATE)
        printf("\r\n Operate operation to be cancel");

    if(eOperation   ==  SELECT)
        printf("\r\n Select operation to cancel");

    vPrintDataInformation(psCancelID, psCancelValue);

    printf("\r\nQualifier %u",psCancelParams->eQOCQU );
    printf("\r\nPulse duration %u",psCancelParams->u32PulseDuration );
    printf("\r\nOrginator Address %u",psCancelParams->u8OriginatorAddress );


    return i16ErrorCode;
}

/******************************************************************************
* Parameteract callback
******************************************************************************/
Integer16 cbParameterAct(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptOperateID, struct sIEC101DataAttributeData *ptOperateValue,struct sIEC101ParameterActParameters *ptParameterActParams, tErrorValue *ptErrorValue)
{
    Integer16 i16ErrorCode = EC_NONE;

    printf("\n\r\n cbParameterAct() called");
	printf("\r\n Server ID : %u", u16ObjectId);
    vPrintDataInformation(ptOperateID, ptOperateValue);

    return i16ErrorCode;
}

/******************************************************************************
* Freeze Callback
******************************************************************************/
Integer16 cbFreeze(Unsigned16 u16ObjectId, enum eCounterFreezeFlags eCounterFreeze, struct sIEC101DataAttributeID *ptFreezeID, struct sIEC101DataAttributeData *ptFreezeValue, struct sIEC101WriteParameters *ptFreezeCmdParams, tErrorValue *ptErrorValue)
{
    Integer16 i16ErrorCode = EC_NONE;

    printf("\n\r\n cbFreeze() called");
	printf("\r\n Server ID : %u", u16ObjectId);    
    printf(" Command Typeid %u", ptFreezeID->eTypeID);
    printf("\r\nCOT %u", ptFreezeCmdParams->eCause);
	printf("\r\nOrginator Address  %u",ptFreezeCmdParams->u8OriginatorAddress );

    return i16ErrorCode;
}

/******************************************************************************
* Operate pulse end callback
******************************************************************************/
Integer16 cbpulseend(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID * psOperateID,  struct sIEC101DataAttributeData * psOperateValue, struct sIEC101CommandParameters * psOperateParams, tErrorValue * ptErrorValue)
{
    Integer16 i16ErrorCode = EC_NONE;

    printf("\n\r\n cbOperatepulse end() called");
	printf("\r\n Server ID : %u", u16ObjectId); 
    vPrintDataInformation(psOperateID, psOperateValue);
    printf("\r\nQualifier %u",psOperateParams->eQOCQU);
    printf("\r\nPulse duration %u",psOperateParams->u32PulseDuration);
    printf("\r\nOrginator Address %u",psOperateParams->u8OriginatorAddress);

    return i16ErrorCode;
}


/******************************************************************************
* Debug callback
******************************************************************************/
Integer16 cbDebug(Unsigned16 u16ObjectId, struct sIEC101DebugData * ptDebugData, tErrorValue *ptErrorValue)
{
    Integer16 i16ErrorCode = EC_NONE;
    Unsigned16 u16nav                = 0;

	//printf("\n\r\n cbDebug() called");
    printf("\r\n %u:%u:%u Server ID: %u", ptDebugData->sTimeStamp.u8Hour, ptDebugData->sTimeStamp.u8Minute, ptDebugData->sTimeStamp.u8Seconds,u16ObjectId);


    if((ptDebugData->u32DebugOptions & DEBUG_OPTION_TX ) == DEBUG_OPTION_TX)
    {
        printf(" Com %u ",ptDebugData->u16ComportNumber);
		printf("->");
        for(u16nav = 0; u16nav < (ptDebugData->u16TxCount); u16nav++)
        {
            printf(" %02x",ptDebugData->au8TxData[u16nav]);
        }
    }

    if((ptDebugData->u32DebugOptions & DEBUG_OPTION_RX ) == DEBUG_OPTION_RX)
    {
        printf(" Com %u ", ptDebugData->u16ComportNumber);
		printf("<-");
        for(u16nav = 0; u16nav < (ptDebugData->u16RxCount); u16nav++)
        {
            printf(" %02x",ptDebugData->au8RxData[u16nav]);
        }
    }
     if((ptDebugData->u32DebugOptions & DEBUG_OPTION_ERROR ) == DEBUG_OPTION_ERROR)
    {
        printf("\r\nError message %s", ptDebugData->au8ErrorMessage);
        printf("\r\nErrorCode %d", ptDebugData->i16ErrorCode);
        printf("\r\nErrorValue %d", ptDebugData->tErrorvalue);
    }


    return i16ErrorCode;
}


/******************************************************************************
* main()
******************************************************************************/
int main (void)
{

    Integer16								i16ErrorCode        = EC_NONE;     // API Function return error paramter
    tErrorValue                             tErrorValue       = EV_NONE;    // API Function return additional error parameter
    IEC101Object                              myServer         = NULL;      // IEC 60870-5-101 Server object
    Unsigned16                   u16Char         =   0;                     // Get control+x key to stop update values
    struct sIEC101DataAttributeID *psDAID       =   NULL;                   // update data attribute
    struct sIEC101DataAttributeData *psNewValue =   NULL;                   // updtae new value
    Float32 f32data                         = 0;                            // update data
    struct sIEC101ConfigurationParameters  sIEC101Config;                   // server protocol , point configuration parameters
    struct sIEC101Parameters               sParameters;                     // IEC101 Server object callback paramters 
    unsigned int uiCount;                                                   // update number of parameters
    struct tm * timeinfo;                                                   // update date and time structute
    time_t now;                                                             // to get current data and time 

   do
   {
        printf("\n\r\n \t\t**** FreyrSCADA - IEC 60870-5-101 Server Library Test ****");
        // Check library version against the library header file
        if(strcmp((char*)IEC101GetLibraryVersion(), IEC101_VERSION) != 0)
        {
            printf("\r\n Error: Version Number Mismatch");
            printf("\r\n Library Version is  : %s", IEC101GetLibraryVersion());
            printf("\r\n The Version used is : %s", IEC101_VERSION);
            printf("\r\n");
			getchar();
			return 0;
        }

        printf("\r\nLibrary Version is : %s", IEC101GetLibraryVersion());
        printf("\r\nLibrary Build on   : %s", IEC101GetLibraryBuildTime());
		printf("\r\nLibrary License Information   : %s", IEC101GetLibraryLicenseInfo());

        memset(&sParameters, 0, sizeof(struct sIEC101Parameters));

        // Initialize IEC 60870-5-101 Server object parameters
        sParameters.eAppFlag          = APP_SERVER;                         // This is a IEC101 Server
        sParameters.ptReadCallback    = cbRead;                             // Read Callback
        sParameters.ptWriteCallback   = cbWrite;                            // Write Callback
        sParameters.ptUpdateCallback  = NULL;                               // Update Callback
        sParameters.ptSelectCallback  = cbSelect;                           // Select commands
        sParameters.ptOperateCallback = cbOperate;                          // Operate commands
        sParameters.ptCancelCallback  = cbCancel;                           // Cancel commands
        sParameters.ptDebugCallback   = cbDebug;                            // Debug Callback
        sParameters.ptFreezeCallback  = cbFreeze;                           // Freeze Callback
        sParameters.ptPulseEndActTermCallback = cbpulseend;                 // pulse end callback
        sParameters.ptParameterActCallback = cbParameterAct;                // Parameter activation callback            
        sParameters.ptClientStatusCallback      = NULL;                     // client connection status callback
        sParameters.ptDirectoryCallback         = NULL;                     // client Directory callback 
        sParameters.u16ObjectId         = 1;                                // User object idenfication for server
        sParameters.u32Options          = 0;
        
        // Create a server
        myServer = IEC101Create(&sParameters, &i16ErrorCode, &tErrorValue);
        if(myServer == NULL)
        {
            printf("\r\n IEC 60870-5-101 Library API Function -  IEC101Create() failed: %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
            break;
        }

        // Server load configuration - communication and protocol configuration parameters
        memset(&sIEC101Config, 0, sizeof(struct sIEC101ConfigurationParameters));
        sIEC101Config.sServerSet.u8NumberofSerialPortConnections    =   1;
        // Allocate memory for objects
        sIEC101Config.sServerSet.psSerialSet = NULL;
        sIEC101Config.sServerSet.psSerialSet = (struct sSerialCommunicationSettings *)calloc(sIEC101Config.sServerSet.u8NumberofSerialPortConnections, sizeof(struct sSerialCommunicationSettings ));
        if(sIEC101Config.sServerSet.psSerialSet == NULL)
        {
            printf("\r\nError: Not enough memory to alloc objects");
            break;
        }
		
	   sIEC101Config.sServerSet.psSerialSet[0].eSerialType   = SERIAL_RS232;
		// check computer configuration serial com port number,  if server and client application running in same system, we can use com0com
       sIEC101Config.sServerSet.psSerialSet[0].u16SerialPortNumber   =   SERIAL_PORT_NUMBER;
       sIEC101Config.sServerSet.psSerialSet[0].eSerialBitRate       =   BITRATE_9600;
       sIEC101Config.sServerSet.psSerialSet[0].eWordLength          =   WORDLEN_8BITS;
       sIEC101Config.sServerSet.psSerialSet[0].eSerialParity        =   EVEN;
       sIEC101Config.sServerSet.psSerialSet[0].eStopBits            =   STOPBIT_1BIT;
	   
	   //serial port flow control
	   sIEC101Config.sServerSet.psSerialSet[0].sFlowControl.bWinCTSoutputflow         =  FALSE;
	   sIEC101Config.sServerSet.psSerialSet[0].sFlowControl.bWinDSRoutputflow         =  FALSE;
	   sIEC101Config.sServerSet.psSerialSet[0].sFlowControl.eWinDTR					  =	 WIN_DTR_CONTROL_DISABLE;
	   sIEC101Config.sServerSet.psSerialSet[0].sFlowControl.eWinRTS					  =  WIN_RTS_CONTROL_DISABLE;
       sIEC101Config.sServerSet.psSerialSet[0].sFlowControl.eLinuxFlowControl         = FLOW_NONE;
	   
	   sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u16CharacterTimeout     =   1;
       sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u16MessageTimeout       =   0;
       sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u16InterCharacterDelay  =   5;
       sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u16PostDelay            =   0;
       sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u16PreDelay             =   0;
       sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u8CharacterRetries      =   20;
       sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u8MessageRetries        =   0;

       sIEC101Config.sServerSet.sServerProtSet.eDataLink                =   UNBALANCED_MODE;

       sIEC101Config.sServerSet.sServerProtSet.elinkAddrSize            =   DL_ONE_BYTE;
       sIEC101Config.sServerSet.sServerProtSet.u16DataLinkAddress       =   1;
       sIEC101Config.sServerSet.sServerProtSet.eCOTsize                 =   COT_TWO_BYTE;
       sIEC101Config.sServerSet.sServerProtSet.eIOAsize                 =   IOA_TWO_BYTE;
       sIEC101Config.sServerSet.sServerProtSet.eCASize                  =   CA_TWO_BYTE;
       sIEC101Config.sServerSet.sServerProtSet.u8TotalNumberofStations  =   1;
       sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[0]     =   1;
       sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[1]     =   0;
       sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[2]     =   0;
       sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[3]     =   0;
       sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[4]     =   0;



       sIEC101Config.sServerSet.sServerProtSet.eNegACK  = FIXED_FRAME_NACK;
       sIEC101Config.sServerSet.sServerProtSet.ePosACK  =   SINGLE_CHAR_ACK_E5;

       sIEC101Config.sServerSet.sServerProtSet.u16Class1EventBufferSize =   5000;
       sIEC101Config.sServerSet.sServerProtSet.u16Class2EventBufferSize =   5000;

       sIEC101Config.sServerSet.sServerProtSet.u8Class1BufferOverFlowPercentage     =   90;
       sIEC101Config.sServerSet.sServerProtSet.u8Class2BufferOverFlowPercentage     =   90;
       sIEC101Config.sServerSet.sServerProtSet.u8MaxAPDUSize                        =   253;
       sIEC101Config.sServerSet.sServerProtSet.u16ShortPulseTime                    =   5000;
       sIEC101Config.sServerSet.sServerProtSet.u16LongPulseTime                     =   10000;
       sIEC101Config.sServerSet.sServerProtSet.u32ClockSyncPeriod                   =   0;
       sIEC101Config.sServerSet.sServerProtSet.bGenerateACTTERMrespond              =   TRUE;


       sIEC101Config.sServerSet.sServerProtSet.u32BalancedModeTestConnectionSignalInterval  = 60;

       // File transfer protocol configuration parameters
       sIEC101Config.sServerSet.sServerProtSet.bEnableFileTransfer = FALSE;
       strcpy((char*)sIEC101Config.sServerSet.sServerProtSet.ai8FileTransferDirPath, "//FileTransferServer//");
       sIEC101Config.sServerSet.sServerProtSet.u16MaxFilesInDirectory    = 10;

#ifdef VIEW_TRAFFIC
       sIEC101Config.sServerSet.sDebug.u32DebugOptions                              =   ( DEBUG_OPTION_TX | DEBUG_OPTION_RX);
#else
	   sIEC101Config.sServerSet.sDebug.u32DebugOptions    =   0;
#endif

       sIEC101Config.sServerSet.sServerProtSet.bTransmitSpontMeasuredValue = TRUE;
       sIEC101Config.sServerSet.sServerProtSet.bTransmitInterrogationMeasuredValue = TRUE;
        sIEC101Config.sServerSet.sServerProtSet.bTransmitBackScanMeasuredValue = TRUE;

        sIEC101Config.sServerSet.sServerProtSet.u8InitialdatabaseQualityFlag = (IV |NT); /*!< 0- good/valid, 1 BIT- iv, 2 BIT-nt,  MAX VALUE -3   */
        sIEC101Config.sServerSet.sServerProtSet.bUpdateCheckTimestamp = TRUE; /*!< if it true ,the timestamp change also generate event  during the iec104update */

        // Allocate memory for objects
        sIEC101Config.sServerSet.u16NoofObject           = 2;        // Define number of objects

        // Allocate memory for objects
        sIEC101Config.sServerSet.psIEC101Objects = NULL;
        sIEC101Config.sServerSet.psIEC101Objects = (struct sIEC101Object *)calloc(sIEC101Config.sServerSet.u16NoofObject, sizeof(struct sIEC101Object));
        if(sIEC101Config.sServerSet.psIEC101Objects == NULL)
        {
            printf("\r\nError: Not enough memory to alloc objects");
            break;
        }

        // Init objects
        //first object detail
        strncpy((char*)sIEC101Config.sServerSet.psIEC101Objects[0].ai8Name,"M_ME_TF_1",APP_OBJNAMESIZE);
        sIEC101Config.sServerSet.psIEC101Objects[0].eTypeID     = M_ME_TF_1;
        sIEC101Config.sServerSet.psIEC101Objects[0].u32IOA          = 100;
        sIEC101Config.sServerSet.psIEC101Objects[0].eIntroCOT       = INRO1;
        sIEC101Config.sServerSet.psIEC101Objects[0].u16Range        = 10;
        sIEC101Config.sServerSet.psIEC101Objects[0].eControlModel   =   STATUS_ONLY;
        sIEC101Config.sServerSet.psIEC101Objects[0].u32SBOTimeOut   =   0;
        sIEC101Config.sServerSet.psIEC101Objects[0].eClass          =   IEC_CLASS1;
        sIEC101Config.sServerSet.psIEC101Objects[0].u16CommonAddress    =   1;

        //Second object detail
        strncpy((char*)sIEC101Config.sServerSet.psIEC101Objects[1].ai8Name,"C_SE_TC_1",APP_OBJNAMESIZE);
        sIEC101Config.sServerSet.psIEC101Objects[1].eTypeID     =  C_SE_TC_1;
        sIEC101Config.sServerSet.psIEC101Objects[1].u32IOA          = 100;
        sIEC101Config.sServerSet.psIEC101Objects[1].eIntroCOT       = NOTUSED;
        sIEC101Config.sServerSet.psIEC101Objects[1].u16Range        = 10;
        sIEC101Config.sServerSet.psIEC101Objects[1].eControlModel  = DIRECT_OPERATE;
        sIEC101Config.sServerSet.psIEC101Objects[1].u32SBOTimeOut   = 0;
        sIEC101Config.sServerSet.psIEC101Objects[1].eClass          =   IEC_NO_CLASS;
        sIEC101Config.sServerSet.psIEC101Objects[1].u16CommonAddress    =   1;


        // Load configuration
       i16ErrorCode = IEC101LoadConfiguration(myServer, &sIEC101Config, &tErrorValue);
       if(i16ErrorCode != EC_NONE)
       {
            printf("\r\n IEC 60870-5-101 Library API Function -  IEC101LoadConfiguration() failed: %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
            break;
        }

        // Start server
        i16ErrorCode = IEC101Start(myServer, &tErrorValue);  //Start myServer
        if(i16ErrorCode != EC_NONE)
        {
           printf("\r\n IEC 60870-5-101 Library API Function -  IEC101Start() failed: %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
            break;
        }



    
#ifdef SIMULATE_UPDATE
        // update parameters
    uiCount    =   1;
    psDAID     = (struct sIEC101DataAttributeID*)  calloc(uiCount,sizeof(struct sIEC101DataAttributeID));
    psNewValue  =  (struct sIEC101DataAttributeData*) calloc(uiCount,sizeof(struct sIEC101DataAttributeData));

    psDAID[0].u16SerialPortNumber    =   SERIAL_PORT_NUMBER;
    psDAID[0].u16DataLinkAddress    =   1;
    psDAID[0].eTypeID                              =   M_ME_TF_1;
    psDAID[0].u32IOA                               =   100L;
    psDAID[0].pvUserData                           =   NULL;
    psNewValue[0].tQuality                         =   GD;
    psDAID[0].u16CommonAddress                      =   1;

    psNewValue[0].pvData                           =   &f32data;
    psNewValue[0].eDataType                        =   FLOAT32_DATA;
    psNewValue[0].eDataSize                        =   FLOAT32_SIZE;
#endif

    // Loop

    printf("\r\nPlease Enter CTRL-X to Exit");
    printf("\r\n");


        Sleep(3000);


    while(TRUE)
    {

        if(_kbhit())      
        {
          u16Char = _getch() & 0x00FF;
          if(u16Char == 24)
          {
            break;
          }
        }
        else
        {
#ifdef SIMULATE_UPDATE
            //server Update Value called

            time(&now);
            timeinfo = localtime(&now);
            timeinfo->tm_year += 1900;

            //current date
            psNewValue[0].sTimeStamp.u8Day              =   (Unsigned8)timeinfo->tm_mday;
            psNewValue[0].sTimeStamp.u8Month            =   (Unsigned8)(timeinfo->tm_mon + 1);
            psNewValue[0].sTimeStamp.u16Year            =   timeinfo->tm_year;

            //time
            psNewValue[0].sTimeStamp.u8Hour             =   (Unsigned8)timeinfo->tm_hour;
            psNewValue[0].sTimeStamp.u8Minute           =   (Unsigned8)timeinfo->tm_min;
            psNewValue[0].sTimeStamp.u8Seconds          =   (Unsigned8)(timeinfo->tm_sec);
            psNewValue[0].sTimeStamp.u16MilliSeconds    =   0;
            psNewValue[0].sTimeStamp.u16MicroSeconds    =   0;
            psNewValue[0].sTimeStamp.i8DSTTime          =   0; //No Day light saving time
            psNewValue[0].sTimeStamp.u8DayoftheWeek     =   4;


            // increment the Update value to generate event
            f32data                     += (float)1;

            // Update server
            i16ErrorCode = IEC101Update(myServer, TRUE, psDAID,psNewValue,uiCount,&tErrorValue);  
            if(i16ErrorCode != EC_NONE)
            {
                printf("\r\n IEC 60870-5-101 Library API Function -  IEC101Update() failed: %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
            }


#endif
        }
//Monitoring Information data update - time frequency 

        Sleep(5000);
    }

#ifdef SIMULATE_UPDATE
    free(psDAID);
    free(psNewValue);
#endif


    // Stop server
    i16ErrorCode = IEC101Stop(myServer, &tErrorValue); 
    if(i16ErrorCode != EC_NONE)
    {
        printf("\r\n IEC 60870-5-101 Library API Function - IEC101Stop() failed: %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
        break;
    }

   }while(FALSE);

   printf("\r\n Enter any key to free");
   while(TRUE)
   {
    if(_kbhit())
		break;
   }

   // Free server
   i16ErrorCode = IEC101Free(myServer, &tErrorValue);  
   if(i16ErrorCode != EC_NONE)
   {
        printf("\r\n IEC 60870-5-101 Library API Function - IEC101Free() failed: %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
   }
   printf("\r\nBye\r\n");


   return(0);

}
