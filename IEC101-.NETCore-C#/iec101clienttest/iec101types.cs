/*****************************************************************************/
/*! \file        iec101types.cs
 *  \brief       iec101 protocol types win32 c# wrapper file
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
/*! \brief iec101 types c# class  */

public partial class iec101types
{


    
        /*! \brief  Max Size of Rx Message sent to callback  */
    public const int IEC101_MAX_RX_MESSAGE =       261;
        /*! \brief  Max Size of Tx Message sent to callback  */
    public const int IEC101_MAX_TX_MESSAGE =       261;

         
 

        /*! Flags for enum eDataLinkTransmission mode */
        public enum eDataLinkTransmission
        {
            UNBALANCED_MODE                     = 0, /*!< Data link Unbalanced mode */
            BALANCED_MODE                       = 1, /*!< Data link Balanced mode*/
        }

      

        /*! List of error code returned by API functions */
        public class eIEC101AppErrorCodes
        {
            public const int APP_ERROR_ERRORVALUE_IS_NULL                = -4501;       /*!< APP Error value is  null*/
            public const int APP_ERROR_CREATE_FAILED                     = -4502;       /*!< IEC101 create function failed */
            public const int APP_ERROR_FREE_FAILED                       = -4503;       /*!< IEC101 free function failed */
            public const int APP_ERROR_SERVER_INITIALIZE                 = -4504;       /*!< IEC101 server initialize function failed */
            public const int APP_ERROR_LOADCONFIG_FAILED                 = -4505;       /*!< IEC101 Load configuration function failed */
            public const int APP_ERROR_CHECKALLOCLOGICNODE               = -4506;       /*!< IEC101 Load- check alloc logical node function failed */
            public const int APP_ERROR_START_FAILED                      = -4507;       /*!< IEC101 Start function failed */
            public const int APP_ERROR_STOP_FAILED                       = -4508;       /*!< IEC101 Stop function failed */
            public const int APP_ERROR_SETDEBUGOPTIONS_FAILED            = -4509;       /*!< IEC101 set debug option failed */
            public const int APP_ERROR_PHYSICALLAYEROPEN_FAILED          = -4510;      /*!< IEC101 Physical Layer open operation failed  */
            public const int APP_ERROR_PHYSICALLAYERCLOSE_FAILED         = -4511;      /*!< IEC101 Physical Layer close operation failed */
            public const int APP_ERROR_SERIALCOMOPEN_FAILED              = -4512;      /*!< IEC101 Physical Layer com open failed    */
            public const int APP_ERROR_SERIALCOMCLOSE_FAILED             = -4513;      /*!< IEC101 Physical Layer com close failed   */
            public const int APP_ERROR_PHYSICALINITIALIZE_FAILED         = -4514;      /*!< IEC101 Physical Layer initialization failed  */
            public const int APP_ERROR_SERIALRECEIVE_FAILED              = -4515;      /*!< IEC101 Data Link Layer serial receive failed */
            public const int APP_ERROR_UPDATE_FAILED                     = -4516;      /*!< IEC101 Update function failed */
            public const int APP_ERROR_CREATESEMAPHORE_PHYSCIALLAYER     = -4517;      /*!< IEC101 physical layer semaphore creation is invalid  */
            public const int APP_ERROR_DELETESEMAPHORE_PHYSCIALLAYER     = -4518;      /*!< IEC101 physical layer semaphore deletion is invalid  */
            public const int APP_ERROR_RESERVESEMAPHORE_PHYSCIALLAYER    = -4519;      /*!< IEC101 physical layer semaphore reservation is invalid  */
            public const int APP_ERROR_TIMESTRUCT_INVALID                = -4520;      /*!< Time structure is invalid */
            public const int APP_ERROR_READ_FAILED                       = -4521;      /*!< IEC101 Read function failed */
            public const int APP_ERROR_WRITE_FAILED                      = -4522;      /*!< IEC101 Write function failed */
            public const int APP_ERROR_SELECT_FAILED                     = -4523;      /*!< IEC101 Select function failed */
            public const int APP_ERROR_OPERATE_FAILED                    = -4524;      /*!< IEC101 Operate function failed */
            public const int APP_ERROR_CANCEL_FAILED                     = -4525;      /*!< IEC101 Cancel function failed */
            public const int APP_ERROR_GETDATATYPEANDSIZE_FAILED         = -4526;      /*!< IEC101 Get Data type & size function failed */
            public const int APP_ERROR_LINKLAYER_INITIALIZE              = -4527;      /*!< Link layer initialize failed*/
            public const int APP_ERROR_LINKLAYER_DEINITIALIZE            = -4528;      /*!< link layer deinitialize failed*/
            public const int APP_ERROR_RESET_COMMAND_FAILED              = -4529;      /*!< link layer master reset failed*/
            public const int APP_ERROR_CLIENT_INITIALIZE                 = -4530;      /*!< IEC101 Client initialize function failed */
            public const int APP_ERROR_RESETOFREMOTELINK_FAILED          = -4531;      /*!< IEC101 Master reset of remote link failed*/
            public const int APP_ERROR_FRAME_DECODE_FAILED               = -4532;      /*!< IEC101 master frame decode failed*/
            public const int APP_ERROR_REQUESTSTATUSLINK_FAILED          = -4533;      /*!< IEC101 master request status link failed*/
            public const int APP_ERROR_GENTERAL_INTERROGATION_FAILED     = -4534;      /*!< IEC101 master general interrogation failed*/
            public const int APP_ERROR_CLOCKSYNC_FAILED                  = -4535;      /*!< IEC101 master clock sync failed*/
            public const int APP_ERROR_FRAME_ENCODE_FAILED               = -4536;      /*!< IEC101 master frame encode failed*/
            public const int APP_ERROR_SINGLECOMMAND_FAILED              = -4537;      /*!< IEC101 master single command failed*/
            public const int APP_ERROR_DOUBLECOMMAND_FAILED              = -4538;      /*!< IEC101 master decode failed*/
            public const int APP_ERROR_STEPCOMMAND_FAILED                = -4539;      /*!< IEC101 master step position failed*/
            public const int APP_ERROR_SETNORMALIZEDCOMMAND_FAILED       = -4540;      /*!< IEC101 set normalized command failed*/
            public const int APP_ERROR_SETSCALEDCOMMAND_FAILED           = -4541;      /*!< IEC101 set scaled command failed*/
            public const int APP_ERROR_SETPOINTFLOATCOMMAND_FAILED       = -4542;      /*!< IEC101 set point float command failed*/
            public const int APP_ERROR_SETPOINTBITSTRING_FAILED          = -4543;      /*!< IEC101 set point bit string failed*/
            public const int APP_ERROR_CALLBACK_FAILED                   = -4544;      /*!< callback error code for fail */
            public const int APP_ERROR_INVALID_POINTCOUNT                = -4545;      /*!<  Total Number of Points exceeding Point Count*/
            public const int APP_ERROR_TESTLINK_FAILED                   = -4546;      /*!< IEC101 Master Test link failed*/
            public const int APP_ERROR_CLIENTSTATUS_FAILED               = -4547;       /*!< IEC101 MASTER Client status failed*/
            public const int APP_ERROR_FILE_TRANSFER_FAILED              = -4548;        /*!< IEC101 File Transfer Failed*/
            public const int APP_ERROR_LIST_DIRECTORY_FAILED             = -4549;       /*!< IEC101 get Directory faied*/
            public const int APP_ERROR_GET_OBJECTSTATUS_FAILED           = -4550;       /*!< IEC101 get object status faied*/
            public const int APP_ERROR_PARAMETERACT_FAILED               = -4551;       /*!< IEC101 parameter act command faied*/



        }

