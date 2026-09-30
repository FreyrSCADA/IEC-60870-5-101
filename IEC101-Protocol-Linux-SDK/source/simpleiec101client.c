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
/*! \file       simpleiec101client.c
 *  \brief      C Source code file, IEC 60870-5-101 Client library test program - linux
 *
 *  \par        FreyrSCADA Embedded Solution Pvt Ltd
 *              Email   : support@freyrscada.com
 */
/*****************************************************************************/

/******************************************************************************
* Includes
******************************************************************************/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/time.h>
#include <termios.h>
#include <fcntl.h>
#include <terminalinput.h>

#include "tgttypes.h"
#include "iec101api.h"



  IEC101Object                        myClient          = NULL;        // IEC101 Client Object
  Boolean viewtraffic =	FALSE;

#define SERIAL_PORT_NUMBER 1 //ttyS1


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
* client status callback
******************************************************************************/
Integer16 cbClientStatus(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *psDAID, enum eStatus *peSat, tErrorValue *ptErrorValue)
{
     Integer16 i16ErrorCode = EC_NONE;

     printf("\n\r\n cbClientStatus called");
	 printf("\r\n Client ID : %u", u16ObjectId);

     printf("\r\n  DataLink Address %u", psDAID->u16DataLinkAddress);
     printf("\r\n  Serial port number %u", psDAID->u16SerialPortNumber);

     if( *peSat ==  CONNECTED)
     {
         printf("\r\n Connected");
     }
     else
     {
         printf("\r\n Disconnected");
    }


	 printf("\r\n Enter CTRL-X to Exit \t s - Send command called \t e - enable view traffic \t d - disable view traffic");
     printf("\r\n");

     return i16ErrorCode;
}

