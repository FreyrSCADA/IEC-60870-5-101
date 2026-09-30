/*****************************************************************************/
/*! \file        iec101api.h
 *  \brief       IEC101 API Header file
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


/*!
 * \defgroup IEC101API IEC60870-5-101 API
 * \{
 */


#ifndef     IEC101API_H

        /*! \brief      Define IEC101 API header */
    #define IEC101API_H 1


    #include "iec101types.h"

    /*! \brief          IEC101 Version Number */
    #define IEC101_VERSION  "21.06.022"


    #ifdef __cplusplus
        extern "C" {
    #endif

            /*! \brief          Get Library Version
                \ingroup        Management

                \return         version number of library as a string of char with format AA.BB.CCC

                Example Usage:
                \code
                                printf("Version number: %s", IEC101GetLibraryVersion());
                \endcode
            */
            PUBLICAPIPX const Integer8 * PUBLICAPISX IEC101GetLibraryVersion(void);

            /*! \brief          Get Library Build Time
                \ingroup        Management

                \return         Build time of the library as a string of char. Format "Mmm dd yyyy hh:mm:ss"

                Example Usage:
                \code
                                printf("Build Time: %s", IEC101GetLibraryBuildTime());
                \endcode
            */
            PUBLICAPIPX const Integer8 * PUBLICAPISX IEC101GetLibraryBuildTime(void);

            /*! \brief          Create a client or server object with call-bacnks for reading, writing and updating data objects
                \ingroup        Management

                \param[in]      psParameters    IEC101 Object Parameters
                \param[out]     pi16ErrorCode     Pointer to a Error Code (if any error occurs)
                \param[out]     ptErrorValue    Pointer to a Error Value (if any error occurs while creating the object)

                \return         Pointer to a new IEC101 object
                \return         NULL if an error occured (errorCode will contain an error code)

                Server Example Usage:
                \code

                    Integer16                    i16ErrorCode           = EC_NONE;
                    tErrorValue                         tErrorValue          = EV_NONE;
                    IEC101Object                           myServer             = NULL;
                    struct sIEC101Parameters               sParameters          = {0};

                    // Initialize parameters
                    sParameters.eAppFlag          = APP_SERVER;      
                    sParameters.u32Options          = APP_OPTION_NONE;      // No Options
                    sParameters.ptReadCallback    = cbRead;                 // Read Callback
                    sParameters.ptWriteCallback   = cbWrite;                // Write Callback           
                    sParameters.ptUpdateCallback  = NULL;                   // Update Callback
                    sParameters.ptSelectCallback  = cbSelect;                // Select Callback
                    sParameters.ptOperateCallback = cbOperate;              // Operate Callback
                    sParameters.ptCancelCallback  = cbCancel;               // Cancel Callback
                    sParameters.ptFreezeCallback  = cbFreeze;               // freeze Callback
                    sParameters.ptDebugCallback   = cbDebug;                // Debug Callback
                    sParameters.ptPulseEndActTermCallback = cbpulseend;     // pulse end callback   
                    sParameters.ptParameterActCallback = cbParameterAct;    // parameter act Callback
                    

                    // Create a server
                    myServer = IEC101Create(&sParameters, &i16ErrorCode, &tErrorValue);
                    if(myServer == NULL)
                    {
                        printf("\r\n Error iec101Create() failed: %d %d", i16ErrorCode,  tErrorValue);
                    
                    }   

                \endcode

                Client Example Usage:
                \code

                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;
                    IEC101Object                           myClient          = NULL;
                    struct sIEC101Parameters               sParameters       = {0};

                    // Initialize parameters
                    sParameters.eAppFlag          = APP_CLIENT;      // This is a IEC101 master
                    sParameters.u32Options        = 0;
                    sParameters.ptReadCallback    = NULL;            // Read Callback
                    sParameters.ptWriteCallback   = NULL;            // Write Callback           
                    sParameters.ptUpdateCallback  = cbUpdate;        // Update Callback
                    sParameters.ptSelectCallback  = NULL;            // Select commands
                    sParameters.ptOperateCallback = NULL;            // Operate commands
                    sParameters.ptCancelCallback  = NULL;            // Cancel commands
                    sParameters.ptDebugCallback   = cbDebug;         // Debug Callback
                    sParameters.ptPulseEndActTermCallback = NULL;     // pulse end callback
                    sParameters.ptClientStatusCallback   = cbClientstatus;         // client connection Callback
     
                          
                    // Create a client
                    myClient = IEC101Create(&sParameters, &i16ErrorCode, &tErrorValue);
                    if(myClient == NULL)
                    {
                        printf("\r\n Error iec101Create() failed: %d %d", i16ErrorCode,  tErrorValue);
                    
                    }

                \endcode
            */
            PUBLICAPIPX IEC101Object PUBLICAPISX IEC101Create(struct sIEC101Parameters *psParameters, Integer16 *pi16ErrorCode, tErrorValue *ptErrorValue);

            /*! \brief          Load the configuration to be used by IEC101 object.
                \ingroup        Management

                \param[in]      myIEC101Obj       IEC101 object 
                \param[in]      psIEC101Config    Pointer to IEC101 Configuration parameters 
                \param[out]     ptErrorValue    Pointer to a Error Value (if any error occurs while creating the object)

                \return         EC_NONE on success
                \return         otherwise error code

                Server Example Usage:
                \code

                    Integer16                    i16ErrorCode           = EC_NONE;
                    tErrorValue                         tErrorValue          = EV_NONE;
                    struct sIEC101ConfigurationParameters  sIEC101Config        = {0};

                    sIEC101Config.sServerSet.u8NumberofSerialPortConnections    =   1;

                    // Allocate memory for objects
                    sIEC101Config.sServerSet.psSerialSet = calloc(sIEC101Config.sServerSet.u8NumberofSerialPortConnections, sizeof(struct sSerialCommunicationSettings ));
                    if(sIEC101Config.sServerSet.psSerialSet == NULL)
                    {
                        printf("\r\nError: Not enough memory to alloc objects");
                        break;
                    }

                   sIEC101Config.sServerSet.psSerialSet[0].u16SerialPortNumber   =   1;
                   sIEC101Config.sServerSet.psSerialSet[0].eSerialBitRate       =   BITRATE_9600;
                   sIEC101Config.sServerSet.psSerialSet[0].eWordLength          =   WORDLEN_8BITS;
                   sIEC101Config.sServerSet.psSerialSet[0].eSerialParity        =   EVEN;
                   sIEC101Config.sServerSet.psSerialSet[0].eStopBits            =   STOPBIT_1BIT;
                   sIEC101Config.sServerSet.psSerialSet[0].eFlowControl         =  FLOW_NONE;

                   sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u16CharacterTimeout     =   0;
                   sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u16MessageTimeout       =   0;
                   sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u16InterCharacterDelay  =   0;
                   sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u16PostDelay            =   0;
                   sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u16PreDelay             =   0;
                   sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u8CharacterRetries      =   0;
                   sIEC101Config.sServerSet.psSerialSet[0].sRxTimeParam.u8MessageRetries        =   0;

                   sIEC101Config.sServerSet.sServerProtSet.eDataLink                =   BALANCED_MODE;
                   sIEC101Config.sServerSet.sServerProtSet.eCASize                  =   CA_TWO_BYTE;
                   sIEC101Config.sServerSet.sServerProtSet.u8TotalNumberofStations  =   1;
                   sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[0]     =   1;
                   sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[1]     =   0;
                   sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[2]     =   0;
                   sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[3]     =   0;
                   sIEC101Config.sServerSet.sServerProtSet.au16CommonAddress[4]     =   0;
                   sIEC101Config.sServerSet.sServerProtSet.eCOTsize                 =   COT_TWO_BYTE;
                   sIEC101Config.sServerSet.sServerProtSet.eIOAsize                 =   IOA_TWO_BYTE;
                   sIEC101Config.sServerSet.sServerProtSet.elinkAddrSize            =   DL_TWO_BYTE;
                   
                   sIEC101Config.sServerSet.sServerProtSet.u16DataLinkAddress   =   1;

                   sIEC101Config.sServerSet.sServerProtSet.eNegACK  = FIXED_FRAME_NACK;
                   sIEC101Config.sServerSet.sServerProtSet.ePosACK  =   FIXED_FRAME_ACK;

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

                   sIEC101Config.sServerSet.sServerProtSet.bEnableFileTransfer = FALSE;
                   strcpy((char*)sIEC101Config.sServerSet.sServerProtSet.ai8FileTransferDirPath, "\\FileTransferServer");
                   sIEC101Config.sServerSet.sServerProtSet.u16MaxFilesInDirectory    = 10;

                   sIEC101Config.sServerSet.sDebug.u32DebugOptions                              =   ( DEBUG_OPTION_TX | DEBUG_OPTION_RX);
                   //sIEC101Config.sServerSet.sDebug.u32DebugOptions    =   0;

                   sIEC101Config.sServerSet.sServerProtSet.bTransmitSpontMeasuredValue = TRUE;
                   sIEC101Config.sServerSet.sServerProtSet.bTransmitInterrogationMeasuredValue = TRUE;
                    sIEC101Config.sServerSet.sServerProtSet.bTransmitBackScanMeasuredValue = TRUE;

                    sIEC101Config.sServerSet.sServerProtSet.u8InitialdatabaseQualityFlag = (IV |NT); // 0- good/valid, 1 BIT- iv, 2 BIT-nt,  MAX VALUE -3   
                    sIEC101Config.sServerSet.sServerProtSet.bUpdateCheckTimestamp = FALSE; // if it true ,the timestamp change also generate event  during the iec101update 

                    sIEC101Config.sServerSet.u16NoofObject           = 2;        // Define number of objects

                    // Allocate memory for objects
                    sIEC101Config.sServerSet.psIEC101Objects = calloc(sIEC101Config.sServerSet.u16NoofObject, sizeof(struct sIEC101Object));
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
                        printf("\r\nError: IEC101LoadConfiguration() failed: %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
                        break;
                    }


                \endcode

                Client Example Usage:
                \code
                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;
                    struct sIEC101ConfigurationParameters  sIEC101Config   = {0};

                    sIEC101Config.sClientSet.u8NoofClient   =   1;
                    sIEC101Config.sClientSet.psClientObjects    =   calloc(sIEC101Config.sClientSet.u8NoofClient, sizeof(struct sIECClientObject ));

                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.u16SerialPortNumber   =   2;
                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.eSerialBitRate       =   BITRATE_9600;
                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.eWordLength          =   WORDLEN_8BITS;
                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.eSerialParity        =   EVEN;
                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.eStopBits            =   STOPBIT_1BIT;
                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.eFlowControl =  FLOW_NONE;
                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u16CharacterTimeout     =   0;
                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u16MessageTimeout       =   0;
                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u16InterCharacterDelay  =   0;
                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u16PostDelay            =   0;
                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u16PreDelay             =   0;
                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u8CharacterRetries      =   0;
                    sIEC101Config.sClientSet.psClientObjects[0].sSerialSet.sRxTimeParam.u8MessageRetries        =   0;

                    sIEC101Config.sClientSet.eLink  =   UNBALANCED_MODE;
                    
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.eCASize  =   CA_TWO_BYTE;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.eCOTsize =   COT_TWO_BYTE;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u8OriginatorAddress  =   1;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.eIOAsize =   IOA_TWO_BYTE;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.elinkAddrSize    =   DL_TWO_BYTE;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u8TotalNumberofStations  =   1;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.au16CommonAddress[0] =   1;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.au16CommonAddress[1]     =   0;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.au16CommonAddress[2]     =   0;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.au16CommonAddress[3]     =   0;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.au16CommonAddress[4]     =   0;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u16DataLinkAddress   =   1;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32LinkLayerTimeout  =   1000;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32PollInterval  =   1000;

                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32GeneralInterrogationInterval  =   0;    // in sec if 0 , gi will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group1InterrogationInterval   =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group2InterrogationInterval   =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group3InterrogationInterval   =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group4InterrogationInterval   =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group5InterrogationInterval   =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group6InterrogationInterval   =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group7InterrogationInterval   =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group8InterrogationInterval   =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group9InterrogationInterval   =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group10InterrogationInterval  =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group11InterrogationInterval  =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group12InterrogationInterval  =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group13InterrogationInterval  =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group14InterrogationInterval  =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group15InterrogationInterval  =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group16InterrogationInterval  =   0;    // in sec if 0 , group 1 interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32CounterInterrogationInterval  =   0;    // in sec if 0 , ci will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group1CounterInterrogationInterval    =   0;    // in sec if 0 , group 1 counter interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group2CounterInterrogationInterval    =   0;    // in sec if 0 , group 1 counter interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group3CounterInterrogationInterval    =   0;    // in sec if 0 , group 1 counter interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32Group4CounterInterrogationInterval    =   0;    // in sec if 0 , group 1 counter interrogation will not send in particular interval
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32ClockSyncInterval =   0;              // in sec if 0 , clock sync, will not send in particular interval 


                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32CommandTimeout    =   5000;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.bCommandResponseActtermUsed  =   TRUE;
                    sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.u32FileTransferTimeout           = 1000000;
                    strcpy((char*)sIEC101Config.sClientSet.psClientObjects[0].sClientProtSet.ai8FileTransferDirPath, "D:\\FileTest");

                    //sIEC101Config.sClientSet.sDebug.u32DebugOptions   =   0;
                    sIEC101Config.sClientSet.sDebug.u32DebugOptions                             =   ( DEBUG_OPTION_TX | DEBUG_OPTION_RX);

                    sIEC101Config.sClientSet.psClientObjects[0].u16NoofObject           = 2;        // Define number of objects

                    // Allocate memory for objects
                    sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects = calloc(sIEC101Config.sClientSet.psClientObjects[0].u16NoofObject, sizeof(struct sIEC101Object));
                    if(sIEC101Config.sClientSet.psClientObjects[0].psIEC101Objects == NULL)
                    {
                        printf("\r\nError: Not enough memory to alloc objects");
                        break;
                    }

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
                        printf("\r\nError: IEC101LoadConfiguration() failed:   %d - %s, %d - %s ", i16ErrorCode, errorcodestring(i16ErrorCode),  tErrorValue , errorvaluestring(tErrorValue));
                        break;
                    }


                \endcode
            */
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101LoadConfiguration(IEC101Object myIEC101Obj, struct sIEC101ConfigurationParameters *psIEC101Config, tErrorValue *ptErrorValue);

            /*! \brief          Start IEC101 object communication
                \ingroup        Management

                \param[in]      myIEC101Obj     IEC101 object to Start
                \param[out]     ptErrorValue    Pointer to a Error Value (if any error occurs while creating the object)

                \return         EC_NONE on success
                \return         otherwise error code

                Server Example Usage:
                \code

                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;

                    // Start server
                    i16ErrorCode = IEC101Start(myServer, &tErrorValue);  //Start myServer
                    if(i16ErrorCode != EC_NONE)
                    {  
                        printf("\r\n Error IEC101Start() failed: %i %i", i16ErrorCode,    tErrorValue);
                        
                    }

                \endcode 

                Client Example Usage:
                \code

                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;

                    // Start Client
                    i16ErrorCode = IEC101Start(myClient, &tErrorValue);  //Start myClient
                    if(i16ErrorCode != EC_NONE)
                    {  
                        printf("\r\n Error IEC101Start() failed: %i %i", i16ErrorCode,  tErrorValue);
                        break;
                    }            

                \endcode

                
            */
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101Start(IEC101Object myIEC101Obj, tErrorValue *ptErrorValue);

 
             /*! \brief           Set IEC101 debug options.
                 \ingroup         Management
             
                  \param[in]      myIEC101Obj         IEC101 object to Get Type and Size
                  \param[in]      psDebugParams       Pointer to debug parameters
                  \param[out]     ptErrorValue        Pointer to a Error Value (if any error occurs while creating the object)
             
                  \return         EC_NONE on success
                  \return         otherwise error code
             
                  Example Usage:
                  \code
                                
                    Integer16                  i16ErrorCode        = EC_NONE;
                    tErrorValue                       tErrorValue       = EV_NONE;
                                  
                    struct sIEC101DebugParameters       sDebugParams    = {0};
             
                    // Set the debug option to error, tx and rx data 
                    sDebugParams.u32DebugOptions   = DEBUG_OPTION_ERROR | DEBUG_OPTION_TX | DEBUG_OPTION_RX;
             
                    //update debug option
                    i16ErrorCode = IEC101SetDebugOptions(myIEC101Obj, &sDebugParams, &tErrorValue);
                    if(i16ErrorCode != EC_NONE)
                    {
                        printf("Set debug options IEC101 has failed: %i %i", i16ErrorCode, tErrorValue);
                    }

                  \endcode 

                 
              */
             PUBLICAPIPX Integer16 PUBLICAPISX IEC101SetDebugOptions(IEC101Object myIEC101Obj, struct sIEC101DebugParameters *psDebugParams, tErrorValue *ptErrorValue);            

 
            /*! \brief          Stop IEC101 object communication
                \ingroup        Management

                \param[in]      myIEC101Obj     IEC101 object to Stop
                \param[out]     ptErrorValue    Pointer to a Error Value (if any error occurs while creating the object)

                \return         EC_NONE on success
                \return         otherwise error code

                Server Example Usage:
                \code

                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;

                    // Stop server
                    i16ErrorCode = IEC101Stop(myServer, &tErrorValue);  //Stop myServer
                    if(i16ErrorCode != EC_NONE)
                    {  
                        printf("\r\n Error IEC101Stop() failed: %i %i", i16ErrorCode, tErrorValue);
                        
                    }

                \endcode 

                Client Example Usage:
                \code

                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;

                    // Stop Client
                    i16ErrorCode = IEC101Stop(myClient, &tErrorValue);  //Stop myClient
                    if(i16ErrorCode != EC_NONE)
                    {  
                        printf("\r\n Error IEC101Stop() failed: %i %i", i16ErrorCode,  tErrorValue);
                        break;
                    }            

                \endcode

            */
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101Stop(IEC101Object myIEC101Obj,tErrorValue *ptErrorValue);

            /*! \brief          Free memory used by IEC101 object.
                \ingroup        Management

                \param[in]      myIEC101Obj     IEC101 object to free
                \param[out]     ptErrorValue    Pointer to a Error Value (if any error occurs while creating the object)

                \return         EC_NONE on success
                \return         otherwise error code

                Server Example Usage:
                \code

                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;

                    // free server
                    i16ErrorCode = IEC101Free(myServer, &tErrorValue);  //free myServer
                    if(i16ErrorCode != EC_NONE)
                    {  
                        printf("\r\n Error IEC101free() failed: %i %i", i16ErrorCode, tErrorValue);
                        
                    }

                \endcode 

                Client Example Usage:
                \code

                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;

                    // free Client
                    i16ErrorCode = IEC101Free(myClient, &tErrorValue);  //free myClient
                    if(i16ErrorCode != EC_NONE)
                    {  
                        printf("\r\n Error IEC101free() failed: %i %i", i16ErrorCode,  tErrorValue);
                        break;
                    }            

                \endcode

            */
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101Free(IEC101Object myIEC101Obj, tErrorValue *ptErrorValue);

            
            /*!\brief           Update IEC101 data attribute ID to the New Value. 
                \ingroup        Management
            
                \param[in]      myIEC101Obj     IEC101 object to Update
                \param[in]      bCreateEvent    Generate event or not, if false, only update the database, not genearate event
                \param[in]      psDAID          Pointer to IEC101 Data Attribute ID
                \param[in]      psNewValue      Pointer to IEC101 Data Attribute Data
                \param[in]      u16Count        Number of IEC101 Data attribute ID and Data attribute data to be updated simultaneously
                \param[out]     ptErrorValue    Pointer to a Error Value (if any error occurs while creating the object)
            
                \return         EC_NONE on success
                \return         otherwise error code

                Server Example Usage:
                \code

                    
                    Integer16                    i16ErrorCode       = EC_NONE;
                    tErrorValue                         tErrorValue      = EV_NONE;
                
                    struct sIEC101DataAttributeID *psDAID                   = NULL; //update dataaddtribute
                    struct sIEC101DataAttributeData *psNewValue             = NULL; //updtae new value
                    unsigned int uiCount;

                    Unsigned8   u8Data                      = 1;
                    Float32 f32Data                         = -10;

                    // update parameters
                    uiCount     =   2;
                    psDAID      =   calloc(uiCount,sizeof(struct sIEC101DataAttributeID));
                    psNewValue  =   calloc(uiCount,sizeof(struct sIEC101DataAttributeData));
                
                
                    psDAID[0].u16SerialPortNumber                =   1;
                    psDAID[0].u16DataLinkAddress                =   1;
                    psDAID[0].eTypeID                           =   M_SP_NA_1;
                    psDAID[0].u32IOA                            =   5006;
                    psDAID[0].u16CommonAddress                      =   1;
                    psDAID[0].pvUserData                        =   NULL;
                    psNewValue[0].tQuality                      =   GD;
                    //current date 11/8/2012
                    psNewValue[0].sTimeStamp.u8Day              =   8;
                    psNewValue[0].sTimeStamp.u8Month            =   11;
                    psNewValue[0].sTimeStamp.u16Year            =   2012;
                
                    //time 13.35.0
                    psNewValue[0].sTimeStamp.u8Hour             =   13;
                    psNewValue[0].sTimeStamp.u8Minute           =   36;
                    psNewValue[0].sTimeStamp.u8Seconds          =   0;
                    psNewValue[0].sTimeStamp.u16MilliSeconds    =   0;
                    psNewValue[0].sTimeStamp.u16MicroSeconds    =   0;
                    psNewValue[0].sTimeStamp.i8DSTTime          =   0; //No Day light saving time
                    psNewValue[0].sTimeStamp.u8DayoftheWeek     =   4;
                
                    psNewValue[0].pvData                        =   &u8Data;
                    psNewValue[0].eDataType                     =   SINGLE_POINT_DATA;
                    psNewValue[0].eDataSize                     =   DOUBLE_POINT_SIZE;
                
                    psDAID[1].u16SerialPortNumber                =   1;
                    psDAID[1].u16DataLinkAddress                =   1;
                    psDAID[1].eTypeID                           =   M_ME_TF_1;
                    psDAID[1].u32IOA                            =   7006L;
                    psDAID[1].u16CommonAddress                  =   1;
                    psDAID[1].pvUserData                        =   NULL;
                    psNewValue[1].tQuality                      =   GD;
                    //current date 11/8/2012
                    psNewValue[1].sTimeStamp.u8Day              =   8;
                    psNewValue[1].sTimeStamp.u8Month            =   11;
                    psNewValue[1].sTimeStamp.u16Year            =   2012;
                
                    //time 13.35.0
                    psNewValue[1].sTimeStamp.u8Hour             =   13;
                    psNewValue[1].sTimeStamp.u8Minute           =   36;
                    psNewValue[1].sTimeStamp.u8Seconds          =   0;
                    psNewValue[1].sTimeStamp.u16MilliSeconds    =   0;
                    psNewValue[1].sTimeStamp.u16MicroSeconds    =   0;
                    psNewValue[1].sTimeStamp.i8DSTTime          =   0; //No Day light saving time
                    psNewValue[1].sTimeStamp.u8DayoftheWeek     =   4;
                
                    psNewValue[1].pvData                        =   &f32Data;
                    psNewValue[1].eDataType                     =   FLOAT32_DATA;
                    psNewValue[1].eDataSize                     =   FLOAT32_SIZE;

                    // Update server
                    i16ErrorCode = IEC101Update(myServer,psDAID,psNewValue,uiCount,&tErrorValue);  //Update myServer
                    if(i16ErrorCode != EC_NONE)
                    {
                        printf("\r\nError: IEC101Update() failed:  %i %i", i16ErrorCode, tErrorValue);
                    }

                \endcode 

            */            
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101Update(IEC101Object myIEC101Obj, Boolean bCreateEvent, struct sIEC101DataAttributeID *psDAID, struct sIEC101DataAttributeData *psNewValue, Unsigned16 u16Count, tErrorValue *ptErrorValue);

            /*!\brief           Read a value to a given Object ID. 
                \ingroup        Management
            
                \param[in]      myIEC101Obj       IEC101 object 
                \param[in]      psDAID          Pointer to IEC101 DataAttributeID structure (or compatable) that idendifies the point that is to be read
                \param[in]      psReturnedValue Pointer to Object Data structure that hold the returned vaule
                \param[out]     ptErrorValue    Pointer to a Error Value (if any error occurs while reading the object)
            
                \return         EC_NONE on success
                \return         otherwise error code

                Client Example Usage:
                \code
                
                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;
                
                    struct sIEC101DataAttributeID sDAID;
                    struct sIEC101DataAttributeData sReturnedValue;
                
                    sDAID.u16SerialPortNumber                =   1;
                    sDAID.u16DataLinkAddress                =   1;
                    sDAID.u16CommonAddress                  =   1;
                    sDAID.eTypeID               =   M_SP_NA_1;
                    sDAID.u16DataLinkAddress    =   1;
                    sDAID.u32IOA                =   8006;
                            
                    i16ErrorCode =    IEC101Read(myClient,&sDAID, &sReturnedValue,&tErrorValue);
                    if(i16ErrorCode != EC_NONE)
                    {
                        printf("\r\nError: IEC101Read() failed:  %i %i", i16ErrorCode, tErrorValue);
                    }
                    
                \endcode            
            */
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101Read(IEC101Object myIEC101Obj, struct sIEC101DataAttributeID *psDAID, struct sIEC101DataAttributeData *psReturnedValue, tErrorValue *ptErrorValue);

            /*!\brief           IEC101Client - send clock sync, General Interrogation, counter interrogation command. 
                \ingroup        Management
            
                \param[in]      myIEC101Obj       IEC101 object 
                \param[in]      eCounterFreeze    enum eCounterFreezeFlags
                \param[in]      psDAID            Pointer to IEC101_DataAttributeID structure (or compatable) that idendifies the point that is to be written
                \param[in]      psWriteValue      Pointer to Object Data structure that hold the new vaule of the struct sIEC101DataAttributeData 
                \param[in]      ptWriteParams     Pointer to struct sIEC101WriteParameters 
                \param[out]     ptErrorValue      Pointer to a Error Value 
            
                \return         EC_NONE on success
                \return         otherwise error code
                

            Client Example Usage:
            \code
            
                Integer16                    i16ErrorCode        = EC_NONE;
                tErrorValue                         tErrorValue       = EV_NONE;
            
                struct sIEC101DataAttributeID sDAID;
                struct sIEC101DataAttributeData sWriteValue;
            
                sDAID.u16SerialPortNumber                =   1;
                sDAID.u16DataLinkAddress                =   1;
                sDAID.u16CommonAddress                  =   1;
                sDAID.eTypeID               =   C_IC_NA_1;
                sDAID.u16DataLinkAddress    =   1;
                
                        
                i16ErrorCode =    IEC101Write(myClient,&sDAID, &sWriteValue,&tErrorValue);
                if(i16ErrorCode != EC_NONE)
                {
                    printf("\r\nError: IEC101Write() failed:  %i %i", i16ErrorCode, tErrorValue);
                }

             \endcode
            
            */            
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101Write(IEC101Object myIEC101Obj, enum eCounterFreezeFlags eCounterFreeze, struct sIEC101DataAttributeID *psDAID, struct sIEC101DataAttributeData *psWriteValue, struct sIEC101WriteParameters *ptWriteParams, tErrorValue *ptErrorValue);

            /*!\brief           IEC101Client Select a given control Data object.             
                \ingroup        Management
            
                \param[in]      myIEC101Obj       IEC101 object 
                \param[in]      psDAID          Pointer to IEC101 Data Attribute ID of control that is to be Selected
                \param[in]      psSelectValue   Pointer to IEC101 Data Attribute Data (The value the control is to be set)
                \param[in]      psSelectParams  Pointer to IEC101 Data Attribute Parameters (Quality Paramters)
                \param[out]     ptErrorValue    Pointer to a Error Value 
            
                \return         EC_NONE on success
                \return         otherwise error code

                Client Example Usage:
                \code

                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;

                    Float32             f32value        =   0;
                    struct sIEC101DataAttributeID sDAID;
                    struct sIEC101DataAttributeData sSelectValue;
                    struct sIEC101CommandParameters sSelectParams;
                    
                    sDAID.u16SerialPortNumber                =   1;
                    sDAID.u16DataLinkAddress                =   1;
                    sDAID.u16CommonAddress                  =   1;
                    sDAID.eTypeID               =   C_SE_TC_1;
                    sDAID.u16DataLinkAddress    =   1;
                    sDAID.u32IOA                =   8006;

                    f32value                    =   -1.2345;
                    sSelectValue.eDataSize      =   FLOAT32_SIZE;
                    sSelectValue.eDataType      =   FLOAT32_DATA;
                    sSelectValue.pvData         =   &f32value;

                    sSelectParams.eQOCQU        =   NOADDDEF;
                    memset(&sSelectValue.sTimeStamp, 0, sizeof(struct sTargetTimeStamp));

                    //current date 11/8/2012
                    sSelectValue.sTimeStamp.u8Day               =   8;
                    sSelectValue.sTimeStamp.u8Month             =   11;
                    sSelectValue.sTimeStamp.u16Year             =   2012;

                    //time 13.35.0
                    sSelectValue.sTimeStamp.u8Hour              =   13;
                    sSelectValue.sTimeStamp.u8Minute            =   36;
                    sSelectValue.sTimeStamp.u8Seconds           =   0;
                    sSelectValue.sTimeStamp.u16MilliSeconds     =   0;
                    sSelectValue.sTimeStamp.u16MicroSeconds     =   0;
                    sSelectValue.sTimeStamp.i8DSTTime           =   0; //No Day light saving time
                    sSelectValue.sTimeStamp.u8DayoftheWeek      =   4;
                    
                    
                    i16ErrorCode =    IEC101Select(myClient,&sDAID, &sSelectValue, &sSelectParams,&tErrorValue);
                    if(i16ErrorCode != EC_NONE)
                    {
                        printf("\r\nError: IEC101Select() failed:  %i %i", i16ErrorCode, tErrorValue);
                    }

                \endcode
            */            
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101Select(IEC101Object myIEC101Obj, struct sIEC101DataAttributeID *psDAID, struct sIEC101DataAttributeData *psSelectValue, struct sIEC101CommandParameters *psSelectParams , tErrorValue *ptErrorValue);

            /*!\brief           Send an Operate command on given control Data object. 
                \ingroup        Management
            
                \param[in]      myIEC101Obj       IEC101 object 
                \param[in]      psDAID          Pointer to IEC101 Data Attribute ID of control that is to be Operated
                \param[in]      psOperateValue  Pointer to IEC101 Data Attribute Data (The value the control is to be set )
                \param[in]      psOperateParams Pointer to IEC101 Data Attribute Parameters (Quality Paramters)
                \param[out]     ptErrorValue    Pointer to a Error Value 

                \return         EC_NONE on success
                \return         otherwise error code

                Client Example Usage:
                \code
                
                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;

                    Float32             f32value        =   0;
                    struct sIEC101DataAttributeID sDAID;
                    struct sIEC101DataAttributeData sOperateValue;
                    struct sIEC101CommandParameters sOperateParams;

                    sDAID.u16SerialPortNumber                =   1;
                    sDAID.u16DataLinkAddress                =   1;
                    sDAID.u16CommonAddress                  =   1;
                    sDAID.eTypeID               =   C_SE_TC_1;
                    sDAID.u16DataLinkAddress    =   1;
                    sDAID.u32IOA                =   8006;

                    f32value                    =   -1.2345;
                    sOperateValue.eDataSize     =   FLOAT32_SIZE;
                    sOperateValue.eDataType     =   FLOAT32_DATA;
                    sOperateValue.pvData            =   &f32value;

                    sOperateParams.eQOCQU       =   NOADDDEF;
                    memset(&sOperateValue.sTimeStamp, 0, sizeof(struct sTargetTimeStamp));

                    //current date 11/8/2012
                    sOperateValue.sTimeStamp.u8Day              =   8;
                    sOperateValue.sTimeStamp.u8Month                =   11;
                    sOperateValue.sTimeStamp.u16Year                =   2012;

                    //time 13.35.0
                    sOperateValue.sTimeStamp.u8Hour             =   13;
                    sOperateValue.sTimeStamp.u8Minute           =   36;
                    sOperateValue.sTimeStamp.u8Seconds          =   0;
                    sOperateValue.sTimeStamp.u16MilliSeconds        =   0;
                    sOperateValue.sTimeStamp.u16MicroSeconds        =   0;
                    sOperateValue.sTimeStamp.i8DSTTime          =   0; //No Day light saving time
                    sOperateValue.sTimeStamp.u8DayoftheWeek     =   4;
                    
                    
                    i16ErrorCode =    IEC101Operate(myClient,&sDAID, &sOperateValue, &sOperateParams,&tErrorValue);
                    if(i16ErrorCode != EC_NONE)
                    {
                        printf("\r\nError: IEC101Operate() failed:  %i %i", i16ErrorCode, tErrorValue);
                    }
                    
                \endcode            
            */             
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101Operate(IEC101Object myIEC101Obj, struct sIEC101DataAttributeID *psDAID, struct sIEC101DataAttributeData *psOperateValue, struct sIEC101CommandParameters *psOperateParams, tErrorValue *ptErrorValue);

			/*!\brief           IEC101Client SelectBeforeOperate a given control Data object.             
                \ingroup        Management
            
                \param[in]      myIEC101Obj       IEC101 object 
                \param[in]      psDAID          Pointer to IEC101 Data Attribute ID of control that is to be Selected
                \param[in]      psSelectValue   Pointer to IEC101 Data Attribute Data (The value the control is to be set)
                \param[in]      psSelectParams  Pointer to IEC101 Data Attribute Parameters (Quality Paramters)
                \param[out]     ptErrorValue    Pointer to a Error Value 
            
                \return         EC_NONE on success
                \return         otherwise error code

                Client Example Usage:
                \code

                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;

                    Float32             f32value        =   0;
                    struct sIEC101DataAttributeID sDAID;
                    struct sIEC101DataAttributeData sSelectValue;
                    struct sIEC101CommandParameters sSelectParams;
                    
                    sDAID.u16SerialPortNumber                =   1;
                    sDAID.u16DataLinkAddress                =   1;
                    sDAID.u16CommonAddress                  =   1;
                    sDAID.eTypeID               =   C_SE_TC_1;
                    sDAID.u16DataLinkAddress    =   1;
                    sDAID.u32IOA                =   8006;

                    f32value                    =   -1.2345;
                    sSelectValue.eDataSize      =   FLOAT32_SIZE;
                    sSelectValue.eDataType      =   FLOAT32_DATA;
                    sSelectValue.pvData         =   &f32value;

                    sSelectParams.eQOCQU        =   NOADDDEF;
                    memset(&sSelectValue.sTimeStamp, 0, sizeof(struct sTargetTimeStamp));

                    //current date 11/8/2012
                    sSelectValue.sTimeStamp.u8Day               =   8;
                    sSelectValue.sTimeStamp.u8Month             =   11;
                    sSelectValue.sTimeStamp.u16Year             =   2012;

                    //time 13.35.0
                    sSelectValue.sTimeStamp.u8Hour              =   13;
                    sSelectValue.sTimeStamp.u8Minute            =   36;
                    sSelectValue.sTimeStamp.u8Seconds           =   0;
                    sSelectValue.sTimeStamp.u16MilliSeconds     =   0;
                    sSelectValue.sTimeStamp.u16MicroSeconds     =   0;
                    sSelectValue.sTimeStamp.i8DSTTime           =   0; //No Day light saving time
                    sSelectValue.sTimeStamp.u8DayoftheWeek      =   4;
                    
                    
                    i16ErrorCode =    IEC101Select(myClient,&sDAID, &sSelectValue, &sSelectParams,&tErrorValue);
                    if(i16ErrorCode != EC_NONE)
                    {
                        printf("\r\nError: IEC101Select() failed:  %i %i", i16ErrorCode, tErrorValue);
                    }

                \endcode
            */            
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101SelectBeforeOperate(IEC101Object myIEC101Obj, struct sIEC101DataAttributeID *psDAID, struct sIEC101DataAttributeData *psSelectValue, struct sIEC101CommandParameters *psSelectParams , tErrorValue *ptErrorValue);

            /*!\brief           Cancel current command on given control Data object. 
                \ingroup        Management

                
                \param[in]      myIEC101Obj     IEC101 object 
                \param[in]      eOperation      Select/Operate to cancel enum eOperationFlag
                \param[in]      psDAID          Pointer to IEC101 Data Attribute ID of control that is to be canceled
                \param[in]      psCancelValue   Pointer to IEC101 Data Attribute Data (The value the control is to be set to)
                \param[in]      psCancelParams  Pointer to struct sIEC101CommandParameters (Quality Paramters)
                \param[out]     ptErrorValue    Pointer to a Error Value 
            
                \return         EC_NONE on success
                \return         otherwise error code

                Client Example Usage:
                \code

                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;

                    Float32             f32value        =   0;
                    struct sIEC101DataAttributeID sDAID;
                    struct sIEC101DataAttributeData sCancelValue;
                    struct sIEC101CommandParameters sCancelParams;

                    sDAID.u16SerialPortNumber                =   1;
                    sDAID.u16DataLinkAddress                =   1;
                    sDAID.u16CommonAddress                  =   1;
                    sDAID.eTypeID               =   C_SE_TC_1;
                    sDAID.u16DataLinkAddress    =   1;
                    sDAID.u32IOA                =   8006;

                    f32value                    =   -1.2345;
                    sCancelValue.eDataSize      =   FLOAT32_SIZE;
                    sCancelValue.eDataType      =   FLOAT32_DATA;
                    sCancelValue.pvData         =   &f32value;

                    sCancelParams.eQOCQU        =   NOADDDEF;
                    memset(&sCancelValue.sTimeStamp, 0, sizeof(struct sTargetTimeStamp));

                    //current date 11/8/2012
                    sCancelValue.sTimeStamp.u8Day               =   8;
                    sCancelValue.sTimeStamp.u8Month             =   11;
                    sCancelValue.sTimeStamp.u16Year             =   2012;

                    //time 13.35.0
                    sCancelValue.sTimeStamp.u8Hour              =   13;
                    sCancelValue.sTimeStamp.u8Minute            =   36;
                    sCancelValue.sTimeStamp.u8Seconds           =   0;
                    sCancelValue.sTimeStamp.u16MilliSeconds     =   0;
                    sCancelValue.sTimeStamp.u16MicroSeconds     =   0;
                    sCancelValue.sTimeStamp.i8DSTTime           =   0; //No Day light saving time
                    sCancelValue.sTimeStamp.u8DayoftheWeek      =   4;
                    
                    
                    i16ErrorCode =    IEC101Cancel(OPERATE, myClient,&sDAID, &sCancelValue, &sCancelParams,&tErrorValue);
                    if(i16ErrorCode != EC_NONE)
                    {
                        printf("\r\nError: IEC101Cancel() failed:  %i %i", i16ErrorCode, tErrorValue);
                    }
                    

                \endcode            
            */             
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101Cancel(enum eOperationFlag eOperation, IEC101Object myIEC101Obj, struct sIEC101DataAttributeID *psDAID, struct sIEC101DataAttributeData *psCancelValue, struct sIEC101CommandParameters *psCancelParams, tErrorValue *ptErrorValue);

            
            /*! \brief        Get IEC101 data type and data size to the returned Value.
                \ingroup      Management
                     
                \param[in]    myIEC101Obj           IEC101 object to Get Type and Size
                \param[in]    psDAID              Pointer to IEC101 Data Attribute ID
                \param[out]   psReturnedValue     Pointer to IEC101 Data Attribute Data containing only data type and data size.
                \param[out]   ptErrorValue        Pointer to a Error Value 
                     
                \return       EC_NONE on success
                \return       otherwise error code
                     
                Example Usage:
                \code

                    Integer16                    i16ErrorCode        = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;
                    struct sIEC101DataAttributeID      sDAID           = {0};
                    struct sIEC101DataAttributeData    sReturnedValue  = {0};
                     
                    // Set the Type ID for which you want to get the datatype and datasize 
                    sDAID.eTypeID         = M_SP_NA_1;
                     
                    //Call function to get type and size
                    i16ErrorCode = IEC101GetDataTypeAndSize(myiec101Obj, &sDAID, &sReturnedValue, &tErrorValue);
                    if(i16ErrorCode != EC_NONE)
                    {
                       printf("Get Type IEC101 has failed: %i %i", i16ErrorCode, tErrorValue);
                    }
                    else
                    {
                       printf("\r\n Type is : %u, Size is %u", sReturnedValue.eDataType, sReturnedValue.eDataSize);
                    }
                    
                \endcode 

            */
             PUBLICAPIPX Integer16 PUBLICAPISX IEC101GetDataTypeAndSize(IEC101Object myIEC101Obj, struct sIEC101DataAttributeID *psDAID, struct sIEC101DataAttributeData *psReturnedValue, tErrorValue *ptErrorValue);

                /*!\brief           Send an Parameter Act command on given control Data object. 
                \ingroup        Management

                \param[in]      myIEC101Obj       IEC101 object 
                \param[in]      psDAID          Pointer to IEC101 Data Attribute ID of control that is to be Operated
                \param[in]      psOperateValue  Pointer to IEC101 Data Attribute Data (The value the control is to be set )
                \param[in]      psParaParams Pointer to IEC101 Data Attribute Parameters (Quality Paramters)
                \param[out]     ptErrorValue    Pointer to a Error Value 

                \return         EC_NONE on success
                \return         otherwise error code

                Client Example Usage:
                \code
                
                    Integer16                  i16ErrorCode      = EC_NONE;
                    tErrorValue                         tErrorValue       = EV_NONE;

                    Float32             f32value        =   0;
                    struct sIEC101DataAttributeID sDAID;
                    struct sIEC101DataAttributeData sOperateValue;
                    struct sIEC101ParameterActParameters sParaParams;
                    
                    sDAID.u16SerialPortNumber                =   1;
                    sDAID.u16DataLinkAddress                =   1;
                    sDAID.u16CommonAddress                  =   1;
                    sDAID.eTypeID               =   P_ME_NC_1;
                    sDAID.u16CommonAddress    =   1;
                    sDAID.u32IOA                =   8006;

                    f32value                    =   -1.2345;
                    sOperateValue.eDataSize     =   FLOAT32_SIZE;
                    sOperateValue.eDataType     =   FLOAT32_DATA;
                    sOperateValue.pvData            =   &f32value;

                    sOperateParams.eQOCQU       =   NOADDDEF;
                    memset(&sOperateValue.sTimeStamp, 0, sizeof(struct sTargetTimeStamp));

                    //current date 11/8/2012
                    sOperateValue.sTimeStamp.u8Day              =   8;
                    sOperateValue.sTimeStamp.u8Month                =   11;
                    sOperateValue.sTimeStamp.u16Year                =   2012;

                    //time 13.35.0
                    sOperateValue.sTimeStamp.u8Hour             =   13;
                    sOperateValue.sTimeStamp.u8Minute           =   36;
                    sOperateValue.sTimeStamp.u8Seconds          =   0;
                    sOperateValue.sTimeStamp.u16MilliSeconds        =   0;
                    sOperateValue.sTimeStamp.u16MicroSeconds        =   0;
                    sOperateValue.sTimeStamp.i8DSTTime          =   0; //No Day light saving time
                    sOperateValue.sTimeStamp.u8DayoftheWeek     =   4;
                    
                    
                    i16ErrorCode =  IEC101ParameterAct(myClient,&sDAID, &sOperateValue, &sOperateParams,&tErrorValue);
                    if(i16ErrorCode != EC_NONE)
                    {
                        printf("\r\nError: IEC101ParameterAct() failed: %i %i", i16ErrorCode, tErrorValue);
                    }
                    
                \endcode            
            */
             PUBLICAPIPX Integer16 PUBLICAPISX IEC101ParameterAct(IEC101Object myIEC101Obj, struct sIEC101DataAttributeID *psDAID,  struct sIEC101DataAttributeData *psOperateValue, struct sIEC101ParameterActParameters *psParaParams, tErrorValue *ptErrorValue);

            /*! \brief        Get IEC101 Client Status.
             *  \par          Get IEC101 Get Client connection status.
             *  \ingroup      Management
             *
             *  \param[in]    myIEC101Obj         IEC101 object 
             *  \param[in]    psDAID              Pointer to IEC101 Data Attribute ID
             *  \param[out]    peSat              Pointer to enum eStatus 
             *  \param[out]   ptErrorValue        Pointer to a Error Value
             *
             *  \return       EC_NONE on success
             *  \return       otherwise error code
             */
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101ClientStatus(IEC101Object myIEC101Obj, struct sIEC101DataAttributeID *psDAID, enum eStatus *peSat, tErrorValue *ptErrorValue);

            
             /*! \brief        Get IEC101 Get File.
             *  \par          Get IEC101 Get file Using File Name.
             *  \ingroup      Management
             *
             *  \param[in]    myIEC101Obj         IEC101 object to Get Type and Size
             *  \param[in]    psDAID              Pointer to IEC101 Data Attribute ID
             *  \param[in]    u16FileName         File Name.
             *  \param[out]   ptErrorValue        Pointer to a Error Value
             *
             *  \return       EC_NONE on success
             *  \return       otherwise error code
             */
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101GetFile(IEC101Object myIEC101Obj, struct sIEC101DataAttributeID * psDAID, Unsigned16 u16FileName, tErrorValue *ptErrorValue);
        
                /*! \brief        IEC101 List Directory
             *  \par          Get Directory List as call Backs
             *  \ingroup      Management
             *
             *  \param[in]    myIEC101Obj         IEC101 object to Get Type and Size
             *  \param[in]    psDAID              Pointer to IEC101 Data Attribute ID
             *  \param[out]   ptErrorValue        Pointer to a Error Value
             *
             *  \return       EC_NONE on success
             *  \return       otherwise error code
             */
            PUBLICAPIPX Integer16 PUBLICAPISX IEC101ListDirectory(IEC101Object myIEC101Obj, struct sIEC101DataAttributeID * psDAID, tErrorValue *ptErrorValue);
              
            /*! \brief        Get IEC101 object Status.
             *  \par          Get IEC101 Get object status -  loaded, running, stoped, freed.
             *  \ingroup      Management
             *
             *  \param[in]    myIEC101Obj         IEC101 object 
             *  \param[out]   peCurrentState      Pointer to enum  eAppState   
             *  \param[out]   ptErrorValue        Pointer to a Error Value
             *
             *  \return       EC_NONE on success
             *  \return       otherwise error code
             */
            PUBLICAPIPX Integer16 PUBLICAPISX GetIEC101ObjectStatus(IEC101Object myIEC101Obj, enum  eAppState  *peCurrentState, tErrorValue *ptErrorValue);

            /*! \brief        Get Error code String
            *  \par            For particular Error code , get Error String
            *  \ingroup        Management
            *
            *  \param[in]      psIEC101ErrorCodeDes - Pointer to struct sIEC101ErrorCode 
            *
            *  \return         error code string
            */            
            PUBLICAPIPX void PUBLICAPISX IEC101ErrorCodeString(struct sIEC101ErrorCode *psIEC101ErrorCodeDes);
            
            /*! \brief        Get Error value String
            *  \par            For particular Error value , get Error String
            *  \ingroup        Management
            *
            *  \param[in]      psIEC101ErrorValueDes - Pointer to struct sIEC101ErrorValue 
            *
            *  \return         error value string
            */
            PUBLICAPIPX void PUBLICAPISX IEC101ErrorValueString(struct sIEC101ErrorValue *psIEC101ErrorValueDes);

            /*! \brief             Get IEC 101 Library License information
             *  \par               Function used to get IEC 101 Library License information
             *
             *  \return            License information of library as a string of char 
             *  Example Usage:
             *  \code
             *      printf("Version number: %s", IEC101GetLibraryVersion(void));
             *  \endcode
             */
            PUBLICAPIPX const Integer8 * PUBLICAPISX IEC101GetLibraryLicenseInfo(void);

    		/*! \brief		  Get IEC101 Client - stop/start polling particular server in serial multi drop
			 *	\par		  Get IEC101 Get Client - stop/start polling particular server in serial multi drop
			 *
			 *	\param[in]	  myIEC101Obj 	  IEC101 object 
			 *	\param[in]	  psDAID			  Pointer to dnp3 Data Attribute ID
			 *	\param[out]   bStop 			True - stop , false - start polling particular server/device
			 *	\param[out]   ptErrorValue		  Pointer to a Error Value
			 *
			 *	\return 	  EC_NONE on success
			 *	\return 	  otherwise error code
			 */
			PUBLICAPIPX Integer16 PUBLICAPISX IEC101ClientStopServerMultidrop(IEC101Object myIEC101Obj, struct sIEC101DataAttributeID *psDAID, Boolean bStop, tErrorValue *ptErrorValue);
    

    #ifdef __cplusplus
        }
    #endif

#endif


/*!
 *\}
 */