        /*! List of error value returned by API functions */
        public class eIEC101AppErrorValues
        {
            public const int APP_ERRORVALUE_ERRORCODE_IS_NULL                =   -4501;          /*!< APP Error code is Null */
            public const int APP_ERRORVALUE_INVALID_INPUTPARAMETERS          =   -4502;          /*!< Supplied Parameters are invalid */
            public const int APP_ERRORVALUE_INVALID_APPFLAG                  =   -4503;          /*!< Invalid Application Flag , Client not supported by the API*/
            public const int APP_ERRORVALUE_UPDATECALLBACK_CLIENTONLY        =   -4504;          /*!< Update Callback used only for client*/
            public const int APP_ERRORVALUE_NO_MEMORY                        =   -4505;          /*!< Allocation of memory has failed */
            public const int APP_ERRORVALUE_INVALID_IEC101OBJECT             =   -4506;          /*!< Supplied IEC101Object is invalid */
            public const int APP_ERRORVALUE_IEC101FREE_CALLED_BEFORE_STOP    =   -4507;          /*!< APP state is running free function called before stop function*/
            public const int APP_ERRORVALUE_INVALID_STATE                    =   -4508;          /*!< IEC101OBJECT invalid state */
            public const int APP_ERRORVALUE_INVALID_DEBUG_OPTION             =   -4509;          /*!< invalid debug option */
            public const int APP_ERRORVALUE_TASK_CREATEFAILED                =   -4510;          /*!< Task creation failed */
            public const int APP_ERRORVALUE_TASK_STOPFAILED                  =   -4511;          /*!< Task stop failed */
            public const int APP_ERRORVALUE_INVALID_TYPEID                   =   -4512;          /*!< In the function eGroupID not valid, or later we will implement */
            public const int APP_ERRORVALUE_INVALIDUPDATE_COUNT              =   -4513;          /*!< Invalid update count */
            public const int APP_ERRORVALUE_UPDATEOBJECT_NOTFOUND            =   -4514;          /*!< IEC101Update function, for particular group id, index number not found, update failed */
            public const int APP_ERRORVALUE_INVALID_DATATYPE                 =   -4515;          /*!< IEC101Update function, for particular group id, psnewvalue invalid data type, update failed */
            public const int APP_ERRORVALUE_INVALID_DATASIZE                 =   -4516;          /*!< IEC101Update function, for particular group id, psnewvalue invalid data size, update failed */
            public const int APP_ERRORVALUE_INVALID_COMPORT_NUMBER           =   -4517;          /*!< IEC101 Load config parameters Communication Serial com port number is greater than 9*/
            public const int APP_ERRORVALUE_INVALID_BAUD_RATE                =   -4518;          /*!< IEC101 Load config parameters Communication SERIAL COM Invalid baud rate*/
            public const int APP_ERRORVALUE_INVALID_PARITY                   =   -4519;          /*!< IEC101 Load config parameters Communication SERIAL COM Invalid parity*/
            public const int APP_ERRORVALUE_INVALID_STOPBIT                  =   -4520;          /*!< IEC101 Load config parameters Communication SERIAL COM Invalid Stop bit*/
            public const int APP_ERRORVALUE_INVALID_WORDLENGTH               =   -4521;          /*!< IEC101 Load config parameters Communication SERIAL COM Invalid word length*/
            public const int APP_ERRORVALUE_INVALID_FLOWCONTROL              =   -4522;          /*!< IEC101 Load config parameters Communication SERIAL COM Invalid flow control */
            public const int APP_ERRORVALUE_INVALID_DEBUGOPTION              =   -4523;          /*!< IEC101 Load config parameters Invalid Debug option*/
            public const int APP_ERRORVALUE_INVALID_MASTER_LINKADDRESS       =   -4524;          /*!< IEC101 Load config parameters Invalid master address*/
            public const int APP_ERRORVALUE_INVALID_SLAVE_LINKADDRESS        =   -4525;          /*!< IEC101 Load config parameters invalid slave address*/
            public const int APP_ERRORVALUE_INVALID_SLAVEMASTER_ADDRESSSAME  =   -4526;          /*!< IEC101 Load config parameters master & slave address must not be equal*/
            public const int APP_ERRORVALUE_INVALID_DATETIME_STRUCT          =   -4527;          /*!< IEC101  invalid date time struct user input*/
            public const int APP_ERRORVALUE_INVALID_NUMBEROFOBJECTS          =   -4528;          /*!< IEC101  invalid no of objects user input*/
            public const int APP_ERRORVALUE_INVALID_IEC101OBJECTS            =   -4529;          /*!< IEC101 Load config parameters dnp3 objects , invalid u16NoofPoints must be 1-1000 & each group total no of objects 1 - 1000*/
            public const int APP_ERRORVALUE_READCALLBACK_CLIENTONLY          =   -4530;          /*!< Read Callback used only for client*/
            public const int APP_ERRORVALUE_CANCELCALLBACK_CLIENTONLY        =   -4531;          /*!< Cancel Callback used only for client*/
            public const int APP_ERRORVALUE_INVALID_IOA                      =   -4532;          /*!< IOA Value mismatch */
            public const int APP_ERRORVALUE_INVALID_CONTROLMODEL_SBOTIMEOUT  =   -4533;          /*!< invalid enum control model |u32SBOTimeOut , for typeids from M_SP_NA_1 to M_EP_TF_1 -> STATUS_ONLY & u32SBOTimeOut 0 , for type ids C_SC_NA_1 to C_BO_TA_1 should not STATUS_ONLY & u32SBOTimeOut 0*/
            public const int APP_ERRORVALUE_INVALID_CYCLICTRANSTIME          =   -4534;          /*!< INVALID cyclic transmission time  for measurands 0 or 60 - 3600 */
            public const int APP_ERRORVALUE_INVALID_BUFFERSIZE               =   -4535;          /*!< event buffer size minimum 100*/
            public const int APP_ERRORVALUE_INVALID_CLASS                    =   -4536;          /*!< typeid c_XX_XX type id must be IEC_NOCLASS*/
            public const int APP_ERRORVALUE_INVLAID_EVENTBUF_OVERFLOWPER     =   -4537;          /*!< Load config parameters invalid, Event buffer OVER FLOW percentage < 25|| >100*/
            public const int APP_ERRORVALUE_INVALID_MAXAPDU_SIZE             =   -4538;          /*!< MAX_APDU Size should be minimum 42 MAX 255*/
            public const int APP_ERRORVALUE_INVALID_SHORTPULSETIME           =   -4539;          /*!< Pulse time should not be zero */
            public const int APP_ERRORVALUE_INVALID_LONGPULSETIME            =   -4540;          /*!< Pulse time should not be zero*/
            public const int APP_ERRORVALUE_INVALID_NOOFCLIENT               =   -4541;          /*!< u8 No of Client should not be zero */
            public const int APP_ERRORVALUE_INVALID_CLIENTOBJECTS            =   -4542;          /*!< psClientObjects should not be null */
            public const int APP_ERRORVALUE_INVALID_LINKADDRESS_SIZE         =   -4543;          /*!< invalid link address size*/
            public const int APP_ERRORVALUE_INVALID_COT_SIZE                 =   -4544;          /*!< invalid cause of transmission size*/
            public const int APP_ERRORVALUE_INVALID_IOA_SIZE                 =   -4545;          /*!< invalid ioa size*/
            public const int APP_ERRORVALUE_INVALID_CA_SIZE                  =   -4546;          /*!< invalid common */
            public const int APP_ERRORVALUE_INVALID_EPOS_ACK                 =   -4547;          /*!< invalid positive ack*/
            public const int APP_ERRORVALUE_INVALID_ENEG_ACK                 =   -4548;          /*!< invalid negative ack*/
            public const int APP_ERRORVALUE_INVALID_LINKADDRESS              =   -4549;          /*!< Broadcast address 255, or 65535 */
            public const int APP_ERRORVALUE_INVALID_IOA_ADDRESS              =   -4550;          /*!< Invalid ioa address may be 0 */
            public const int APP_ERRORVALUE_NACKLINK_BUSY                    =   -4551;          /*!< IEC101 Master link busy*/
            public const int APP_ERRORVALUE_NACKDATA_NOTAVILABLE             =   -4552;          /*!< IEC101 Master poll data not available*/
            public const int APP_ERRORVALUE_INVALID_LINKADDRESS_MISMATCH     =   -4553;          /*!< Link address must be unique */
            public const int APP_ERRORVALUE_SLAVE_NOT_CONNECTED              =   -4554;          /*!< IEC101 slave device not connected*/
            public const int APP_ERRORVALUE_INVALID_OPERATION_FLAG           =   -4555;          /*!< IEC101 cancel function invalid operation flag*/
            public const int APP_ERRORVALUE_UNKNOWN_TYPEID                   =   -4556;          /*!< IEC101 command operation slave responds unknown typeid*/
            public const int APP_ERRORVALUE_UNKNOWN_COT                      =   -4557;          /*!< IEC101 command operation slave responds unknown cause of transmission*/
            public const int APP_ERRORVALUE_UNKNOWN_CASDU                    =   -4558;          /*!< IEC101 command operation slave responds unknown common asdu*/
            public const int APP_ERRORVALUE_UNKNOWN_IOA                      =   -4559;          /*!< IEC101 command operation slave responds unknown ioa*/
            public const int APP_ERRORVALUE_INVALID_QUALIFIER                =   -4560;          /*!< IEC101 command operation invalid qualifier/KPA*/
            public const int APP_ERRORVALUE_INVALID_DATAPOINTER              =   -4561;          /*!< Void pvdata is invalid */
            public const int APP_ERRORVALUE_CALLBACK_FAILED                  =   -4562;          /*!< callback error value for fail */
            public const int APP_ERRORVALUE_INVALID_POINTCOUNT               =   -4563;          /*!< Total Number of Points exceeding Point Count*/
            public const int APP_ERRORVALUE_INVALID_COUNT_SERIALCONNECTIONS  =   -4564;          /*!<invalid count Serial connections*/
            public const int APP_ERRORVALUE_INVALID_DATALINK_MODE            =   -4565;          /*!<invalid Datalink mode*/
            public const int APP_ERRORVALUE_COMMAND_TIMEOUT                  =   -4566;          /*!<After command timeout, client did not receive valid response from server */
            public const int APP_ERRORVALUE_INVALID_RANGE                    =   -4567;          /*!< Invalid range 0- 1000 */
            public const int APP_ERRORVALUE_INVALID_COT                      =   -4568;         /*!<  For commands the COT must be NOTUSED */
            public const int APP_ERRORVALUE_INVALID_DATALINKADDRESS          =   -4569;          /*!<  Datalink address mismatch */
            public const int APP_ERRORVALUE_INVALID_KPA                      =   -4570;          /*!<  Invalid Kind of Parameter , For typeids,P_ME_NA_1, P_ME_NB_1, P_ME_NC_1 - Kind of parameter , refer enum eKPA for other typeids - PARAMETER_NONE */
            public const int APP_ERRORVALUE_INVALID_QRP                      =   -4571;          /*!< Invalid quality of reset process */
            public const int APP_ERRORVALUE_INVALID_COMMONADDRESS            =   -4572;          /*!< Invalid common address / station address */ 
            public const int APP_ERRORVALUE_FILETRANSFER_TIMEOUT             =   -4573;          /*!< file transfer timeout, no response from server */
            public const int APP_ERRORVALUE_FILE_NOT_READY                   =   -4574;          /*!< file not ready */
            public const int APP_ERRORVALUE_SECTION_NOT_READY                =   -4575;          /*!< Section not ready */  
            public const int APP_ERRORVALUE_FILE_OPEN_FAILED                 =   -4576;          /*!< File Open Failed */ 
            public const int APP_ERRORVALUE_FILE_CLOSE_FAILED                =   -4577;          /*!< File Close Failed */
            public const int APP_ERRORVALUE_FILE_WRITE_FAILED                =   -4578;         /*!< File Write Failed */
            public const int APP_ERRORVALUE_FILETRANSFER_INTERUPTTED         =   -4579;          /*!< File Transfer Interrupted */
            public const int APP_ERRORVALUE_SECTIONTRANSFER_INTERUPTTED      =   -4580;          /*!< Section Transfer Interrupted */
            public const int APP_ERRORVALUE_FILE_CHECKSUM_FAILED             =   -4581;          /*!< File Checksum Failed*/
            public const int APP_ERRORVALUE_SECTION_CHECKSUM_FAILED          =   -4582;          /*!< Section Checksum Failed*/
            public const int APP_ERRORVALUE_FILE_NAME_UNEXPECTED             =   -4583;          /*!< File Name Unexpected*/
            public const int APP_ERRORVALUE_SECTION_NAME_UNEXPECTED          =   -4584;          /*!< Section Name Unexpected*/
            public const int APP_ERRORVALUE_DIRECTORYCALLBACK_CLIENTONLY     =   -4585;          /*!< Directory Callback used only for client*/
            public const int APP_ERRORVALUE_INVALID_BACKSCANTIME             =   -4586;          /*!< INVALID back ground scan time, 0 or 60 - 3600*/
            public const int APP_ERRORVALUE_INVALID_FILETRANSFER_PARAMETER   =   -4587;         /*!< Server loadconfig, file transfer enabled, but the dir path and number of files not valid*/      
            public const int APP_ERRORVALUE_FILETRANSFER_DISABLED            =   -4588;         /*!< file transfer disabled in the settings*/
            public const int APP_ERRORVALUE_INVALID_INTIAL_DATABASE_QUALITYFLAG = -4589;            /*!<  invalid settings initialquality flag*/
            public const int APP_ERRORVALUE_DEMO_EXPIRED                        = -4590;     /*!< Demo software expired contact support@freyrscada.com*/
            public const int APP_ERRORVALUE_DEMO_INVALID_POINTCOUNT             = -4591;	  /*!< Demo software - Total Number of Points exceeded, maximum 100 points*/
            public const int APP_ERRORVALUE_SERVER_DISABLED						= -4592;		/*!< Server functionality disabled in the api, please contact support@freyrscada.com */
            public const int APP_ERRORVALUE_CLIENT_DISABLED                     = -4593;		/*!< Client functionality disabled in the api, please contact support@freyrscada.com*/

        }

        
        /*!   Flags for eDataLinkAddressSize - Data link address size*/
        public enum eDataLinkAddressSize
        {
            DL_NOT_PRESENT = 0,        /*!< in the frame link address present or not */
            DL_ONE_BYTE    = 1,        /*!< */
            DL_TWO_BYTE    = 2,        /*!< */
        }