/******************************************************************************
* Update callback
******************************************************************************/
Integer16 cbUpdate(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptUpdateID, struct sIEC101DataAttributeData *ptUpdateValue,struct sIEC101UpdateParameters *ptUpdateParams, tErrorValue *ptErrorValue)
{
    Integer16 i16ErrorCode = EC_NONE;
    Unsigned8 u8data = 0;

    printf("\n\r\n cbupdate called");
	printf("\r\n Client ID : %u", u16ObjectId);
    printf("\r\n Link Address %u",ptUpdateID->u16DataLinkAddress);
    printf("\t Station Address %u",ptUpdateID->u16CommonAddress);
    printf("\t Type id %u",ptUpdateID->eTypeID);
    printf("\t IOA %u",ptUpdateID->u32IOA);

    if((ptUpdateID->eTypeID == M_EP_TB_1) || (ptUpdateID->eTypeID == M_EP_TE_1))
    {
        memcpy(&u8data,ptUpdateValue->pvData,sizeof(Unsigned8));

        if((u8data & GS) == GS)
        {
            printf("\r\n General start of operation");
        }

        if((u8data & SL1) == SL1)
        {
            printf("\r\n  Start of operation phase L1");
        }

        if((u8data & SL2) == SL2)
        {
            printf("\r\n  Start of operation phase L2");
        }

        if((u8data & SL3) == SL3)
        {
            printf("\r\n  Start of operation phase L3");
        }

        if((u8data & SIE) == SIE)
        {
            printf("\r\n  Start of operation IE");
        }

        if((u8data & SRD) == SRD)
        {
            printf("\r\n Start of operation in reverse direction");
        }
    }
    else if ((ptUpdateID->eTypeID == M_EP_TC_1)|| (ptUpdateID->eTypeID == M_EP_TF_1))
    {

        memcpy(&u8data,ptUpdateValue->pvData,sizeof(Unsigned8));

        if((u8data & GC) == GC)
        {
            printf("\r\n General command to output circuit ");
        }

        if((u8data &  CL1) ==  CL1)
        {
            printf("\r\n Command to output circuit phase L1");
        }

        if((u8data &  CL2) ==  CL2)
        {
            printf("\r\n Command to output circuit phase L2");
        }

        if((u8data &  CL3) ==  CL3)
        {
            printf("\r\n Command to output circuit phase L3");
        }

    }
    else
    {

     switch(ptUpdateValue->eDataType)
        {
            case SINGLE_POINT_DATA:
                if(*(Unsigned8*)ptUpdateValue->pvData==FALSE)
                    printf("  OFF   ");
                else if(*(Unsigned8*)ptUpdateValue->pvData == TRUE)
                    printf("  ON  ");
                break;

            case DOUBLE_POINT_DATA:
                if((*(Unsigned8*)ptUpdateValue->pvData==0)||(*(Unsigned8*)ptUpdateValue->pvData==03))
                    printf("  Indeterminate state   ");
                else if(*(Unsigned8*)ptUpdateValue->pvData==1)
                    printf("  OFF   ");
                else if(*(Unsigned8*)ptUpdateValue->pvData==2)
                    printf("  ON  ");
                break;

            case SIGNED_BYTE_DATA:
                printf(" I8 %d   ",*(Integer8*)ptUpdateValue->pvData);
                break;

            case UNSIGNED_BYTE_DATA:
                printf(" u8 %u   ",*(Unsigned8*)ptUpdateValue->pvData);
                break;

            case SIGNED_WORD_DATA:
                printf(" i16 %d  ",*(Integer16*)ptUpdateValue->pvData);
                break;

            case UNSIGNED_WORD_DATA:
                printf(" u16 %u  ",*(Unsigned16*)ptUpdateValue->pvData);
                break;

            case FLOAT32_DATA:
                printf(" f %0.3f  ",*(Float32*)ptUpdateValue->pvData);
                break;

            case SIGNED_DWORD_DATA:
                printf(" i32 %d  ",*(Integer32*)ptUpdateValue->pvData);
                break;

            case UNSIGNED_DWORD_DATA:
                printf(" u32 %u  ",*(Unsigned32*)ptUpdateValue->pvData);
                break;

            default:
                printf("value datatype not supported");
                break;
            }
    }


    if(ptUpdateValue->tQuality != GD)
        {


            if((ptUpdateValue->tQuality & IV) == IV)
            {
                printf("\r\n IEC_INVALID_FLAG");
            }

            if((ptUpdateValue->tQuality & NT) == NT)
            {
                printf("\r\n IEC_NONTOPICAL_FLAG");
            }

            if((ptUpdateValue->tQuality & SB) == SB)
            {
                printf("\r\n IEC_SUBSTITUTED_FLAG");
            }

            if((ptUpdateValue->tQuality & BL) == BL)
            {
                printf("\r\n IEC_BLOCKED_FLAG");
            }

            if((ptUpdateValue->tQuality & OV) == OV)
            {
                printf("\r\n IEC_OV_FLAG");
            }

            if((ptUpdateValue->tQuality & EI) == EI)
            {
                printf("\r\n IEC_EI_FLAG");
            }

            if((ptUpdateValue->tQuality & TR) == TR)
            {
                printf("\r\n IEC_TR_FLAG");
            }

            if((ptUpdateValue->tQuality & CA) == CA)
            {
                printf("\r\n IEC_CA_FLAG");
            }

            if((ptUpdateValue->tQuality & CR) == CR)
            {
                printf("\r\n IEC_CR_FLAG");
            }

        }

    printf("\t COT %u",ptUpdateParams->eCause);

    if((ptUpdateID->eTypeID == M_EP_TA_1) ||
        (ptUpdateID->eTypeID == M_EP_TB_1) ||
        (ptUpdateID->eTypeID == M_EP_TC_1) ||
        (ptUpdateID->eTypeID == M_EP_TD_1) ||
        (ptUpdateID->eTypeID == M_EP_TE_1) ||
        (ptUpdateID->eTypeID == M_EP_TF_1))
    {
        printf("\r\n Elapsed time %u",ptUpdateValue->u16ElapsedTime);
    }


    printf("\t h:m:s:ms %u:%u:%u:%u",ptUpdateValue->sTimeStamp.u8Hour, ptUpdateValue->sTimeStamp.u8Minute, ptUpdateValue->sTimeStamp.u8Seconds, ptUpdateValue->sTimeStamp.u16MilliSeconds);
    printf("\t d:m:y %u:%u:%u",ptUpdateValue->sTimeStamp.u8Day, ptUpdateValue->sTimeStamp.u8Month, ptUpdateValue->sTimeStamp.u16Year);


    if(((ptUpdateID->eTypeID	  ==  M_ST_NA_1) || (ptUpdateID->eTypeID	  ==  M_ST_TA_1)) || (ptUpdateID->eTypeID    ==  M_ST_TB_1))
	{
		if(ptUpdateValue->bTRANSIENT)
			printf("\t M_ST bTRANSIENT  - TRUE");
		else
			printf("\t M_ST bTRANSIENT  - FALSE");
	}

	if(((ptUpdateID->eTypeID	  ==  M_IT_NA_1) || (ptUpdateID->eTypeID	  ==  M_IT_TA_1)) || (ptUpdateID->eTypeID    == M_IT_TB_1))
	{
		printf("\t M_IT Sequence - %u",ptUpdateValue->u8Sequence);
	}



	printf("\r\n Enter CTRL-X to Exit \t s - Send command called \t e - enable view traffic \t d - disable view traffic");
     printf("\r\n");

    return i16ErrorCode;
}

