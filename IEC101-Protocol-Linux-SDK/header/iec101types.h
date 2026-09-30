/*****************************************************************************/
/*! \file        iec101types.h
 *  \brief       IEC101 API-types Header file
 *  \author      FreyrSCADA Embedded Solution Pvt Ltd
 *  \copyright (c) FreyrSCADA Embedded Solution Pvt Ltd. All rights reserved.
 *
 * THIS IS PROPRIETARY SOFTWARE AND YOU NEED A LICENSE TO USE OR REDISTRIBUTE.
 *
 * THIS SOFTWARE IS PROVIDED BY FREYRSCADA AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL FREYRSCADA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/ 
/*****************************************************************************/



#ifndef IEC101TYPES_H
    /*! \brief  Define IEC101 Types */
    #define IEC101TYPES_H       1


        #include <iec60870common.h>
        

    #ifdef __cplusplus
        extern "C" {
    #endif


        
        /*! \brief  Max Size of Rx Message sent to callback  */
        #define IEC101_MAX_RX_MESSAGE          261
        
        /*! \brief  Max Size of Tx Message sent to callback  */
        #define IEC101_MAX_TX_MESSAGE          261








        /*! Flags for enum eDataLinkTransmission mode*/
        enum eDataLinkTransmission
        {
            UNBALANCED_MODE                     = 0, /*!< Data link Unbalanced mode */
            BALANCED_MODE                       = 1, /*!< Data link Balanced mode*/
        };

        



        /*! List of error code returned by API functions */
        enum eIEC101AppErrorCodes
        {
            IEC101_APP_ERROR_ERRORVALUE_IS_NULL                = -4501,      /*!< APP Error value is  null*/
            IEC101_APP_ERROR_CREATE_FAILED                     = -4502,      /*!< IEC101 create function failed */
            IEC101_APP_ERROR_FREE_FAILED                       = -4503,      /*!< IEC101 free function failed */
            IEC101_APP_ERROR_SERVER_INITIALIZE                 = -4504,      /*!< IEC101 server initialize function failed */
            IEC101_APP_ERROR_LOADCONFIG_FAILED                 = -4505,      /*!< IEC101 Load configuration function failed */
            IEC101_APP_ERROR_CHECKALLOCLOGICNODE               = -4506,      /*!< IEC101 Load- check alloc logical node function failed */
            IEC101_APP_ERROR_START_FAILED                      = -4507,      /*!< IEC101 Start function failed */
            IEC101_APP_ERROR_STOP_FAILED                       = -4508,      /*!< IEC101 Stop function failed */
            IEC101_APP_ERROR_SETDEBUGOPTIONS_FAILED            = -4509,      /*!< IEC101 set debug option failed */
            IEC101_APP_ERROR_PHYSICALLAYEROPEN_FAILED          = -4510,      /*!< IEC101 Physical Layer open operation failed  */
            IEC101_APP_ERROR_PHYSICALLAYERCLOSE_FAILED         = -4511,      /*!< IEC101 Physical Layer close operation failed */
            IEC101_APP_ERROR_SERIALCOMOPEN_FAILED              = -4512,      /*!< IEC101 Physical Layer com open failed    */
            IEC101_APP_ERROR_SERIALCOMCLOSE_FAILED             = -4513,      /*!< IEC101 Physical Layer com close failed   */
            IEC101_APP_ERROR_PHYSICALINITIALIZE_FAILED         = -4514,      /*!< IEC101 Physical Layer initialization failed  */
            IEC101_APP_ERROR_SERIALRECEIVE_FAILED              = -4515,      /*!< IEC101 Data Link Layer serial receive failed */
            IEC101_APP_ERROR_UPDATE_FAILED                     = -4516,      /*!< IEC101 Update function failed */
            IEC101_APP_ERROR_CREATESEMAPHORE_PHYSCIALLAYER     = -4517,      /*!< IEC101 physical layer semaphore creation is invalid  */
            IEC101_APP_ERROR_DELETESEMAPHORE_PHYSCIALLAYER     = -4518,      /*!< IEC101 physical layer semaphore deletion is invalid  */
            IEC101_APP_ERROR_RESERVESEMAPHORE_PHYSCIALLAYER    = -4519,      /*!< IEC101 physical layer semaphore reservation is invalid  */
            IEC101_APP_ERROR_TIMESTRUCT_INVALID                = -4520,      /*!< Time structure is invalid */
            IEC101_APP_ERROR_READ_FAILED                       = -4521,      /*!< IEC101 Read function failed */
            IEC101_APP_ERROR_WRITE_FAILED                      = -4522,      /*!< IEC101 Write function failed */
            IEC101_APP_ERROR_SELECT_FAILED                     = -4523,      /*!< IEC101 Select function failed */
            IEC101_APP_ERROR_OPERATE_FAILED                    = -4524,      /*!< IEC101 Operate function failed */
            IEC101_APP_ERROR_CANCEL_FAILED                     = -4525,      /*!< IEC101 Cancel function failed */
            IEC101_APP_ERROR_GETDATATYPEANDSIZE_FAILED         = -4526,      /*!< IEC101 Get Data type & size function failed */
            IEC101_APP_ERROR_LINKLAYER_INITIALIZE              = -4527,      /*!< Link layer initialize failed*/
            IEC101_APP_ERROR_LINKLAYER_DEINITIALIZE            = -4528,      /*!< Link layer deinitialize failed*/
            IEC101_APP_ERROR_RESET_COMMAND_FAILED              = -4529,      /*!< Link layer master reset failed*/
            IEC101_APP_ERROR_CLIENT_INITIALIZE                 = -4530,      /*!< IEC101 Client initialize function failed */
            IEC101_APP_ERROR_RESETOFREMOTELINK_FAILED          = -4531,      /*!< IEC101 Master reset of remote link failed*/
            IEC101_APP_ERROR_FRAME_DECODE_FAILED               = -4532,      /*!< IEC101 master frame decode failed*/
            IEC101_APP_ERROR_REQUESTSTATUSLINK_FAILED          = -4533,      /*!< IEC101 master request status link failed*/
            IEC101_APP_ERROR_GENTERAL_INTERROGATION_FAILED     = -4534,      /*!< IEC101 master general interrogation failed*/
            IEC101_APP_ERROR_CLOCKSYNC_FAILED                  = -4535,      /*!< IEC101 master clock sync failed*/
            IEC101_APP_ERROR_FRAME_ENCODE_FAILED               = -4536,      /*!< IEC101 master frame encode failed*/
            IEC101_APP_ERROR_SINGLECOMMAND_FAILED              = -4537,      /*!< IEC101 master single command failed*/
            IEC101_APP_ERROR_DOUBLECOMMAND_FAILED              = -4538,      /*!< IEC101 master decode failed*/
            IEC101_APP_ERROR_STEPCOMMAND_FAILED                = -4539,      /*!< IEC101 master step position failed*/
            IEC101_APP_ERROR_SETNORMALIZEDCOMMAND_FAILED       = -4540,      /*!< IEC101 set normalized command failed*/
            IEC101_APP_ERROR_SETSCALEDCOMMAND_FAILED           = -4541,      /*!< IEC101 set scaled command failed*/
            IEC101_APP_ERROR_SETPOINTFLOATCOMMAND_FAILED       = -4542,      /*!< IEC101 set point float command failed*/
            IEC101_APP_ERROR_SETPOINTBITSTRING_FAILED          = -4543,      /*!< IEC101 set point bit string failed*/
            IEC101_APP_ERROR_CALLBACK_FAILED                   = -4544,      /*!< Callback error code for fail */
            IEC101_APP_ERROR_INVALID_POINTCOUNT                = -4545,      /*!< Total Number of Points exceeding Point Count*/
            IEC101_APP_ERROR_TESTLINK_FAILED                   = -4546,      /*!< IEC101 Master Test link failed*/
            IEC101_APP_ERROR_CLIENTSTATUS_FAILED               = -4547,      /*!< IEC101 MASTER Client status failed*/
            IEC101_APP_ERROR_FILE_TRANSFER_FAILED              = -4548,      /*!< IEC101 File Transfer Failed*/
            IEC101_APP_ERROR_LIST_DIRECTORY_FAILED             = -4549,      /*!< IEC101 get Directory faied*/
            IEC101_APP_ERROR_GET_OBJECTSTATUS_FAILED           = -4550,      /*!< IEC101 get object status faied*/
            IEC101_APP_ERROR_PARAMETERACT_FAILED               = -4551,      /*!< IEC101 parameter act command faied*/
            IEC101_APP_ERROR_CLIENT_STOPSERVERMULTIDROP        = -4552,		 /*!< IEC101 Client Api function stop server multidrop failed */
            



        };

        /*! List of error value returned by API functions */
        enum eIEC101AppErrorValues
        {
            IEC101_APP_ERRORVALUE_ERRORCODE_IS_NULL                =   -4501,          /*!< APP Error code is Null */
            IEC101_APP_ERRORVALUE_INVALID_INPUTPARAMETERS          =   -4502,          /*!< Supplied Parameters are invalid */
            IEC101_APP_ERRORVALUE_INVALID_APPFLAG                  =   -4503,          /*!< Invalid Application Flag , Client not supported by the API*/
            IEC101_APP_ERRORVALUE_UPDATECALLBACK_CLIENTONLY        =   -4504,          /*!< Update Callback used only for client*/
            IEC101_APP_ERRORVALUE_NO_MEMORY                        =   -4505,          /*!< Allocation of memory has failed */
            IEC101_APP_ERRORVALUE_INVALID_IEC101OBJECT             =   -4506,          /*!< Supplied IEC101Object is invalid */
            IEC101_APP_ERRORVALUE_IEC101FREE_CALLED_BEFORE_STOP    =   -4507,          /*!< APP state is running free function called before stop function*/
            IEC101_APP_ERRORVALUE_INVALID_STATE                    =   -4508,          /*!< IEC101OBJECT invalid state */
            IEC101_APP_ERRORVALUE_INVALID_DEBUG_OPTION             =   -4509,          /*!< invalid debug option */
            IEC101_APP_ERRORVALUE_TASK_CREATEFAILED                =   -4510,          /*!< Task creation failed */
            IEC101_APP_ERRORVALUE_TASK_STOPFAILED                  =   -4511,          /*!< Task stop failed */
            IEC101_APP_ERRORVALUE_INVALID_TYPEID                   =   -4512,          /*!< In the function eGroupID not valid, or later we will implement */
            IEC101_APP_ERRORVALUE_INVALIDUPDATE_COUNT              =   -4513,          /*!< Invalid update count */
            IEC101_APP_ERRORVALUE_UPDATEOBJECT_NOTFOUND            =   -4514,          /*!< IEC101Update function, for particular group id, index number not found, update failed */
            IEC101_APP_ERRORVALUE_INVALID_DATATYPE                 =   -4515,          /*!< IEC101Update function, for particular group id, psnewvalue invalid data type, update failed */
            IEC101_APP_ERRORVALUE_INVALID_DATASIZE                 =   -4516,          /*!< IEC101Update function, for particular group id, psnewvalue invalid data size, update failed */
            IEC101_APP_ERRORVALUE_INVALID_COMPORT_NUMBER           =   -4517,          /*!< IEC101 Load config parameters Communication Serial com port number is greater than 9*/
            IEC101_APP_ERRORVALUE_INVALID_BAUD_RATE                =   -4518,          /*!< IEC101 Load config parameters Communication SERIAL COM Invalid baud rate*/
            IEC101_APP_ERRORVALUE_INVALID_PARITY                   =   -4519,          /*!< IEC101 Load config parameters Communication SERIAL COM Invalid parity*/
            IEC101_APP_ERRORVALUE_INVALID_STOPBIT                  =   -4520,          /*!< IEC101 Load config parameters Communication SERIAL COM Invalid Stop bit*/
            IEC101_APP_ERRORVALUE_INVALID_WORDLENGTH               =   -4521,          /*!< IEC101 Load config parameters Communication SERIAL COM Invalid word length*/
            IEC101_APP_ERRORVALUE_INVALID_FLOWCONTROL              =   -4522,          /*!< IEC101 Load config parameters Communication SERIAL COM Invalid flow control */
            IEC101_APP_ERRORVALUE_INVALID_DEBUGOPTION              =   -4523,          /*!< IEC101 Load config parameters Invalid Debug option*/
            IEC101_APP_ERRORVALUE_INVALID_MASTER_LINKADDRESS       =   -4524,          /*!< IEC101 Load config parameters Invalid master address*/
            IEC101_APP_ERRORVALUE_INVALID_SLAVE_LINKADDRESS        =   -4525,          /*!< IEC101 Load config parameters invalid slave address*/
            IEC101_APP_ERRORVALUE_INVALID_SLAVEMASTER_ADDRESSSAME  =   -4526,          /*!< IEC101 Load config parameters master & slave address must not be equal*/
            IEC101_APP_ERRORVALUE_INVALID_DATETIME_STRUCT          =   -4527,          /*!< IEC101  invalid date time struct user input*/
            IEC101_APP_ERRORVALUE_INVALID_NUMBEROFOBJECTS          =   -4528,          /*!< IEC101  invalid no of objects user input*/
            IEC101_APP_ERRORVALUE_INVALID_IEC101OBJECTS            =   -4529,          /*!< IEC101 Load config parameters dnp3 objects , invalid u16NoofPoints must be 1-1000 & each group total no of objects 1 - 1000*/
            IEC101_APP_ERRORVALUE_READCALLBACK_CLIENTONLY          =   -4530,          /*!< Read Callback used only for client*/
            IEC101_APP_ERRORVALUE_CANCELCALLBACK_CLIENTONLY        =   -4531,          /*!< Cancel Callback used only for client*/
            IEC101_APP_ERRORVALUE_INVALID_IOA                      =   -4532,          /*!< IOA Value mismatch */
            IEC101_APP_ERRORVALUE_INVALID_CONTROLMODEL_SBOTIMEOUT  =   -4533,          /*!< Invalid enum control model |u32SBOTimeOut , for typeids from M_SP_NA_1 to M_EP_TF_1 -> STATUS_ONLY & u32SBOTimeOut 0 , for type ids C_SC_NA_1 to C_BO_TA_1 should not STATUS_ONLY & u32SBOTimeOut 0*/
            IEC101_APP_ERRORVALUE_INVALID_CYCLICTRANSTIME          =   -4534,          /*!< INVALID cyclic transmission time  for measurands 0 or 60 - 3600 */
            IEC101_APP_ERRORVALUE_INVALID_BUFFERSIZE               =   -4535,          /*!< Event buffer size minimum 100*/
            IEC101_APP_ERRORVALUE_INVALID_CLASS                    =   -4536,          /*!< Typeid c_XX_XX type id must be IEC_NOCLASS*/
            IEC101_APP_ERRORVALUE_INVLAID_EVENTBUF_OVERFLOWPER     =   -4537,          /*!< Load config parameters invalid, Event buffer OVER FLOW percentage < 25|| >100*/
            IEC101_APP_ERRORVALUE_INVALID_MAXAPDU_SIZE             =   -4538,          /*!< MAX_APDU Size should be minimum 42 MAX 255*/
            IEC101_APP_ERRORVALUE_INVALID_SHORTPULSETIME           =   -4539,          /*!< Pulse time should not be zero */
            IEC101_APP_ERRORVALUE_INVALID_LONGPULSETIME            =   -4540,          /*!< Pulse time should not be zero*/
            IEC101_APP_ERRORVALUE_INVALID_NOOFCLIENT               =   -4541,          /*!< u8 No of Client should not be zero */
            IEC101_APP_ERRORVALUE_INVALID_CLIENTOBJECTS            =   -4542,          /*!< psClientObjects should not be null */
            IEC101_APP_ERRORVALUE_INVALID_LINKADDRESS_SIZE         =   -4543,          /*!< Invalid link address size*/
            IEC101_APP_ERRORVALUE_INVALID_COT_SIZE                 =   -4544,          /*!< Invalid cause of transmission size*/
            IEC101_APP_ERRORVALUE_INVALID_IOA_SIZE                 =   -4545,          /*!< Invalid ioa size*/
            IEC101_APP_ERRORVALUE_INVALID_CA_SIZE                  =   -4546,          /*!< Invalid common */
            IEC101_APP_ERRORVALUE_INVALID_EPOS_ACK                 =   -4547,          /*!< Invalid positive ack*/
            IEC101_APP_ERRORVALUE_INVALID_ENEG_ACK                 =   -4548,          /*!< Invalid negative ack*/
            IEC101_APP_ERRORVALUE_INVALID_LINKADDRESS              =   -4549,          /*!< Broadcast address 255, or 65535 */
            IEC101_APP_ERRORVALUE_INVALID_IOA_ADDRESS              =   -4550,          /*!< Invalid ioa address may be 0 */
            IEC101_APP_ERRORVALUE_NACKLINK_BUSY                    =   -4551,          /*!< IEC101 Master link busy*/
            IEC101_APP_ERRORVALUE_NACKDATA_NOTAVILABLE             =   -4552,          /*!< IEC101 Master poll data not available*/
            IEC101_APP_ERRORVALUE_INVALID_LINKADDRESS_MISMATCH     =   -4553,          /*!< Link address must be unique */
            IEC101_APP_ERRORVALUE_SLAVE_NOT_CONNECTED              =   -4554,          /*!< IEC101 slave device not connected*/
            IEC101_APP_ERRORVALUE_INVALID_OPERATION_FLAG           =   -4555,          /*!< IEC101 cancel function invalid operation flag*/
            IEC101_APP_ERRORVALUE_UNKNOWN_TYPEID                   =   -4556,          /*!< IEC101 command operation slave responds unknown typeid*/
            IEC101_APP_ERRORVALUE_UNKNOWN_COT                      =   -4557,          /*!< IEC101 command operation slave responds unknown cause of transmission*/
            IEC101_APP_ERRORVALUE_UNKNOWN_CASDU                    =   -4558,          /*!< IEC101 command operation slave responds unknown common asdu*/
            IEC101_APP_ERRORVALUE_UNKNOWN_IOA                      =   -4559,          /*!< IEC101 command operation slave responds unknown ioa*/
            IEC101_APP_ERRORVALUE_INVALID_QUALIFIER                =   -4560,          /*!< IEC101 command operation invalid qualifier/KPA*/
            IEC101_APP_ERRORVALUE_INVALID_DATAPOINTER              =   -4561,          /*!< Void pvdata is invalid */
            IEC101_APP_ERRORVALUE_CALLBACK_FAILED                  =   -4562,          /*!< Callback error value for fail */
            IEC101_APP_ERRORVALUE_INVALID_POINTCOUNT               =   -4563,          /*!< Total Number of Points exceeding Point Count*/
            IEC101_APP_ERRORVALUE_INVALID_COUNT_SERIALCONNECTIONS  =   -4564,          /*!< Invalid count Serial connections*/
            IEC101_APP_ERRORVALUE_INVALID_DATALINK_MODE            =   -4565,          /*!< Invalid Datalink mode*/
            IEC101_APP_ERRORVALUE_COMMAND_TIMEOUT                  =   -4566,          /*!< After command timeout, client did not receive valid response from server */
            IEC101_APP_ERRORVALUE_INVALID_RANGE                    =   -4567,          /*!< Invalid range 0- 1000 */
            IEC101_APP_ERRORVALUE_INVALID_COT                      =   -4568,          /*!< For commands the COT must be NOTUSED */
            IEC101_APP_ERRORVALUE_INVALID_DATALINKADDRESS          =   -4569,          /*!< Datalink address mismatch */
            IEC101_APP_ERRORVALUE_INVALID_KPA                      =   -4570,          /*!< Invalid Kind of Parameter , For typeids,P_ME_NA_1, P_ME_NB_1, P_ME_NC_1 - Kind of parameter , refer enum eKPA for other typeids - PARAMETER_NONE */
            IEC101_APP_ERRORVALUE_INVALID_QRP                      =   -4571,          /*!< Invalid quality of reset process */
            IEC101_APP_ERRORVALUE_INVALID_COMMONADDRESS            =   -4572,          /*!< Invalid common addressor station address */ 
            IEC101_APP_ERRORVALUE_FILETRANSFER_TIMEOUT             =   -4573,          /*!< file transfer timeout, no response from server */
            IEC101_APP_ERRORVALUE_FILE_NOT_READY                   =   -4574,          /*!< file not ready */
            IEC101_APP_ERRORVALUE_SECTION_NOT_READY                =   -4575,          /*!< Section not ready */  
            IEC101_APP_ERRORVALUE_FILE_OPEN_FAILED                 =   -4576,          /*!< File Open Failed */ 
            IEC101_APP_ERRORVALUE_FILE_CLOSE_FAILED                =   -4577,          /*!< File Close Failed */
            IEC101_APP_ERRORVALUE_FILE_WRITE_FAILED                =   -4578,          /*!< File Write Failed */
            IEC101_APP_ERRORVALUE_FILETRANSFER_INTERUPTTED         =   -4579,          /*!< File Transfer Interrupted */
            IEC101_APP_ERRORVALUE_SECTIONTRANSFER_INTERUPTTED      =   -4580,          /*!< Section Transfer Interrupted */
            IEC101_APP_ERRORVALUE_FILE_CHECKSUM_FAILED             =   -4581,          /*!< File Checksum Failed*/
            IEC101_APP_ERRORVALUE_SECTION_CHECKSUM_FAILED          =   -4582,          /*!< Section Checksum Failed*/
            IEC101_APP_ERRORVALUE_FILE_NAME_UNEXPECTED             =   -4583,          /*!< File Name Unexpected*/
            IEC101_APP_ERRORVALUE_SECTION_NAME_UNEXPECTED          =   -4584,          /*!< Section Name Unexpected*/
            IEC101_APP_ERRORVALUE_DIRECTORYCALLBACK_CLIENTONLY     =   -4585,          /*!< Directory Callback used only for client*/
            IEC101_APP_ERRORVALUE_INVALID_BACKSCANTIME             =   -4586,          /*!< INVALID back ground scan time, 0 or 60 - 3600*/
            IEC101_APP_ERRORVALUE_INVALID_FILETRANSFER_PARAMETER   =   -4587,          /*!< Server loadconfig, file transfer enabled, but the dir path and number of files not valid*/      
            IEC101_APP_ERRORVALUE_FILETRANSFER_DISABLED            =   -4588,          /*!< File transfer disabled in the settings*/
            IEC101_APP_ERRORVALUE_INVALID_INTIAL_DATABASE_QUALITYFLAG = -4589,         /*!< Invalid settings initialquality flag*/
            IEC101_APP_ERRORVALUE_TRIAL_EXPIRED                     = -4590,           /*!< Trial software expired - contact tech.support@freyrscada.com*/
            IEC101_APP_ERRORVALUE_TRIAL_INVALID_POINTCOUNT          = -4591,     		/*!< Trial software - Total Number of Points exceeded, maximum 100 points*/
			IEC101_APP_ERRORVALUE_SERVER_DISABLED						= -4592,		/*!< Server functionality disabled in the api, please contact - tech.support@freyrscada.com */
			IEC101_APP_ERRORVALUE_CLIENT_DISABLED						= -4593,		/*!< Client functionality disabled in the api, please contact -tech.support@freyrscada.com*/


		};
    

       
        /*!   Flags for eDataLinkAddressSize - Data link address size*/
        enum eDataLinkAddressSize
        {
            DL_NOT_PRESENT = 0,        /*!< in the frame Data link address present or not */
            DL_ONE_BYTE    = 1,        /*!< 1 Octet Size - DataLinkAddress */
            DL_TWO_BYTE    = 2,        /*!< 2 Octet Size - DataLinkAddress*/
        };

        /*!   Flags for eInformationObjectAddressSize - Information object address size*/
        enum eInformationObjectAddressSize
        {
            IOA_ONE_BYTE        = 1,        /*!< 1 Octet Size of Information object address*/
            IOA_TWO_BYTE        = 2,        /*!< 2 Octet Size of Information object address*/
            IOA_THREE_BYTE      = 3,        /*!< 3 Octet Size of Information object address*/
        };

        /*!  Flags for eCommonAddressSize - Common Address size*/
        enum eCommonAddressSize
        {
            CA_ONE_BYTE     = 1,        /*!< 1 Octet Size of Common Address */
            CA_TWO_BYTE     = 2,        /*!< 2 Octet Size of Common Address */
        };



        /*!  Flags for ePositiveACK*/
        enum ePositiveACK
        {
            SINGLE_CHAR_ACK_E5      =   0xE5,   /*!< Positive ACK e5*/
            FIXED_FRAME_ACK         =   0x10,   /*!< Positive ACK - fixed frame*/
        };

        /*!  Flags for eNegativeACK */
        enum eNegativeACK
        {
            SINGLE_CHAR_NACK_A2     =   0xA2,   /*!< Negative ACK - a2*/
            FIXED_FRAME_NACK        =   0x10,   /*!< Negative ACK - fixed frame*/
        };

         /*! \typedef enum eIECClass
            *  \brief IEC Class
        */
        enum eIECClass
        {
            IEC_NO_CLASS        = 0,        /*!< IEC_NO_CLASS for Output point Data, if assigned for input points event will not generate. */
            IEC_CLASS1          = 1,        /*!< Class 1 for high priority data */
            IEC_CLASS2          = 2,        /*!< Class 2 for low priority data  */
        };









        /*! \brief  IEC101 Object Structure */
        struct sIEC101Object
        {
            enum eIEC870TypeID                  eTypeID;                    /*!< Type Identifcation see  */
            Unsigned32                          u32IOA;                     /*!< Informatiion Object Address */
            Unsigned16                          u16Range;                   /*!< Range */
            enum eIEC870COTCause                eIntroCOT;                  /*!< Interrogation group */
            enum eControlModelConfig            eControlModel;              /*!< Control Model specified in eControlModelFlags */
            Unsigned32                          u32SBOTimeOut;              /*!< Select Before Operate Timeout  in milliseconds*/
            enum eIECClass                      eClass;                     /*!< Class of data */
            enum eKindofParameter               eKPA;                       /*!< For typeids,P_ME_NA_1, P_ME_NB_1, P_ME_NC_1 - Kind of parameter , refer enum eKPA for other typeids - PARAMETER_NONE*/
            Unsigned16                          u16CommonAddress;           /*!< Common Address , 0 - not used, 1-65534 station address, 65535 = global address (only master can use this)*/
            Unsigned32                          u32CyclicTransTime;         /*!< Periodic or Cyclic Transmissin time in seconds. If 0 do not transmit Periodically (only applicable to measured values M_ME_NA_1, M_ME_NB_1, M_ME_NC_1, M_ME_ND_1) MINIMUM 60 Seconds, max 3600 seconds (1 hour)*/
            Unsigned32                          u32BackgroundScanPeriod;    /*!< in seconds, if 0 the background scan will not be performed, MINIMUM 60 Seconds, max 3600 seconds (1 hour), all monitoring iinformation except Integrated totals will be transmitteed . the reporting typeid without timestamp*/
            Integer8                            ai8Name[APP_OBJNAMESIZE];   /*!< Name */
            
        };

        /*! \brief  IEC101 Debug Parameters */
        struct sIEC101DebugParameters
        {
            Unsigned32                      u32DebugOptions;           /*!< Debug Option see eDebugOptionsFlag */
        };

        /*! \brief      Server protocol settings parameters structure  */
        struct sIEC101ServerProtocolSettings
        {
            enum eDataLinkTransmission          eDataLink;                          /*!< Data link transmission - Unbalanced mode - 0, Balanced mode -1*/
            enum eDataLinkAddressSize           elinkAddrSize;                      /*!< Data link address size*/
            Unsigned16                          u16DataLinkAddress;                 /*!< Data link address*/
            enum eCauseofTransmissionSize       eCOTsize;                           /*!< Cause of transmission size*/
            enum eInformationObjectAddressSize  eIOAsize;                           /*!< Information object address size*/
            enum eCommonAddressSize             eCASize ;                           /*!< Common Address Size , 0-one octet, 1-two octet*/            
            enum ePositiveACK                   ePosACK;                            /*!< positive ack*/
            enum eNegativeACK                   eNegACK;                            /*!< Negative ack*/
            Unsigned16                          u16Class1EventBufferSize;           /*!< class 1 Event buffer size minimum 100, max u16value */
            Unsigned16                          u16Class2EventBufferSize;           /*!< class 2 Event buffer size minimum 100, max u16value */
            Unsigned8                           u8Class1BufferOverFlowPercentage;   /*!< Class 1 buffer overflow percentage 50 to 95*/
            Unsigned8                           u8Class2BufferOverFlowPercentage;   /*!< Class 2 buffer overflow percentage 50 to 95*/
            Unsigned8                           u8MaxAPDUSize;                      /*!< Monitoring Information - Maximum APDU Size, Maximum Length of APDU 42 to 255 (if max value set to 255, the tx length will be 261)*/
            Unsigned32                          u32ClockSyncPeriod;                 /*!< Clock Synchronisation period in milliseconds. If 0 than Clock Synchronisation command is not expected from Master */


            /* Controlled stations expect the reception of clock synchronization messages 
            within agreed time intervals. When the synchronization command does not arrive within this 
            time interval, the controlled station sets all time-tagged information objects with a mark 
            that the time tag may be inaccurate (invalid).*/

            Unsigned16                          u16ShortPulseTime;                              /*!< Short Pulse Time in milliseconds */
            Unsigned16                          u16LongPulseTime;                               /*!< Long Pulse Time in milliseconds */
            Boolean                             bGenerateACTTERMrespond;                        /*!< if Yes , Generate ACTTERM  responses for operate commands*/    
            Unsigned32                          u32BalancedModeTestConnectionSignalInterval;    /*!< in seconds, in Balanced mode , nothing received, after this interval, server will send the test link function to master 60 seconds to 3600 seconds*/
            Boolean                             bEnableDoubleTransmission;                      /*!< enable double transmission*/
            Unsigned8                           u8TotalNumberofStations;                        /*!< Total number of stations / common address 1-5 */         
            Boolean                             bEnableFileTransfer;                            /*!< enable / disable File Transfer */
            Unsigned16                          u16MaxFilesInDirectory;                         /*!< Maximum No of Files in Directory(default 25) */
            Boolean                             bTransmitSpontMeasuredValue;                    /*!< transmit M_ME measured values in spontanous message */ 
            Boolean                             bTransmitInterrogationMeasuredValue;            /*!< transmit M_ME measured values in General interrogation */
            Boolean                             bTransmitBackScanMeasuredValue;                 /*!< transmit M_ME measured values in background message */
            Unsigned8                           u8InitialdatabaseQualityFlag;                   /*!< 0- good/valid, 1 BIT- iv, 2 BIT-nt,  MAX VALUE -3   */
            Boolean                             bUpdateCheckTimestamp;                          /*!< If it true, the timestamp change also generate event  during the iec101update */
			Boolean 							bSequencebitSet;						  		/*!< If it true, Server builds iec frame with sequence for monitoring information without time stamp */
			Integer8                            ai8FileTransferDirPath[MAX_DIRECTORY_PATH];     /*!< File Transfer Directory Path */
            Unsigned16                          au16CommonAddress[MAX_CA];                      /*!< In a single physical device we can run many stations,station address- Common Address , 0 - not used, 1-65534 , 65535 = global address (only master can use this)*/
                    
        };

        /*! \brief      Client protocol settings parameters structure  */
        struct sIEC101ClientProtocolSettings
        {
            enum eDataLinkAddressSize           elinkAddrSize;                      /*!< Data link address size*/
            Unsigned16                          u16DataLinkAddress;                 /*!< Data link address*/
            enum eCauseofTransmissionSize       eCOTsize;                           /*!< Cause of transmission size*/
            enum eInformationObjectAddressSize  eIOAsize;                           /*!< Information object address size*/
            enum eCommonAddressSize             eCASize;                            /*!< Common Address Size , 0-one octet, 1-two octet*/
            Unsigned8                           u8TotalNumberofStations;            /*!< Total number of stations / common address 1-5 */  
            Unsigned8                           u8OriginatorAddress;                /*!< if cot size is 2 octet, we need to set originator address, default 0 */
            Unsigned32                          u32LinkLayerTimeout;                /*!< in ms, minimum 1000  */
            Unsigned32                          u32PollInterval;                    /*!< in msec  min 100 */
            Unsigned32                          u32GeneralInterrogationInterval;    /*!< in sec if 0 , gi will not send in particular interval*/
            Unsigned32                          u32Group1InterrogationInterval;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
            Unsigned32                          u32Group2InterrogationInterval;    /*!< in sec if 0 , group 2 interrogation will not send in particular interval*/
            Unsigned32                          u32Group3InterrogationInterval;    /*!< in sec if 0 , group 3 interrogation will not send in particular interval*/
            Unsigned32                          u32Group4InterrogationInterval;    /*!< in sec if 0 , group 4 interrogation will not send in particular interval*/
            Unsigned32                          u32Group5InterrogationInterval;    /*!< in sec if 0 , group 5 interrogation will not send in particular interval*/
            Unsigned32                          u32Group6InterrogationInterval;    /*!< in sec if 0 , group 6 interrogation will not send in particular interval*/
            Unsigned32                          u32Group7InterrogationInterval;    /*!< in sec if 0 , group 7 interrogation will not send in particular interval*/
            Unsigned32                          u32Group8InterrogationInterval;    /*!< in sec if 0 , group 8 interrogation will not send in particular interval*/
            Unsigned32                          u32Group9InterrogationInterval;    /*!< in sec if 0 , group 9 interrogation will not send in particular interval*/
            Unsigned32                          u32Group10InterrogationInterval;    /*!< in sec if 0 , group 10 interrogation will not send in particular interval*/
            Unsigned32                          u32Group11InterrogationInterval;    /*!< in sec if 0 , group 11 interrogation will not send in particular interval*/
            Unsigned32                          u32Group12InterrogationInterval;    /*!< in sec if 0 , group 12 interrogation will not send in particular interval*/
            Unsigned32                          u32Group13InterrogationInterval;    /*!< in sec if 0 , group 13 interrogation will not send in particular interval*/
            Unsigned32                          u32Group14InterrogationInterval;    /*!< in sec if 0 , group 14 interrogation will not send in particular interval*/
            Unsigned32                          u32Group15InterrogationInterval;    /*!< in sec if 0 , group 15 interrogation will not send in particular interval*/
            Unsigned32                          u32Group16InterrogationInterval;    /*!< in sec if 0 , group 16 interrogation will not send in particular interval*/
            Unsigned32                          u32CounterInterrogationInterval;    /*!< in sec if 0 , ci will not send in particular interval*/
            Unsigned32                          u32Group1CounterInterrogationInterval;    /*!< in sec if 0 , group 1 counter interrogation will not send in particular interval*/
            Unsigned32                          u32Group2CounterInterrogationInterval;    /*!< in sec if 0 , group 2 counter interrogation will not send in particular interval*/
            Unsigned32                          u32Group3CounterInterrogationInterval;    /*!< in sec if 0 , group 3 counter interrogation will not send in particular interval*/
            Unsigned32                          u32Group4CounterInterrogationInterval;    /*!< in sec if 0 , group 4 counter interrogation will not send in particular interval*/            
            Unsigned32                          u32ClockSyncInterval;               /*!< in sec if 0 , clock sync, will not send in particular interval */
            Unsigned32                          u32CommandTimeout;                  /*!< in ms, minimum 1000  */
            Unsigned32                          u32FileTransferTimeout;             /*!< in ms, minimum 3000  */
            Boolean                             bEnableFileTransfer;             /*!< enable / disable File Transfer */
            Boolean                             bCommandResponseActtermUsed;        /*!< server side is ACTTERM Used for command termination */
            Unsigned32                          u32BalancedModeTestConnectionSignalInterval; /*!< in seconds, in Balanced mode , nothing received, after this interval, client will send the test link function to server */
            Boolean                             bUpdateCallbackCheckTimestamp; /*!< if it true ,the timestamp change also create the updatecallback */
            Integer8                            ai8FileTransferDirPath[MAX_DIRECTORY_PATH]; /*!< File Transfer Directory Path */
            Unsigned16                          au16CommonAddress[MAX_CA];                      /*!< in a single physical device we can run many stations,station address- Common Address , 0 - not used, 1-65534 , 65535 = global address (only master can use this)*/
            

        };

        /*! \brief      Server  settings parameters structure  */
        struct sIEC101ServerSettings
        {
            Unsigned8                                   u8NumberofSerialPortConnections;                        /*!<  Total number of serial port commnication for master to connect */
            struct sIEC101ServerProtocolSettings              sServerProtSet;         /*!<  server protocol settings*/
            struct sIEC101DebugParameters               sDebug;                             /*!< Debug options settings on loading the configuarion See struct sIEC101DebugParameters */
            Boolean                                     benabaleUTCtime;                            /*!< enable utc time/ local time*/  
            Unsigned16                                  u16NoofObject;                      /*!< Total number of IEC101 Objects */
            struct sIEC101Object                        *psIEC101Objects;                  /*!< Pointer to strcuture IEC 101 Objects - according u16NoofObject*/
            struct sSerialCommunicationSettings         *psSerialSet;             /*!< Serial Communication Port Settings according to u8NumberofSerialPortConnections*/
            
        };

        /*! \brief      Client object structure  */
        struct sIEC101ClientObject
        {
            struct sSerialCommunicationSettings         sSerialSet;             /*!< Serial Communication Port Settings */
            struct sIEC101ClientProtocolSettings              sClientProtSet;         /*!< Protocol settings*/
            Unsigned16                      			u16NoofObject;          /*!< Total number of IEC101 Objects */
            struct sIEC101Object            			*psIEC101Objects;       /*!< Pointer to strcuture IEC 101 Objects accroding to u16NoofObject*/
        };

        /*! \brief      Client settings parameters structure  */
        struct sIEC101ClientSettings
        {
            Boolean                         bAutoGenIEC101DataObjects;          /*!< if it true ,the IEC101 Objects created automatically, use u16NoofObject = 0, psIEC104Objects = NULL*/
			Unsigned16						u16UpdateBuffersize;				/*!< if bAutoGenIEC101DataObjects true, update callback buffersize, approx 3 * max count of monitoring points in the server */		
			enum eDataLinkTransmission      eLink;                              /*!< Data link transmission - Unbalanced mode - 0, Balanced mode -1*/
            struct sIEC101DebugParameters   sDebug;                             /*!< Debug options settings on loading the configuarion See struct sIEC101DebugParameters */
            Boolean                         benabaleUTCtime;                    /*!< enable utc time/ local time*/  
            Unsigned8                       u8NoofClient;                       /*!< Total number of client Objects */
            struct sIEC101ClientObject            *psClientObjects;                   /*!< Pointer to strcuture IEC 101 Objects accroding to u8NoofClient */
            
        };

        /*! \brief  IEC101 Configuration parameters  */
        struct sIEC101ConfigurationParameters
        {
            struct sIEC101ServerSettings          sServerSet;                         /*!< IEC101 Server settings*/
            struct sIEC101ClientSettings          sClientSet;                         /*!< IEC101 Client settings*/
        };


        /*! \brief      This structure hold the identification of a IEC101 Data Attribute */
        struct sIEC101DataAttributeID
        {
            Unsigned16           u16SerialPortNumber;     /*!< Serial COM port number*/
            Unsigned16          u16DataLinkAddress;     /*!< Data Link Address */
            Unsigned32          u32IOA;                 /*!< Information Object Address */
            enum eIEC870TypeID  eTypeID;                /*!< Type Identification */
            Unsigned16          u16CommonAddress;       /*!< Orginator Address /Common Address , 0 - not used, 1-65534 station address, 65535 = global address (only master can use this)*/
            void                *pvUserData;            /*!< Application specific User Data */
        };


        /*! \brief      A Data object structure. Used to exchange data objects between IEC101 object and application. */
        struct sIEC101DataAttributeData
        {
            struct sTargetTimeStamp    sTimeStamp;         /*!< TimeStamp */
            tIEC870Quality          tQuality;           /*!< Quality of Data see eIEC101QualityFlags */
            enum    eDataTypes      eDataType;          /*!< Data Type */
            enum    eDataSizes      eDataSize;          /*!< Data Size */
            Boolean                 bTimeInvalid;       /*!< time Invalid */
            enum eTimeQualityFlags eTimeQuality;  /*!< time quality */
            Unsigned16              u16ElapsedTime;      /*!< Elapsed time(M_EP_TA_1, M_EP_TD_1) /Relay duration time(M_EP_TB_1, M_EP_TE_1) /Relay Operating time (M_EP_TC_1, M_EP_TF_1)  In Milliseconds */
			Boolean 				bTRANSIENT; 								/*!<transient state indication result value step position information*/
			Unsigned8 				u8Sequence;								/*!< m_it - Binary counter reading - Sequence notation*/
			void                    *pvData;            /*!< Pointer to Data */
            
        };

        /*! \brief      Parameters provided by read callback   */
        struct sIEC101ReadParameters
        {
            Unsigned8   u8OriginatorAddress;        /*!< client orginator address */
            Unsigned8   u8Dummy;                    /*!< Dummy only for future expansion purpose */
        };

        /*! \brief      Parameters provided by write callback   */
        struct sIEC101WriteParameters
        {
            Unsigned8   u8OriginatorAddress;        /*!< client orginator address */
            enum eIEC870COTCause  eCause;           /*!< cause of transmission */
            Unsigned8   u8Dummy;                    /*!< Dummy only for future expansion purpose */
        };

        /*! \brief      Parameters provided by update callback   */
        struct sIEC101UpdateParameters
        {
            enum eIEC870COTCause  eCause;                       /*!< cause of transmission */
            enum eKindofParameter   eKPA;                       /*!< For typeids,P_ME_NA_1, P_ME_NB_1, P_ME_NC_1 - Kind of parameter , refer enum eKPA*/			
		};

        /*! \brief      Parameters provided by Command callback   */
        struct sIEC101CommandParameters
        {
            Unsigned8           u8OriginatorAddress;         /*!<  client orginator address */
            enum eCommandQOCQU  eQOCQU;                     /*!<Qualifier of Commad */
            Unsigned32          u32PulseDuration;           /*!< Pulse Duration Based on the Command Qualifer */
        };
        
        /*! \brief      Parameters provided by parameter act term callback   */
        struct sIEC101ParameterActParameters
        {
             Unsigned8           u8OriginatorAddress;         /*!<  client orginator address */
             Unsigned8              u8QPA;                  /*!< Qualifier of parameter activation/kind of parameter , for typeid P_AC_NA_1, please refer 7.2.6.25, for typeid 110,111,112 please refer KPA 7.2.6.24*/
        };


        /*! \brief  IEC101 Debug Callback Data */
        struct sIEC101DebugData
        {
            Unsigned32                      u32DebugOptions;                            /*!< Debug Option see eDebugOptionsFlag */
            Integer16                       i16ErrorCode;                                 /*!< error code if any */
            tErrorValue                     tErrorvalue;                                /*!< error value if any */
            Unsigned16                      u16ComportNumber;                            /*!< serial com port number for transmit & receive */
            Unsigned16                      u16RxCount;                                 /*!< Received data count*/
            Unsigned16                      u16TxCount;                                 /*!< Transmitted data count */
            struct sTargetTimeStamp            sTimeStamp;                                 /*!< TimeStamp */
            Unsigned8                       au8ErrorMessage[MAX_ERROR_MESSAGE];         /*!< error message */
            Unsigned8                       au8WarningMessage[MAX_WARNING_MESSAGE];     /*!< warning message */
            Unsigned8                       au8RxData[IEC101_MAX_RX_MESSAGE];                  /*!< Received data from master */
            Unsigned8                       au8TxData[IEC101_MAX_TX_MESSAGE];                  /*!< Transmitted data from master */
            
        };

                /*! \brief IEC101 File Attributes*/
        struct sIEC101FileAttributes
        {
            Boolean                     bFileDirectory;                  /*!< File /Directory File-1,Directory 0 */                      
            Unsigned16                  u16FileName;                     /*!< File Name */
            UnSize                      zFileSize;                       /*!< File size*/
            Boolean                     bLastFileOfDirectory;            /*!< Last File Of Directory*/
            struct sTargetTimeStamp        sLastModifiedTime;               /*!< Last Modified Time*/        
        };

        /*! \brief IEC101 Directory List*/
        struct sIEC101DirectoryList
        {
            Unsigned16                      u16FileCount;                         /*!< File Count read from the Directory */
            struct sIEC101FileAttributes    *psFileAttrib;                        /*!< Pointer to File Attributes */
        };


            /*! \brief error code more description */
        struct sIEC101ErrorCode
        {
                Integer16 iErrorCode;        /*!< errorcode */
                char* shortDes;     /*!< error code short description*/
                char* LongDes;     /*!< error code brief description*/

        };

        
        /*! \brief error value more description */
        struct sIEC101ErrorValue
        {
            Integer16 iErrorValue;       /*!< errorvalue */
            char* shortDes;     /*!< error value short description*/
            char* LongDes;     /*!< error value brief description*/

        };


        struct sIEC101AppObject; // Forward Declaration of struct

        /*! \brief  Pointer to a IEC 101 object */
        typedef struct sIEC101AppObject *IEC101Object;


        //For callback , from slave side configuration can give errorcode = EC_NONE  means command successful
        // else command fail


        /*  errror codes for callback
            EC_NONE                    = 0,              // callback success
            IEC101_APP_ERROR_CALLBACK_FAILED         = -44,            // callback error code for fail
        */

        /* error values for callback
           EV_NONE                              = 0,                      // Everything was ok
           IEC101_APP_ERRORVALUE_CALLBACK_FAILED                   =   -1062,   // callback error value for fail
        */


        /*! \brief          IEC101 Read call-back
         *  \ingroup        IEC101Call-back
         *
         *  \param[in]      u16ObjectId     IEC101 object identifier
         *  \param[in]      ptReadID        Pointer to IEC 101 Data Attribute ID
         *  \param[out]     ptReadValue     Pointer to IEC 101 Data Attribute Data
         *  \param[in]      ptReadParams    Pointer to Read parameters      
         *  \param[out]     ptErrorValue    Pointer to Error Value (if any error occurs while creating the object)
         *
         *  \return         IEC101_APP_ERROR_NONE on success
         *  \return         otherwise error code
         *
         *  \code
         *                  //Sample read call-back
         *                  enum eAppErrorCodes cbRead(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptReadID,struct sIEC101DataAttributeData *ptReadValue, struct sIEC101ReadParameters *ptReadParams, tErrorValue *ptErrorValue )
         *                  {
         *                      enum eAppErrorCodes     i16ErrorCode        = IEC101_APP_ERROR_NONE;
         *
         *                      // If the type ID and IOA matches handle and update the value.
         *                      
         *                          
         *                      return i16ErrorCode;
         *                  }
         *  \endcode
         */
        typedef Integer16 (*IEC101ReadCallback)(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptReadID, struct sIEC101DataAttributeData *ptReadValue, struct sIEC101ReadParameters *ptReadParams, tErrorValue *ptErrorValue );

        /*! \brief          IEC101 Write call-back
         *  \ingroup        IEC101Call-back
         *
         *  \param[in]      u16ObjectId     IEC101 object identifier
         *  \param[in]      ptWriteID       Pointer to IEC 101 Data Attribute ID
         *  \param[in]      ptWriteValue    Pointer to IEC 101 Data Attribute Data
         *  \param[in]      ptWriteParams   Pointer to Write parameters       
         *  \param[out]     ptErrorValue    Pointer to Error Value (if any error occurs while creating the object)
         *
         *  \return         IEC101_APP_ERROR_NONE on success
         *  \return         otherwise error code
         *
         *  \code
         *                  //Sample write call-back
         *                  enum eAppErrorCodes cbWrite(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptWriteID,struct sIEC101DataAttributeData *ptWriteValue, struct sIEC101WriteParameters *ptWriteParams, tErrorValue *ptErrorValue )
         *                  {
         *                      enum eAppErrorCodes     i16ErrorCode        = IEC101_APP_ERROR_NONE;
         *                      struct sTargetTimeStamp    sReceivedTime   = {0};
         *
         *                      // If the type ID is Clock Synchronisation than set time and date based on target
         *                      if(ptWriteID->eTypeID == C_CS_NA_1)
         *                      {
         *                          memcpy(&sReceivedTime, ptWriteValue->sTimeStamp, sizeof(struct sTargetTimeStamp));
         *                          SetTimeDate(&sReceivedTime);
         *                      }
         *                          
         *                      return i16ErrorCode;
         *                  }
         *  \endcode
         */
        typedef Integer16 (*IEC101WriteCallback)(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptWriteID, struct sIEC101DataAttributeData *ptWriteValue,struct sIEC101WriteParameters *ptWriteParams, tErrorValue *ptErrorValue);

        /*! \brief          IEC101 Update call-back
         *  \ingroup        IEC101Call-back
         *
         *  \param[in]      u16ObjectId     IEC101 object identifier
         *  \param[in]      ptUpdateID       Pointer to IEC 101 Data Attribute ID
         *  \param[in]      ptUpdateValue    Pointer to IEC 101 Data Attribute Data
         *  \param[in]      ptUpdateParams   Pointer to Update parameters       
         *  \param[out]     ptErrorValue     Pointer to Error Value (if any error occurs while creating the object)
         *
         *  \return         IEC101_APP_ERROR_NONE on success
         *  \return         otherwise error code
         *
         *  \code
         *                  //Sample update call-back
         *                  enum eAppErrorCodes cbUpdate(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptUpdateID, struct sIEC101DataAttributeData *ptUpdateValue, struct sIEC101UpdateParameters *ptUpdateParams, tErrorValue *ptErrorValue )
         *                  {
         *                      enum eAppErrorCodes     i16ErrorCode            = IEC101_APP_ERROR_NONE;
         *
         *                      // Check -  we received the type ID and IOA than display the value
         *                      // we received the update from server 
         *                          
         *                      return i16ErrorCode;
         *                  }
         *  \endcode
         */
        typedef Integer16 (*IEC101UpdateCallback)(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptUpdateID, struct sIEC101DataAttributeData *ptUpdateValue,struct sIEC101UpdateParameters *ptUpdateParams, tErrorValue *ptErrorValue);

        /*! \brief          IEC101 Control Select call-back
         *  \ingroup        IEC101Call-back
         *  
         *  \param[in]      u16ObjectId     IEC101 object identifier
         *  \param[in]      ptSelectID       Pointer to IEC 101 Data Attribute ID
         *  \param[in]      ptSelectValue    Pointer to IEC 101 Data Attribute Data
         *  \param[in]      ptSelectParams   Pointer to select parameters       
         *  \param[out]     ptErrorValue     Pointer to Error Value (if any error occurs while creating the object)
         *
         *  \return         IEC101_APP_ERROR_NONE on success
         *  \return         otherwise error code
         *
         *  \code
         *                  //Sample select call-back
         *                  
         *                  enum eAppErrorCodes cbSelect(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptSelectID, struct sIEC101DataAttributeData *ptSelectValue, struct sIEC101CommandParameters *ptSelectParams, tErrorValue *ptErrorValue )     
         *                  {
         *                      enum eAppErrorCodes     i16ErrorCode            = IEC101_APP_ERROR_NONE;
         *
         *                      // Check Server received Select command from client, Perform Select in the hardware according to the typeID and IOA 
         *                      // Hardware Control Select Operation;
         *                          
         *                      return i16ErrorCode;
         *                  }
         *  \endcode
         */
        typedef Integer16 (*IEC101ControlSelectCallback)(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptSelectID, struct sIEC101DataAttributeData *ptSelectValue,struct sIEC101CommandParameters *ptSelectParams, tErrorValue *ptErrorValue);

        /*! \brief          IEC101 Control Operate call-back
         *  \ingroup        IEC101Call-back
         *  
         *  \param[in]      u16ObjectId     IEC101 object identifier
         *  \param[in]      ptOperateID      Pointer to IEC 101 Data Attribute ID
         *  \param[in]      ptOperateValue   Pointer to IEC 101 Data Attribute Data
         *  \param[in]      ptOperateParams  Pointer to Operate parameters       
         *  \param[out]     ptErrorValue     Pointer to Error Value (if any error occurs while creating the object)
         *
         *  \return         IEC101_APP_ERROR_NONE on success
         *  \return         otherwise error code
         *
         *  \code
         *                  //Sample control operate call-back
         *                  
         *                  enum eAppErrorCodes cbOperate(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptOperateID, struct sIEC101DataAttributeData *ptOperateValue, struct sIEC101CommandParameters *ptOperateParams, tErrorValue *ptErrorValue )     
         *                  {
         *                      enum eAppErrorCodes     i16ErrorCode            = IEC101_APP_ERROR_NONE;
         *
         *                      // Check Server received Operate command from client, Perform Operate in the hardware according to the typeID and IOA 
         *                      // Hardware Control Operate Operation;
         *                          
         *                      return i16ErrorCode;
        
         *                  }
         *  \endcode
         */ 
        typedef Integer16 (*IEC101ControlOperateCallback)(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptOperateID, struct sIEC101DataAttributeData *ptOperateValue,struct sIEC101CommandParameters *ptOperateParams, tErrorValue *ptErrorValue);
       
       /*! \brief          IEC101 Control Freeze Callback
        *  \ingroup        IEC101Call-back
        *   
        *  \param[in]      u16ObjectId     IEC101 object identifier
        *  \param[in]      ptFreezeID       Pointer to IEC 101 Data Attribute ID
        *  \param[in]      ptFreezeValue    Pointer to IEC 101 Data Attribute Data
        *  \param[in]      ptFreezeParams   Pointer to Freeze parameters       
        *  \param[out]     ptErrorValue    Pointer to Error Value (if any error occurs while creating the object)
        *
        *  \return         IEC101_APP_ERROR_NONE on success
        *  \return         otherwise error code
        *
        *  \code
        *                  //Sample Control Freeze Callback
        *                  enum eAppErrorCodes cbControlFreezeCallback(Unsigned16 u16ObjectId, enum eCounterFreezeFlags eCounterFreeze, struct sIEC101DataAttributeID *ptFreezeID,  struct sIEC101DataAttributeData *ptFreezeValue, struct sIEC101WriteParameters *ptFreezeCmdParams, tErrorValue *ptErrorValue )
        *                  {
        *                      enum eAppErrorCodes     i16ErrorCode    = IEC101_APP_ERROR_NONE;
        *
        *                      // get freeze counter interrogation groub & process it in hardware level
        *                          
        *                      return i16ErrorCode;
        *                  }
        *  \endcode
        */
        typedef Integer16 (*IEC101ControlFreezeCallback)(Unsigned16 u16ObjectId, enum eCounterFreezeFlags eCounterFreeze, struct sIEC101DataAttributeID *ptFreezeID, struct sIEC101DataAttributeData *ptFreezeValue, struct sIEC101WriteParameters *ptFreezeCmdParams, tErrorValue *ptErrorValue);

        /*! \brief          IEC101 Control Cancel call-back
         *  \ingroup        IEC101Call-back
         *   
         *  \param[in]      u16ObjectId     IEC101 object identifier
         *  \param[in]      enum eOperationFlag eOperation - select/ operate to cancel
         *  \param[in]      ptCancelID      Pointer to IEC 101 Data Attribute ID
         *  \param[in]      ptCancelValue   Pointer to IEC 101 Data Attribute Data
         *  \param[in]      ptCancelParams  Pointer to Cancel parameters       
         *  \param[out]     ptErrorValue    Pointer to Error Value (if any error occurs while creating the object)
         *
         *  \return         IEC101_APP_ERROR_NONE on success
         *  \return         otherwise error code
         *
         *  \code
         *                  //Sample control cancel call-back
         *                  
         *                  enum eAppErrorCodes cbCancel(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptCancelID, struct sIEC101DataAttributeData *ptCancelValue, struct sIEC101CommandParameters *ptCancelParams, tErrorValue *ptErrorValue )     
         *                  {
         *                      enum eAppErrorCodes     i16ErrorCode            = IEC101_APP_ERROR_NONE;
         *
         *                      // Check Server received cancel command from client, Perform cancel in the hardware according to the typeID and IOA 
         *                      // Hardware Control Cancel Operation;
         *                          
         *                      return i16ErrorCode;
        
         *                  }
         *  \endcode
         */ 
        typedef Integer16 (*IEC101ControlCancelCallback)(Unsigned16 u16ObjectId, enum eOperationFlag eOperation, struct sIEC101DataAttributeID *ptCancelID, struct sIEC101DataAttributeData *ptCancelValue,struct sIEC101CommandParameters *ptCancelParams, tErrorValue *ptErrorValue);

        /*! \brief          IEC101 Control Pulse End ActTerm Callback
         *  \ingroup        IEC101 Call-back
         *  
         *  \param[in]      u16ObjectId     IEC101 object identifier
         *  \param[in]      ptOperateID      Pointer to IEC 101 Data Attribute ID
         *  \param[in]      ptOperateValue   Pointer to IEC 101 Data Attribute Data
         *  \param[in]      ptOperateParams  Pointer to pulse end parameters       
         *  \param[out]     ptErrorValue     Pointer to Error Value (if any error occurs while creating the object)
         *
         *  \return         IEC101_APP_ERROR_NONE on success
         *  \return         otherwise error code
         *
         *  \code
         *                  //Sample control pulse end act term signal call-back
         *                  
         *                  enum eAppErrorCodes cbPulseEndActTermCallback(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptOperateID, struct sIEC101DataAttributeData *ptOperateValue, struct sIEC101CommandParameters *ptOperateParams, tErrorValue *ptErrorValue )     
         *                  {
         *                      enum eAppErrorCodes     i16ErrorCode            = IEC101_APP_ERROR_NONE;
         *
         *                      // After pulse end, send pulse end command termination signal to client 
         *                      // Hardware PulseEnd ActTerm Operation;
         *                          
         *                      return i16ErrorCode;
        
         *                  }
         *  \endcode
         */
        typedef Integer16 (*IEC101ControlPulseEndActTermCallback)(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptOperateID, struct sIEC101DataAttributeData *ptOperateValue,struct sIEC101CommandParameters *ptOperateParams, tErrorValue *ptErrorValue);

        /*! \brief  Parameter Act Command  CallBack 
         *  \ingroup        IEC101 Call-back
         * 
         *  \param[in]      u16ObjectId     IEC101 object identifier
         *  \param[in]      ptOperateID      Pointer to IEC 101 Data Attribute ID
         *  \param[in]      ptOperateValue   Pointer to IEC 101 Data Attribute Data
         *  \param[in]      ptParameterActParams  Pointer to Parameter Act Params     
         *  \param[out]     ptErrorValue     Pointer to Error Value (if any error occurs while creating the object)
         *
         *  \return         IEC101_APP_ERROR_NONE on success
         *  \return         otherwise error code
         *
         *  \code
         *                  //Sample Parameter Act call-back
         *                  
         *                  enum eAppErrorCodes cbParameterAct(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptOperateID, struct sIEC101DataAttributeData *ptOperateValue,struct sIEC101ParameterActParameters *ptParameterActParams, tErrorValue *ptErrorValue)     
         *                  {
         *                      enum eAppErrorCodes     i16ErrorCode            = IEC101_APP_ERROR_NONE;
         *                      Unsigned8               u8CommandVal        = 0;
         *
         *                      // parameter activation & process parameter value for particular typeid & ioa in hardware value like threshold value for analog input 
         *                          
         *                      return i16ErrorCode;
         *                  }
         *  \endcode
         */
        typedef Integer16 (*IEC101ParameterActCallback)(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptOperateID, struct sIEC101DataAttributeData *ptOperateValue,struct sIEC101ParameterActParameters *ptParameterActParams, tErrorValue *ptErrorValue);

        /*! \brief          IEC101 Debug call-back
         *  \ingroup        IEC101Call-back
         *   
         *  \param[in]      u16ObjectId     IEC101 object identifier
         *  \param[in]      ptDebugData     Pointer to debug data
         *  \param[out]     ptErrorValue    Pointer to Error Value (if any error occurs while creating the object)
         *
         *  \return         IEC101_APP_ERROR_NONE on success
         *  \return         otherwise error code
         *
         *  \code
         *                  //Sample debug call-back
         *                  
         *                  enum eAppErrorCodes cbDebug(Unsigned16 u16ObjectId, struct sIEC101DebugData *ptDebugData, tErrorValue *ptErrorValue )     
         *                  {
         *                      enum eAppErrorCodes     i16ErrorCode            = IEC101_APP_ERROR_NONE;
         *                      Unsigned16  nu16Count = 0;
         *                      // If Debug Option set is Rx DATA than print receive data
         *                      if((ptDebugData->u32DebugOptions & DEBUG_OPTION_RX) == DEBUG_OPTION_RX) 
         *                      {
         *                          printf("\r\n Rx :");
         *                          for(nu16Count = 0;  nu16Count < ptDebugData->u16RxCount; u16RxCount++)
         *                          {
         *                              printf(" %02X", ptDebugData->au8RxData[nu16Count];
         *                          }
         *                      }
         *
         *                      // If Debug Option set is Tx DATA than print transmission data
         *                      if((ptDebugData->u32DebugOptions & DEBUG_OPTION_TX) == DEBUG_OPTION_TX) 
         *                      {
         *                          printf("\r\n Tx :");
         *                          for(nu16Count = 0;  nu16Count < ptDebugData->u16TxCount; u16TxCount++)
         *                          {
         *                              printf(" %02X", ptDebugData->au8TxData[nu16Count];
         *                          }
         *                      }
         *                          
         *                      return i16ErrorCode;
         *                  }
         *  \endcode
         */
        typedef Integer16 (*IEC101DebugMessageCallback)(Unsigned16 u16ObjectId, struct sIEC101DebugData *ptDebugData, tErrorValue *ptErrorValue);

        /*! \brief          IEC101 Client connection status call-back
         *  \ingroup        IEC101Call-back
         * 
         *  \param[in]      u16ObjectId     IEC101 object identifier
         *  \param[out]      ptDataID      Pointer to IEC 101 Data Attribute ID
         *  \param[out]      peSat   Pointer to enum eStatus 
         *  \param[out]     ptErrorValue    Pointer to Error Value (if any error occurs while creating the object)
        
         *
         *  \return         IEC101_APP_ERROR_NONE on success
         *  \return         otherwise error code
         *
         *  \code
         *                  //Sample client status call-back
         *                  
         *                       Integer16 cbClientstatus(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *ptDataID, enum eStatus *peSat, tErrorValue *ptErrorValue)
         *                       {
         *                            Integer16 i16ErrorCode = EC_NONE;
         *                       
         *                            do
         *                            {
         *                                printf("\r\n server ca %u", ptDataID->u16CommonAddress);
         *                       
         *                                if(*peSat  ==  NOT_CONNECTED)
         *                                  {
         *                                    printf("\r\n not connected");
         *                                  }
         *                               else
         *                                  {
         *                                      printf("\r\n connected");
         *                                  }    
         *                     
         *                          }while(FALSE);    
         *                       
         *                            return i16ErrorCode;
         *                      }
         *  \endcode
         */
        typedef Integer16 (*IEC101ClientStatusCallback)(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID *psDAID, enum eStatus *peSat, tErrorValue *ptErrorValue);

        /*! \brief          IEC101 Directory call-back
         *  \ingroup        IEC101Call-back
         *
         *  \param[in]      u16ObjectId     IEC101 object identifier
         *  \param[in]      ptDirectoryID    Pointer to IEC 101 Data Attribute ID
         *  \param[in]      ptDirList        Pointer to IEC 101 sIEC101DirectoryList 
         *  \param[out]     ptErrorValue     Pointer to Error Value (if any error occurs while creating the object)
         *
         *  \return         IEC101_APP_ERROR_NONE on success
         *  \return         otherwise error code
         *
         *  \code
         *                  Integer16 cbDirectory(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID * ptDirectoryID,  struct sIEC101DirectoryList *ptDirList, tErrorValue *ptErrorValue)
         *                  {
         *                      Integer16 i16ErrorCode       =  EC_NONE;
         *                      Unsigned16          u16UptoFileCount =  ZERO;
         *  
         *                      printf("\n Directory CallBack Called");
         *                 
         *                      
         *                      printf("\r\n server port %u",psDirectoryID->u16SerialPortNumber);
         *                      printf("\r\n Data Link Address %u",psDirectoryID->u16DataLinkAddress);
         *                      printf("\r\n server ca %u",psDirectoryID->u16CommonAddress);
         *                      printf("\r\n Data Attribute ID is  %u IOA %u ",psDirectoryID->eTypeID, psDirectoryID->u32IOA);
         *                 
         *                      printf("\n No Of Files in the Directory :%u", psDirList->u16FileCount);
         *                  u16UptoFileCount = 0;
         *                      while(u16UptoFileCount < psDirList->u16FileCount)
         *                      {
         *                          printf("\n \n Object Index:%u   File Name:%u    SizeofFile:%lu", u16UptoFileCount, psDirList->psFileAttrib[u16UptoFileCount].u16FileName, psDirList->psFileAttrib[u16UptoFileCount].zFileSize);
         *                          printf("\n Time:%02d:%02d:%02d:%02d:%02d",  psDirList->psFileAttrib[u16UptoFileCount].sLastModifiedTime.u8Hour, psDirList->psFileAttrib[u16UptoFileCount].sLastModifiedTime.u8Minute, psDirList->psFileAttrib[u16UptoFileCount].sLastModifiedTime.u8Seconds, psDirList->psFileAttrib[u16UptoFileCount].sLastModifiedTime.u16MilliSeconds, psDirList->psFileAttrib[u16UptoFileCount].sLastModifiedTime.u16MicroSeconds);
         *                          printf(" Date:%02d:%02d:%04d:%02d\n", psDirList->psFileAttrib[u16UptoFileCount].sLastModifiedTime.u8Day, psDirList->psFileAttrib[u16UptoFileCount].sLastModifiedTime.u8Month,psDirList->psFileAttrib[u16UptoFileCount].sLastModifiedTime.u16Year,psDirList->psFileAttrib[u16UptoFileCount].sLastModifiedTime.u8DayoftheWeek);
         *                          u16UptoFileCount++;
         *                      }
         *                      return i16ErrorCode;
         *                  }            
         *  \endcode
         */
        typedef Integer16 (*IEC101DirectoryCallback)(Unsigned16 u16ObjectId, struct sIEC101DataAttributeID * ptDirectoryID,  struct sIEC101DirectoryList *ptDirList, tErrorValue *ptErrorValue);



        /*! \brief      Create Server/client parameters structure  */
        struct sIEC101Parameters
        {
            enum eApplicationFlag                   eAppFlag;                           /*!< Flag set to indicate the type of application */
            Unsigned32                              u32Options;                         /*!< Options flag, used to set client/server global options see #eApplicationOptionFlag for values */
            Unsigned16                              u16ObjectId;                        /*!< User idenfication will be retured in the callback for IEC101object identification*/
            IEC101ReadCallback                      ptReadCallback;                     /*!< Read callback function. If equal to NULL then callback is not used. */
            IEC101WriteCallback                     ptWriteCallback;                    /*!< Write callback function. If equal to NULL then callback is not used. */
            IEC101UpdateCallback                    ptUpdateCallback;                   /*!< Update callback function. If equal to NULL then callback is not used. */
            IEC101ControlSelectCallback             ptSelectCallback;                   /*!< Function called when a Select Command  is executed.  If equal to NULL then callback is not used*/
            IEC101ControlOperateCallback            ptOperateCallback;                  /*!< Function called when a Operate command is executed.  If equal to NULL then callback is not used */
            IEC101ControlCancelCallback             ptCancelCallback;                   /*!< Function called when a Cancel command is executed.  If equal to NULL then callback is not used */          
            IEC101ControlFreezeCallback             ptFreezeCallback;                   /*!< Function called when a Freeze Command is executed.  If equal to NULL then callback is not used*/
            IEC101ControlPulseEndActTermCallback    ptPulseEndActTermCallback;          /*!< Function called when a pulse  command time expires.  If equal to NULL then callback is not used */ 
            IEC101ParameterActCallback              ptParameterActCallback;             /*!< Function called when a Parameter act command is executed.  If equal to NULL then callback is not used */
            IEC101DebugMessageCallback              ptDebugCallback;                    /*!< Function called when debug options are set. If equal to NULL then callback is not used */
            IEC101ClientStatusCallback              ptClientStatusCallback;             /*!< Function called when client connection status changed */
            IEC101DirectoryCallback                 ptDirectoryCallback;                /*!< Directory callback function. List The Files in the Directory. */
            
        };


    #ifdef __cplusplus
        }
    #endif

/*
Cyclic data transmission:

Cyclic data transfer is initiated in a similar way as the background scan from the substation. 
It is independent of other commands from the central station. Cyclic data transfer continuously refreshes the process data of the central station. 
The process data are usually measured values that are recorded at regular intervals. 
Cyclic data transfer is often used for monitoring non-time-critical or relatively slowly changing process data (e.g. temperature sensor data).
Cyclic/periodic data are transferred to the central station with cause of transmission <1> periodic/cyclic.

Background scan:

The background scan is used for refreshing the process information sent from the substation to the central station as an additional safety contribution to the station interrogation and for spontaneous transfers.
Application objects with the same type IDs as for the station interrogation may be transferred continuously with low priority, and with <2> background scan as the cause of transmission.
The valid ASDU type IDs are listed in the compatibility list for the station (table type ID <-> cause of transmission). 
The background scan is initiated by the substation and is independent of the station interrogation commands.

*/
    

#endif
// End of File