        /*!   Flags for eInformationObjectAddressSize - Information object address size*/
        public enum eInformationObjectAddressSize
        {
            IOA_ONE_BYTE        = 1,        /*!< 1 Octet Size of Information object address*/
            IOA_TWO_BYTE        = 2,        /*!< 2 Octet Size of Information object address*/
            IOA_THREE_BYTE      = 3,        /*!< 3 Octet Size of Information object address*/
        }

        /*!  Flags for eCommonAddressSize - Common Address size*/
        public enum eCommonAddressSize
        {
            CA_ONE_BYTE     = 1,        /*!< 1 Octet Size of Common Address */
            CA_TWO_BYTE     = 2,        /*!< 2 Octet Size of Common Address */
        }

       
        /*!  Flags for ePositiveACK*/
        public enum ePositiveACK
        {
            SINGLE_CHAR_ACK_E5      =   0xE5,   /*!< Positive ACK e5*/
            FIXED_FRAME_ACK         =   0x10,   /*!< Positive ACK - fixed frame*/
        }

        /*!  Flags for eNegativeACK */
        public enum eNegativeACK
        {
            SINGLE_CHAR_NACK_A2     =   0xA2,   /*!< Negative ACK - a2*/
            FIXED_FRAME_NACK        =   0x10,   /*!< Negative ACK - fixed frame*/
        }