/******************************************************************************
* Debug callback
******************************************************************************/
Integer16 cbDebug(Unsigned16 u16ObjectId, struct sIEC101DebugData *ptDebugData, tErrorValue *ptErrorValue)
{
    Integer16 i16ErrorCode = EC_NONE;
    Unsigned16 u16nav                = 0;

    //printf("\r\n cbDebug() called");

	if(viewtraffic == TRUE)
	{

    printf("\r\n %u:%u:%u Client ID: %u", ptDebugData->sTimeStamp.u8Hour, ptDebugData->sTimeStamp.u8Minute, ptDebugData->sTimeStamp.u8Seconds,u16ObjectId);


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

	printf("\r\n");

	}

    return i16ErrorCode;
}


void sendcommand()
{
	Integer16						   i16ErrorCode        = EC_NONE;     // API Function return error parameter
   tErrorValue                         tErrorValue       = EV_NONE;     // API Function return additional error parameter
   struct sIEC101DataAttributeID sWriteDAID                 = {0};      // Client protocol- point configuration parameters
   struct sIEC101CommandParameters sCommandParams           = {0};      // Command addional input parameters
   Float32 f32data                                          = 0;        // command data
   //Unsigned16           u16Char                             = 0;        // Get control+x key to stop send command
  struct sIEC101DataAttributeData sWriteValue;                         // Command data value parameters

  Unsigned32 ioa	=	0;
  time_t now;                                                          // to get current data and time
   struct tm * timeinfo;                                                // command data- date and time structute


	set_tty_cooked(); //Unix setup to reverse tty_set_raw()
   	printf("\r\n");

		printf ("Enter Information object address (IOA): ");
		if(scanf("%u", &ioa));
		printf("\r\n");

		printf ("Enter command float value: ");
		if(scanf("%f", &f32data));
		printf("\r\n");

		            //client commands starts
            time(&now);
            timeinfo = localtime(&now);
            timeinfo->tm_year += 1900;

            //current date
            sWriteValue.sTimeStamp.u8Day            =   (Unsigned8)timeinfo->tm_mday;
            sWriteValue.sTimeStamp.u8Month          =   (Unsigned8)(timeinfo->tm_mon + 1);
            sWriteValue.sTimeStamp.u16Year          =   timeinfo->tm_year;

            //time
            sWriteValue.sTimeStamp.u8Hour           =   (Unsigned8)timeinfo->tm_hour;
            sWriteValue.sTimeStamp.u8Minute         =   (Unsigned8)timeinfo->tm_min;
            sWriteValue.sTimeStamp.u8Seconds        =   (Unsigned8)(timeinfo->tm_sec);
            sWriteValue.sTimeStamp.u16MilliSeconds  =   0;
            sWriteValue.sTimeStamp.u16MicroSeconds  =   0;
            sWriteValue.sTimeStamp.i8DSTTime        =   0; //No Day light saving time
            sWriteValue.sTimeStamp.u8DayoftheWeek   =   4;

            sWriteDAID.u16SerialPortNumber   =   SERIAL_PORT_NUMBER;
            sWriteDAID.u16DataLinkAddress=  1;
            sWriteDAID.u16CommonAddress=    1;
            sCommandParams.u8OriginatorAddress  =   1;
            sCommandParams.eQOCQU   =   NOADDDEF;


            sWriteDAID.eTypeID      =   C_SE_TC_1;
            sWriteDAID.u32IOA       =   ioa;
            sWriteValue.eDataType   =   FLOAT32_DATA;
            sWriteValue.eDataSize   =   FLOAT32_SIZE;
            sWriteValue.tQuality    =   GD;
            sWriteValue.pvData      =   &f32data;

            i16ErrorCode = IEC101Operate(myClient, &sWriteDAID, &sWriteValue, &sCommandParams,  &tErrorValue);  //Stop myClient
            if(i16ErrorCode != EC_NONE)
            {
                printf("\r\n IEC 60870-5-101 Library API Function - IEC101Operate C_SE_TC_1 command operate failed:  %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
                //break;
            }
            else
            {
                printf("\r\n IEC 60870-5-101 Library API Function - IEC101Operate C_SE_TC_1 command operate success");
            }

            		set_tty_raw() ;  // Unix setup to read a character at a time.

		printf("\r\n");

		printf("\r\n Enter CTRL-X to Exit \t s - Send command called \t e - enable view traffic \t d - disable view traffic");
        printf("\r\n");


}


/******************************************************************************
* main()
******************************************************************************/
int main (void)
{

   Integer16						   i16ErrorCode        = EC_NONE;     // API Function return error parameter
   tErrorValue                         tErrorValue       = EV_NONE;     // API Function return additional error parameter
   Unsigned16           u16Char                             = 0;        // Get control+x key to stop send command
   Boolean bexit							=	FALSE;

   struct sIEC101ConfigurationParameters  sIEC101Config;                // Client protocol , point configuration parameters
    struct sIEC101Parameters            sParameters;                     // IEC101 client object callback paramters

   do
   {
       printf("\n\r\n \t\t**** FreyrSCADA - IEC 60870-5-101 Client Library Test ****");
       // Check library version against the library header file
        if(strcmp((char*)IEC101GetLibraryVersion(), IEC101_VERSION) != 0)
        {
            printf("\r\n Error: Version Number Mismatch");
            printf("\r\n Library Version is  : %s", IEC101GetLibraryVersion());
            printf("\r\n The Version used is : %s", IEC101_VERSION);
           	printf("\r\n");
			getchar();
			return(0);
        }

        printf("\r\nLibrary Version is : %s", IEC101GetLibraryVersion());
        printf("\r\nLibrary Build on   : %s", IEC101GetLibraryBuildTime());
		printf("\r\nLibrary License Information   : %s", IEC101GetLibraryLicenseInfo());

        memset(&sParameters, 0, sizeof( struct sIEC101Parameters));

        // Initialize IEC 60870-5-101 Client object parameters
        sParameters.eAppFlag          = APP_CLIENT;      // This is a IEC101 master
        sParameters.ptReadCallback    = NULL;            // Read Callback
        sParameters.ptWriteCallback   = NULL;            // Write Callback
        sParameters.ptUpdateCallback  = cbUpdate;        // Update Callback
        sParameters.ptSelectCallback  = NULL;            // Select commands
        sParameters.ptOperateCallback = NULL;            // Operate commands
        sParameters.ptCancelCallback  = NULL;            // Cancel commands
        sParameters.ptDebugCallback   = cbDebug;         // Debug Callback
        sParameters.ptClientStatusCallback = cbClientStatus;            // client connection status Callback
        sParameters.u32Options        = 0;
		sParameters.u16ObjectId         = 1;                              // Client identification- User object idenfication for Client


        // Create a client object
        myClient = IEC101Create(&sParameters, &i16ErrorCode, &tErrorValue);
        if(myClient == NULL)
        {
            printf("\r\n IEC 60870-5-101 Library API Function - IEC101Create() failed:  %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
            break;
        }

        // Client load configuration - communication and protocol configuration parameters
        memset(&sIEC101Config, 0, sizeof(struct sIEC101ConfigurationParameters));
        sIEC101Config.sClientSet.u8NoofClient   =   1;

        sIEC101Config.sClientSet.psClientObjects    = NULL;
        sIEC101Config.sClientSet.psClientObjects    =(struct sIEC101ClientObject*)    calloc(sIEC101Config.sClientSet.u8NoofClient, sizeof(struct sIEC101ClientObject ));
        if(sIEC101Config.sClientSet.psClientObjects == NULL)
        {
            printf("\r\nError: Not enough memory to alloc objects");
            break;
        }

/******************************************************************************
* Serial Port Number
* "/dev/ttyS0" to "/dev/ttyS9" portnumber 0-9
* "/dev/ttySP0" to "/dev/ttySP9" portnumber 10-19
* "/dev/ttyUSB0" to "/dev/ttyUSB9" portnumber 20-29
* "/dev/ttyAPP0" to "/dev/ttyAPP9" portnumber 30-39
* "/dev/ttyAMA0" to "/dev/ttyAMA9" portnumber 40-49
* "/dev/ttyAP0" to "/dev/ttyAP9" portnumber 50-59
* "/dev/ttyO0" to"/dev/ttyO9" port number 60-69
**************************************
more details - support@freyrscada.com
******************************************************************************/


        sIEC101Config.sClientSet.eLink  =   UNBALANCED_MODE;            // Data Link Mode
		sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.eSerialType   = SERIAL_RS232;
		// check system configuration serial com port number
        sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.u16SerialPortNumber   =    SERIAL_PORT_NUMBER;  // Serial port /dev/ttyS1
        sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.eSerialBitRate       =   BITRATE_9600;
        sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.eWordLength          =   WORDLEN_8BITS;
        sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.eSerialParity        =   EVEN;
        sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.eStopBits            =   STOPBIT_1BIT;

		//serial port flow control
	    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sFlowControl.bWinCTSoutputflow         =  FALSE;
	    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sFlowControl.bWinDSRoutputflow         =  FALSE;
	    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sFlowControl.eWinDTR					  =	 WIN_DTR_CONTROL_DISABLE;
	    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sFlowControl.eWinRTS					  =  WIN_RTS_CONTROL_DISABLE;
        sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sFlowControl.eLinuxFlowControl         = FLOW_NONE;



		sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u16CharacterTimeout     =   1;
        sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u16MessageTimeout       =   0;
        sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u16InterCharacterDelay  =   5;
        sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u16PostDelay            =   1;
        sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u16PreDelay             =   1;
        sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u8CharacterRetries      =   30;
        sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u8MessageRetries        =   0;



        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.eCASize  =   CA_TWO_BYTE;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.eCOTsize =   COT_TWO_BYTE;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u8OriginatorAddress  =   1;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.eIOAsize =   IOA_TWO_BYTE;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.elinkAddrSize    =   DL_ONE_BYTE;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u16DataLinkAddress   =   1;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u8TotalNumberofStations  =   1;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.au16CommonAddress[0]     =   1;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.au16CommonAddress[1]     =   0;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.au16CommonAddress[2]     =   0;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.au16CommonAddress[3]     =   0;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.au16CommonAddress[4]     =   0;

        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32LinkLayerTimeout  =   5000;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32PollInterval  =   100;

        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32GeneralInterrogationInterval  =   5;    /*!< in sec if 0 , gi will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group1InterrogationInterval   =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group2InterrogationInterval   =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group3InterrogationInterval   =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group4InterrogationInterval   =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group5InterrogationInterval   =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group6InterrogationInterval   =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group7InterrogationInterval   =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group8InterrogationInterval   =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group9InterrogationInterval   =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group10InterrogationInterval  =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group11InterrogationInterval  =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group12InterrogationInterval  =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group13InterrogationInterval  =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group14InterrogationInterval  =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group15InterrogationInterval  =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group16InterrogationInterval  =   0;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32CounterInterrogationInterval  =   5;    /*!< in sec if 0 , ci will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group1CounterInterrogationInterval    =   0;    /*!< in sec if 0 , group 1 counter interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group2CounterInterrogationInterval    =   0;    /*!< in sec if 0 , group 1 counter interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group3CounterInterrogationInterval    =   0;    /*!< in sec if 0 , group 1 counter interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group4CounterInterrogationInterval    =   0;    /*!< in sec if 0 , group 1 counter interrogation will not send in particular interval*/
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32ClockSyncInterval =   5;              /*!< in sec if 0 , clock sync, will not send in particular interval */


        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32CommandTimeout    =   10000;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.bCommandResponseActtermUsed  =   TRUE;

        // File transfer protocol configuration parameters
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.bEnableFileTransfer  =   FALSE;
        sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32FileTransferTimeout           = 1000000;
        strcpy((char*)sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.ai8FileTransferDirPath, "//FileTest//");

        //sIEC101Config.sClientSet.sDebug.u32DebugOptions   =   0;
        sIEC101Config.sClientSet.sDebug.u32DebugOptions                             =   ( DEBUG_OPTION_WARNING | DEBUG_OPTION_ERROR | DEBUG_OPTION_TX | DEBUG_OPTION_RX);

		sIEC101Config.sClientSet.bAutoGenIEC101DataObjects  = FALSE;  /*!< if it true ,the IEC101 Objects created automaticallay, use u16NoofObject = 0, psIEC104Objects = NULL*/
        // Allocate memory for objects
        sIEC101Config.sClientSet.psClientObjects[0].u16NoofObject           = 2;        // Define number of objects
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects = NULL;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects = (struct sIEC101Object *)calloc(sIEC101Config.sClientSet.psClientObjects[0].u16NoofObject, sizeof(struct sIEC101Object));
        if(sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects == NULL)
        {
            printf("\r\nError: Not enough memory to alloc objects");
            break;
        }

        // Init objects
        //first object detail
        strcpy((char*)sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[0].ai8Name,"M_ME_TF_1");
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[0].eTypeID      = M_ME_TF_1;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[0].u32IOA           = 100;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[0].eIntroCOT    = INRO1;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[0].u16Range     = 10;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[0].u32CyclicTransTime   =   0;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[0].eControlModel  =  STATUS_ONLY ;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[0].u32SBOTimeOut    = 0;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[0].eClass           =   IEC_CLASS1;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[0].u16CommonAddress =   1;

        //Second object detail
        strncpy((char*)sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[1].ai8Name,"C_SE_TC_1",APP_OBJNAMESIZE);
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[1].eTypeID      = C_SE_TC_1;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[1].u32IOA           = 100;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[1].eIntroCOT    = NOTUSED;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[1].u16Range     = 10;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[1].u32CyclicTransTime   =   0;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[1].eControlModel  = DIRECT_OPERATE;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[1].u32SBOTimeOut    = 0;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[1].eClass           =   IEC_NO_CLASS;
        sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects[1].u16CommonAddress =   1;


        // Load configuration
        i16ErrorCode = IEC101LoadConfiguration(myClient, &sIEC101Config, &tErrorValue);
        if(i16ErrorCode != EC_NONE)
        {
            printf("\r\n IEC 60870-5-101 Library API Function -  IEC101LoadConfiguration() failed:   %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
            break;
        }

        // Start Client
        i16ErrorCode = IEC101Start(myClient, &tErrorValue);
        if(i16ErrorCode != EC_NONE)
        {
            printf("\r\n IEC 60870-5-101 Library API Function - IEC101Start() failed:  %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
            break;
        }


		fflush(stdout);
        set_tty_raw();         /* set up character-at-a-time */


        printf("\r\n Enter CTRL-X to Exit \t s - Send command called \t e - enable view traffic \t d - disable view traffic");
        printf("\r\n");

        sleep(5);



    // Loop
    while(bexit ==	FALSE)
    {


          u16Char =kb_getc();                                  /* char typed by user? */
		  if(u16Char == 0)
          {
            continue;
          }
		  else
		  {
				switch(u16Char)
				{
					case 0x03: //CTRL + C
					case 0x18: //CTRL + X
						set_tty_cooked();                           /* restore normal TTY mode */
                        bexit = TRUE;
                        break;

					case 0x73:  // s - send command called
						printf("\r\n ***********send command called ***********\r\n");
						sendcommand();
						break;

					case 0x65:  // e - enable view traffic
						printf("\r\n ***********view traffic enabled ***********\r\n");
						viewtraffic =TRUE;
						break;

					case 0x64:  // d - disable view traffic
					printf("\r\n ***********view traffic disabled ***********\r\n");
						viewtraffic =FALSE;
						break;

					default:
						break;
				}
		  }


		// update time interval
        usleep(1);

    }


    // Stop Client
    i16ErrorCode = IEC101Stop(myClient, &tErrorValue);
    if(i16ErrorCode != EC_NONE)
    {
        printf("\r\n IEC 60870-5-101 Library API Function - IEC101Stop() failed:  %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
        break;
    }


   }while(FALSE);


    printf("\r\n Enter any key to free");
   getchar();

   // Free Client
   i16ErrorCode = IEC101Free(myClient, &tErrorValue);
   if(i16ErrorCode != EC_NONE)
   {
        printf("\r\n IEC 60870-5-101 Library API Function - IEC101Free() failed:  %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
   }

   printf("\r\nBye\r\n");

   getchar();
   return(0);

}