         /*! \typedef enum eIECClass
            *  \brief IEC Class
        */
        public enum eIECClass
        {
            IEC_NO_CLASS        = 0,        /*!< IEC_NO_CLASS for Output point Data, if assigned for input points event will not generate. */
            IEC_CLASS1          = 1,        /*!< Class 1 for high priority data */
            IEC_CLASS2          = 2,        /*!< Class 2 for low priority data  */
        }

        
        /*! \brief  IEC101 Object Structure */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101Object
        {
            public iec60870common.eIEC870TypeID                    eTypeID;               /*!< Type Identifcation see  */
            public uint                             u32IOA;                /*!< Informatiion Object Address */
            public ushort                           u16Range;              /*!< Range */
            public iec60870common.eIEC870COTCause                  eIntroCOT;             /*!< Interrogation group */
            public iec60870common.eControlModelConfig              eControlModel;         /*!< Control Model specified in eControlModelFlags */
            public uint                             u32SBOTimeOut;         /*!< Select Before Operate Timeout  in milliseconds*/
            public eIECClass                        eClass;                 /*!< Class of data */
            public iec60870common.eKindofParameter                 eKPA;                  /*!< For typeids,P_ME_NA_1, P_ME_NB_1, P_ME_NC_1 - Kind of parameter , refer enum eKPA for other typeids - PARAMETER_NONE*/
            public ushort                           u16CommonAddress;       /*!< Common Address , 0 - not used, 1-65534 station address, 65535 = global address (only master can use this)*/
            public uint                             u32CyclicTransTime;         /*!< Periodic or Cyclic Transmissin time in seconds. If 0 do not transmit Periodically (only applicable to measured values M_ME_NA_1, M_ME_NB_1, M_ME_NC_1, M_ME_ND_1) MINIMUM 60 Seconds, max 3600 seconds (1 hour)*/
            public uint                             u32BackgroundScanPeriod;        /*!< in seconds, if 0 the background scan will not be performed, MINIMUM 60 Seconds, max 3600 seconds (1 hour), all monitoring iinformation except Integrated totals will be transmitteed . the reporting typeid without timestamp*/
            [System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = tgtcommon.APP_OBJNAMESIZE)]
            public string                        ai8Name;   /*!< Name */
            
        }

        /*! \brief  IEC101 Debug Parameters */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101DebugParameters
        {
            public uint                      u32DebugOptions;           /*!< Debug Option see eDebugOptionsFlag */
        }

        /*! \brief      Server protocol settings parameters structure  */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101ServerProtocolSettings
        {
            public eDataLinkTransmission          eDataLink;                          /*!< Data link transmission - Unbalanced mode - 0, Balanced mode -1*/
            public eDataLinkAddressSize           elinkAddrSize;                      /*!< Data link address size*/
            public ushort                          u16DataLinkAddress;                 /*!< Data link address*/
            public iec60870common.eCauseofTransmissionSize       eCOTsize;                           /*!< Cause of transmission size*/
            public eInformationObjectAddressSize  eIOAsize;                           /*!< Information object address size*/
            public eCommonAddressSize             eCASize ;                           /*!< Common Address Size , 0-one octet, 1-two octet*/            
            public ePositiveACK                   ePosACK;                            /*!< positive ack*/
            public eNegativeACK                   eNegACK;                            /*!< Negative ack*/
            public ushort                         u16Class1EventBufferSize;           /*!< class 1 Event buffer size minimum 100, max u16value */
            public ushort                          u16Class2EventBufferSize;           /*!< class 2 Event buffer size minimum 100, max u16value */
            public byte                           u8Class1BufferOverFlowPercentage;   /*!< Class 1 buffer overflow percentage 50 to 95*/
            public byte                           u8Class2BufferOverFlowPercentage;   /*!< Class 2 buffer overflow percentage 50 to 95*/
            public byte                           u8MaxAPDUSize;                      /*!< Monitoring Information - Maximum APDU Size, Maximum Length of APDU 42 to 255 (if max value set to 255, the tx length will be 261)*/
            public uint                             u32ClockSyncPeriod;                 /*!< Clock Synchronisation period in milliseconds. If 0 than Clock Synchronisation command is not expected from Master */


            /* Controlled stations expect the reception of clock synchronization messages 
            within agreed time intervals. When the synchronization command does not arrive within this 
            time interval, the controlled station sets all time-tagged information objects with a mark 
            that the time tag may be inaccurate (invalid).*/

            public ushort                          u16ShortPulseTime;                           /*!< Short Pulse Time in milliseconds */
            public ushort                          u16LongPulseTime;                            /*!< Long Pulse Time in milliseconds */
            public byte                             bGenerateACTTERMrespond;                        /*!< if Yes , Generate ACTTERM  responses for operate commands*/    
            public uint                             u32BalancedModeTestConnectionSignalInterval;    /*!< in seconds, in Balanced mode , nothing received, after this interval, server will send the test link function to master 60 seconds to 3600 seconds*/
            public byte                             bEnableDoubleTransmission;                      /*!< enable double transmission*/
            public byte                             u8TotalNumberofStations;                        /*!< Total number of stations / common address 1-5 */         
            public byte                             bEnableFileTransfer;                            /*!< enable / disable File Transfer */
            public ushort                           u16MaxFilesInDirectory;                         /*!< Maximum No of Files in Directory(default 25) */
            public byte                             bTransmitSpontMeasuredValue;                    /*!< transmit M_ME measured values in spontanous message */ 
            public byte                             bTranmitInterrogationMeasuredValue;             /*!< transmit M_ME measured values in General interrogation */
            public byte                             bTransmitBackScanMeasuredValue;                 /*!< transmit M_ME measured values in background message */
            public byte                             u8InitialdatabaseQualityFlag;                   /*!< 0- good/valid, 1 BIT- iv, 2 BIT-nt,  MAX VALUE -3   */
            public byte                             bUpdateCheckTimestamp;                          /*!< if it true ,the timestamp change also generate event  during the iec101update */
            public byte							bSequencebitSet;						  		/*!< If it true, Server builds iec frame with sequence for monitoring information without time stamp */
			
			[System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = iec60870common.MAX_DIRECTORY_PATH)]
            public string                           ai8FileTransferDirPath; /*!< File Transfer Directory Path */
            [System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = iec60870common.MAX_CA, ArraySubType = System.Runtime.InteropServices.UnmanagedType.U2)]
            public ushort[]                         au16CommonAddress;                      /*!< in a single physical device we can run many stations,station address- Common Address , 0 - not used, 1-65534 , 65535 = global address (only master can use this)*/
               
        }

        /*! \brief      Client protocol settings parameters structure  */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101ClientProtocolSettings
        {
            public eDataLinkAddressSize           elinkAddrSize;                      /*!< Data link address size*/
            public ushort                          u16DataLinkAddress;                 /*!< Data link address*/
            public iec60870common.eCauseofTransmissionSize       eCOTsize;                           /*!< Cause of transmission size*/
            public eInformationObjectAddressSize  eIOAsize;                           /*!< Information object address size*/
            public eCommonAddressSize             eCASize;                            /*!< Common Address Size , 0-one octet, 1-two octet*/
            public byte                             u8TotalNumberofStations;                        /*!< Total number of stations / common address 1-5 */  
            public byte                           u8OriginatorAddress;                 /*!< if cot size is 2 octet, we need to set originator address, default 0 */
            public uint                          u32LinkLayerTimeout;                /*!< in ms, minimum 1000  */
            public uint                          u32PollInterval;                    /*!< in msec  min 100 */
            public uint                          u32GeneralInterrogationInterval;    /*!< in sec if 0 , gi will not send in particular interval*/
            public uint                          u32Group1InterrogationInterval;    /*!< in sec if 0 , group 1 interrogation will not send in particular interval*/
            public uint                          u32Group2InterrogationInterval;    /*!< in sec if 0 , group 2 interrogation will not send in particular interval*/
            public uint                          u32Group3InterrogationInterval;    /*!< in sec if 0 , group 3 interrogation will not send in particular interval*/
            public uint                          u32Group4InterrogationInterval;    /*!< in sec if 0 , group 4 interrogation will not send in particular interval*/
            public uint                          u32Group5InterrogationInterval;    /*!< in sec if 0 , group 5 interrogation will not send in particular interval*/
            public uint                          u32Group6InterrogationInterval;    /*!< in sec if 0 , group 6 interrogation will not send in particular interval*/
            public uint                          u32Group7InterrogationInterval;    /*!< in sec if 0 , group 7 interrogation will not send in particular interval*/
            public uint                          u32Group8InterrogationInterval;    /*!< in sec if 0 , group 8 interrogation will not send in particular interval*/
            public uint                          u32Group9InterrogationInterval;    /*!< in sec if 0 , group 9 interrogation will not send in particular interval*/
            public uint                          u32Group10InterrogationInterval;    /*!< in sec if 0 , group 10 interrogation will not send in particular interval*/
            public uint                          u32Group11InterrogationInterval;    /*!< in sec if 0 , group 11 interrogation will not send in particular interval*/
            public uint                          u32Group12InterrogationInterval;    /*!< in sec if 0 , group 12 interrogation will not send in particular interval*/
            public uint                          u32Group13InterrogationInterval;    /*!< in sec if 0 , group 13 interrogation will not send in particular interval*/
            public uint                          u32Group14InterrogationInterval;    /*!< in sec if 0 , group 14 interrogation will not send in particular interval*/
            public uint                          u32Group15InterrogationInterval;    /*!< in sec if 0 , group 15 interrogation will not send in particular interval*/
            public uint                          u32Group16InterrogationInterval;    /*!< in sec if 0 , group 16 interrogation will not send in particular interval*/
            public uint                          u32CounterInterrogationInterval;    /*!< in sec if 0 , ci will not send in particular interval*/
            public uint                          u32Group1CounterInterrogationInterval;    /*!< in sec if 0 , group 1 counter interrogation will not send in particular interval*/
            public uint                          u32Group2CounterInterrogationInterval;    /*!< in sec if 0 , group 2 counter interrogation will not send in particular interval*/
            public uint                          u32Group3CounterInterrogationInterval;    /*!< in sec if 0 , group 3 counter interrogation will not send in particular interval*/
            public uint                          u32Group4CounterInterrogationInterval;    /*!< in sec if 0 , group 4 counter interrogation will not send in particular interval*/            
            public uint                          u32ClockSyncInterval;               /*!< in sec if 0 , clock sync, will not send in particular interval */
            public uint                          u32CommandTimeout;                  /*!< in ms, minimum 1000  */
            public uint                          u32FileTransferTimeout;             /*!< in ms, minimum 3000  */
            public byte                             bEnableFileTransfer;             /*!< enable / disable File Transfer */
            public byte                             bCommandResponseActtermUsed;        /*!< server side is ACTTERM Used for command termination */
            public uint                             u32BalancedModeTestConnectionSignalInterval; /*!< in seconds, in Balanced mode , nothing received, after this interval, client will send the test link function to server */
            public byte                             bUpdateCallbackCheckTimestamp; /*!< if it true ,the timestamp change also create the updatecallback */
            [System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = iec60870common.MAX_DIRECTORY_PATH)]
            public string                           ai8FileTransferDirPath; /*!< File Transfer Directory Path */
            [System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = iec60870common.MAX_CA, ArraySubType = System.Runtime.InteropServices.UnmanagedType.U2)]
            public ushort[]                         au16CommonAddress;                      /*!< in a single physical device we can run many stations,station address- Common Address , 0 - not used, 1-65534 , 65535 = global address (only master can use this)*/
           
        }

        /*! \brief      Server  settings parameters structure  */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101ServerSettings
        {
            public byte                                 u8NumberofSerialPortConnections;                        /*!<  Total number of serial port commnication for master to connect */
            public sIEC101ServerProtocolSettings              sServerProtSet;         /*!<  server protocol settings*/
            public sIEC101DebugParameters               sDebug;                             /*!< Debug options settings on loading the configuarion See struct sIEC101DebugParameters */
            public byte                                 benabaleUTCtime;                            /*!< enable utc time/ local time*/  
            public ushort                               u16NoofObject;                      /*!< Total number of IEC101 Objects */
            public System.IntPtr                        psIEC101Objects;                  /*!< Pointer to strcuture IEC 101 Objects - according u16NoofObject*/
            public System.IntPtr                        psSerialSet;             /*!< Serial Communication Port Settings according to u8NumberofSerialPortConnections*/
            
        }

        /*! \brief      Client object structure  */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101ClientObject
        {
            public tgtserialtypes.sSerialCommunicationSettings         sSerialSet;             /*!< Serial Communication Port Settings */
            public sIEC101ClientProtocolSettings              sClientProtSet;         /*!< Protocol settings*/
            public ushort                               u16NoofObject;                      /*!< Total number of IEC101 Objects */
            public System.IntPtr                        psIEC101Objects;                  /*!< Pointer to strcuture IEC 101 Objects */
        }

        /*! \brief      Client settings parameters structure  */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101ClientSettings
        {
            public byte bAutoGenIEC101DataObjects;			/*!< if it true ,the IEC101 Objects created automaticallay, use u16NoofObject = 0, psIEC104Objects = NULL*/
			public ushort						u16UpdateBuffersize;				/*!< if bAutoGenIEC101DataObjects true, update callback buffersize, approx 3 * max count of monitoring points in the server */		
			public eDataLinkTransmission        eLink;                              /*!< Data link transmission - Unbalanced mode - 0, Balanced mode -1*/
            public sIEC101DebugParameters       sDebug;                             /*!< Debug options settings on loading the configuarion See struct sIEC101DebugParameters */
            public byte                         benabaleUTCtime;                            /*!< enable utc time/ local time*/  
            public byte                         u8NoofClient;                                           /*!< Total number of client Objects */
            public System.IntPtr                psClientObjects;                  /*!< Pointer to strcuture IEC 101 Objects accroding to u8NoofClient */
            
        }

        /*! \brief  IEC101 Configuration parameters  */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101ConfigurationParameters
        {
            public sIEC101ServerSettings          sServerSet;                         /*!< IEC101 Server settings*/
            public sIEC101ClientSettings          sClientSet;                         /*!< IEC101 Client settings*/
        }


        /*! \brief      This structure hold the identification of a IEC101 Data Attribute */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101DataAttributeID
        {
            public ushort           u16SerialPortNumber;     /*!< Serial COM port number*/
            public ushort           u16DataLinkAddress;     /*!< Data Link Address */
            public uint             u32IOA;                 /*!< Information Object Address */
            public iec60870common.eIEC870TypeID    eTypeID;                /*!< Type Identification */
            public ushort           u16CommonAddress; /*!< Orginator Address /Common Address , 0 - not used, 1-65534 station address, 65535 = global address (only master can use this)*/
            public System.IntPtr    pvUserData;            /*!< Application specific User Data */
        }


        /*! \brief      A Data object structure. Used to exchange data objects between IEC101 object and application. */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101DataAttributeData
        {
            public tgtcommon.sTargetTimeStamp        sTimeStamp;         /*!< TimeStamp */
            public ushort               tQuality;           /*!< Quality of Data see eIEC101QualityFlags */
            public    tgtcommon.eDataTypes        eDataType;          /*!< Data Type */
            public    tgttypes.eDataSizes        eDataSize;          /*!< Data Size */
            public byte                 bTimeInvalid;       /*!< time Invalid */
            public tgtcommon.eTimeQualityFlags eTimeQuality; /*!< time quality */
            public ushort               u16ElapsedTime;      /*!< Elapsed time(M_EP_TA_1, M_EP_TD_1) /Relay duration time(M_EP_TB_1, M_EP_TE_1) /Relay Operating time (M_EP_TC_1, M_EP_TF_1)  In Milliseconds */
            public byte bTRANSIENT; 								/*!<transient state indication result value step position information*/
            public byte u8Sequence;								/*!< m_it - Binary counter reading - Sequence notation*/
			public System.IntPtr        pvData;            /*!< Pointer to Data */
            
        }

        /*! \brief      Parameters provided by read callback   */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101ReadParameters
        {
            public byte   u8OriginatorAddress;     /*!< client orginator address */
            public byte   u8Dummy;                /*!< Dummy only for future expansion purpose */
        }

        /*! \brief      Parameters provided by write callback   */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101WriteParameters
        {
            public byte   u8OriginatorAddress;     /*!< client orginator address */
            public iec60870common.eIEC870COTCause  eCause;           /*!< cause of transmission */
            public byte   u8Dummy;                /*!< Dummy only for future expansion purpose */
        }

        /*! \brief      Parameters provided by update callback   */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101UpdateParameters
        {
            public iec60870common.eIEC870COTCause  eCause;           /*!< cause of transmission */
            public iec60870common.eKindofParameter   eKPA;                      /*!< For typeids,P_ME_NA_1, P_ME_NB_1, P_ME_NC_1 - Kind of parameter , refer enum eKPA*/
        }

        /*! \brief      Parameters provided by Command callback   */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101CommandParameters
        {
            public byte           u8OriginatorAddress;         /*!<  client orginator address */
            public iec60870common.eCommandQOCQU  eQOCQU;                     /*!<Qualifier of Commad */
            public uint          u32PulseDuration;           /*!< Pulse Duration Based on the Command Qualifer */
        }
        
        /*! \brief      Parameters provided by parameter act term callback   */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101ParameterActParameters
        {
             public byte            u8OriginatorAddress;         /*!<  client orginator address */
             public byte              u8QPA;                  /*!< Qualifier of parameter activation/kind of parameter , for typeid P_AC_NA_1, please refer 7.2.6.25, for typeid 110,111,112 please refer KPA 7.2.6.24*/
        }


        /*! \brief  IEC101 Debug Callback Data */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101DebugData
        {
            public uint                         u32DebugOptions;                            /*!< Debug Option see eDebugOptionsFlag */
            public short                        i16ErrorCode;                                 /*!< error code if any */
            public short                        tErrorvalue;                                /*!< error value if any */
            public ushort                       u16ComportNumber;                            /*!< serial com port number for transmit & receive */
            public ushort                       u16RxCount;                                 /*!< Received data count*/
            public ushort                       u16TxCount;                                 /*!< Transmitted data count */
            public tgtcommon.sTargetTimeStamp                sTimeStamp;                                 /*!< TimeStamp */
            [System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = tgtdefines.MAX_ERROR_MESSAGE)]
        public string                           au8ErrorMessage;         /*!< error message */
        [System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.ByValTStr, SizeConst = tgtdefines.MAX_WARNING_MESSAGE)]
        public string                           au8WarningMessage;     /*!< warning message */
        [System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = IEC101_MAX_RX_MESSAGE)]
        public byte[]                           au8RxData;                 /*!< Received data  */
        [System.Runtime.InteropServices.MarshalAs(System.Runtime.InteropServices.UnmanagedType.ByValArray, SizeConst = IEC101_MAX_TX_MESSAGE)]
        public byte[]                           au8TxData;                  /*!< Transmitted data  */
        
        }

        /*! \brief IEC101 File Attributes*/
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101FileAttributes
        {
            public byte                     bFileDirectory;                  /*!< File /Directory File-1,Directory 0 */                      
            public ushort                   u16FileName;                     /*!< File Name */
            public uint                     zFileSize;                       /*!< File size*/
            public byte                     bLastFileOfDirectory;            /*!< Last File Of Directory*/
            public tgtcommon.sTargetTimeStamp            sLastModifiedTime;               /*!< Last Modified Time*/        
        }

        /*! \brief IEC101 Directory List*/
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101DirectoryList
        {
            public ushort                       u16FileCount;                         /*!< File Count read from the Directory */
            public System.IntPtr                psFileAttrib;                        /*!< Pointer to File Attributes */
        }


            /*! \brief error code more description */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101ErrorCode
        {
             public short iErrorCode;       /*!< errorcode */
             public System.IntPtr shortDes;       /*!< string - error code short description*/
             public System.IntPtr LongDes;        /*!< string - error code brief description*/

        }

        
        /*! \brief error value more description */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101ErrorValue
        {
             public short iErrorValue;      /*!< errorvalue */
             public System.IntPtr shortDes;       /*!< string error code short description*/
             public System.IntPtr LongDes;        /*!< string - error code brief description*/

        }





        //For callback , from slave side configuration can give errorcode = EC_NONE  means command successful
        // else command fail


        /*  errror codes for callback
            EC_NONE                    = 0,              // callback success
            APP_ERROR_CALLBACK_FAILED         = -44,            // callback error code for fail
        */

        /* error values for callback
           EV_NONE                              = 0,                      // Everything was ok
           APP_ERRORVALUE_CALLBACK_FAILED                   =   -1062,   // callback error value for fail
        */


        /*! \brief  Command Read CallBack */
        [System.Runtime.InteropServices.UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate short IEC101ReadCallback(ushort u16ObjectId, ref sIEC101DataAttributeID ptReadID, ref sIEC101DataAttributeData ptReadValue, ref sIEC101ReadParameters ptReadParams, ref short ptErrorValue);

        /*! \brief  Command Write CallBack */
        [System.Runtime.InteropServices.UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate short IEC101WriteCallback(ushort u16ObjectId, ref sIEC101DataAttributeID ptWriteID, ref sIEC101DataAttributeData ptWriteValue, ref sIEC101WriteParameters ptWriteParams, ref short ptErrorValue);

        /*! \brief  Command Update CallBack */
        [System.Runtime.InteropServices.UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate short IEC101UpdateCallback(ushort u16ObjectId, ref sIEC101DataAttributeID ptUpdateID, ref sIEC101DataAttributeData ptUpdateValue, ref sIEC101UpdateParameters ptUpdateParams, ref short ptErrorValue);

        /*! \brief  Command Select CallBack */
        [System.Runtime.InteropServices.UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate short IEC101ControlSelectCallback(ushort u16ObjectId, ref sIEC101DataAttributeID ptSelectID, ref sIEC101DataAttributeData ptSelectValue, ref sIEC101CommandParameters ptSelectParams, ref short ptErrorValue);

        /*! \brief  Command Operate CallBack */
        [System.Runtime.InteropServices.UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate short IEC101ControlOperateCallback(ushort u16ObjectId, ref sIEC101DataAttributeID ptOperateID, ref sIEC101DataAttributeData ptOperateValue, ref sIEC101CommandParameters ptOperateParams, ref short ptErrorValue);
       
        /*! \brief  Command Freeze CallBack */
        [System.Runtime.InteropServices.UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate short IEC101ControlFreezeCallback(ushort u16ObjectId, iec60870common.eCounterFreezeFlags eCounterFreeze, ref sIEC101DataAttributeID ptFreezeID, ref sIEC101DataAttributeData ptFreezeValue, ref sIEC101WriteParameters ptFreezeCmdParams, ref short ptErrorValue);

        /*! \brief  Command Cancel CallBack */
        [System.Runtime.InteropServices.UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate short IEC101ControlCancelCallback( ushort u16ObjectId, iec60870common.eOperationFlag eOperation, ref sIEC101DataAttributeID ptCancelID, ref sIEC101DataAttributeData ptCancelValue, ref sIEC101CommandParameters ptCancelParams, ref short ptErrorValue);

        /*! \brief  Command PulseEndActterm CallBack  */
        [System.Runtime.InteropServices.UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate short IEC101ControlPulseEndActTermCallback(ushort u16ObjectId, ref sIEC101DataAttributeID ptOperateID, ref sIEC101DataAttributeData ptOperateValue, ref sIEC101CommandParameters ptOperateParams, ref short ptErrorValue);

        /*! \brief  Parameter Act Command  CallBack */
        [System.Runtime.InteropServices.UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate short IEC101ParameterActCallback(ushort u16ObjectId, ref sIEC101DataAttributeID ptOperateID, ref sIEC101DataAttributeData ptOperateValue, ref sIEC101ParameterActParameters ptParameterActParams, ref short ptErrorValue);

        /*! \brief  Debug Message CallBack */
        [System.Runtime.InteropServices.UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate short IEC101DebugMessageCallback(ushort u16ObjectId, ref sIEC101DebugData ptDebugData, ref short ptErrorValue);

        /*! \brief  Client Connection Status CallBack */
        [System.Runtime.InteropServices.UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate short IEC101ClientStatusCallback(ushort u16ObjectId, ref  sIEC101DataAttributeID psDAID, ref iec60870common.eStatus peSat, ref short ptErrorValue);

        /*! \brief IEC101 Directory call-back */
        [System.Runtime.InteropServices.UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public delegate short IEC101DirectoryCallback(ushort u16ObjectId, ref sIEC101DataAttributeID ptDirectoryID, ref sIEC101DirectoryList ptDirList, ref short ptErrorValue);



        /*! \brief      Create Server/client parameters structure  */
        [System.Runtime.InteropServices.StructLayoutAttribute(System.Runtime.InteropServices.LayoutKind.Sequential,
        CharSet = System.Runtime.InteropServices.CharSet.Ansi)]
        public struct sIEC101Parameters
        {
            public  tgtcommon.eApplicationFlag          eAppFlag;                           /*!< Flag set to indicate the type of application */
            public uint                                 u32Options;                         /*!< Options flag, used to set client/server global options see #eApplicationOptionFlag for values */
            public ushort                               u16ObjectId;                        /*!< User idenfication will be retured in the callback for iec101object identification*/
            public IEC101ReadCallback                   ptReadCallback;                     /*!< Read callback function. If equal to NULL then callback is not used. */
            public IEC101WriteCallback                  ptWriteCallback;                    /*!< Write callback function. If equal to NULL then callback is not used. */
            public IEC101UpdateCallback                 ptUpdateCallback;                   /*!< Update callback function. If equal to NULL then callback is not used. */
            public IEC101ControlSelectCallback          ptSelectCallback;                   /*!< Function called when a Select Command  is executed.  If equal to NULL then callback is not used*/
            public IEC101ControlOperateCallback         ptOperateCallback;                  /*!< Function called when a Operate command is executed.  If equal to NULL then callback is not used */
            public IEC101ControlCancelCallback          ptCancelCallback;                   /*!< Function called when a Cancel command is executed.  If equal to NULL then callback is not used */          
            public IEC101ControlFreezeCallback          ptFreezeCallback;                   /*!< Function called when a Freeze Command is executed.  If equal to NULL then callback is not used*/
            public IEC101ControlPulseEndActTermCallback ptPulseEndActTermCallback;          /*!< Function called when a pulse  command time expires.  If equal to NULL then callback is not used */ 
            public IEC101ParameterActCallback           ptParameterActCallback;             /*!< Function called when a Parameter act command is executed.  If equal to NULL then callback is not used */
            public IEC101DebugMessageCallback           ptDebugCallback;                    /*!< Function called when debug options are set. If equal to NULL then callback is not used */
            public IEC101ClientStatusCallback           ptClientStatusCallback;             /*!< Function called when client connection status changed */
            public IEC101DirectoryCallback              ptDirectoryCallback;                /*!< Directory callback function. List The Files in the Directory. */
            
        }






}

