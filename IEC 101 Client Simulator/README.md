# [IEC 60870-5-101 Protocol](https://www.freyrscada.com/iec-60870-5-101.php)

RTU Server Simulator, Master Client Simulator, Windows and Linux POSIX ARM, IEC101 Source Code in C, C++, C# .NET Programming

Support both balanced and unbalanced mode.

IEC 60870-5 part 101 enables communication between IED, RTU control station and substation via a standard Serial network. 
IEC 60870 5 101 protocol (IEC 101) is a part of IEC Telecontrol Equipment and Systems Standard IEC 60870-5 that provides a communication profile for sending basic telecontrol messages between two systems in electrical engineering and power system automation.
IEC 60870 part 5 is one of the IEC 60870 set of standards which define systems used for telecontrol (supervisory control and data acquisition SCADA) in electrical engineering and power system automation applications. 
Part 5 provides a communication profile for sending basic telecontrol messages between two systems, which uses permanent directly connected data circuits between the systems. The IEC Technical Committee 57 (Working Group 03) have developed a protocol standard for telecontrol, teleprotection, and associated telecommunications for electric power systems. 
The result of this work is IEC 60870-5. Five documents specify the base IEC 60870-5:

- IEC 60870-5-1 Transmission Frame Formats
- IEC 60870-5-2 Data Link Transmission Services
- IEC 60870-5-3 General Structure of Application Data
- IEC 60870-5-4 Definition and Coding of Information Elements
- IEC 60870-5-5 Basic Application Functions

[![IEC 60870-5-101 Protocol](https://www.freyrscada.com/images/101w320x220.jpg)](https://www.freyrscada.com/iec-60870-5-101.php)

Make your RTU, protocol converter, Gateway, HMI, Data concentrator compatible with iec 101.



## [Download Evaluation Kit - IEC 101 Development Bundle](https://www.freyrscada.com/iec-60870-5-101.php#Download-IEC60870-5-101-Development-Bundle)

In the Development Bundle, We included IEC 101 Protocol Server  Client Simulator, Windows and Linux SDK, C# projects, Doxygen documentation and Raspberry Pi, BeagleBone Demo library.


# [IEC 60870-5-101 Protocol Client Master Simulator](https://www.freyrscada.com/iec-60870-5-101-Client-Simulator.php)


Complete Simulation of IEC 101 Client as per Protocol Standard including File transfer (Both Monitoring and control direction).

[![IEC 60870-5 part 101 Protocol Client Master Simulator](https://www.freyrscada.com/images/iec101clientsimlogo_thump.jpg)](https://www.freyrscada.com/iec-60870-5-101-Client-Simulator.php)


​Support all type of ASDU Typeid according to protocol specification

1) Monitoring (Process information in monitor direction), M_SP. M_DP, M_ST,...

2) control (Process information in control direction), C_SC, C_DC, ...

3)  System information in monitor direction, M_EI

4) System information in control direction C_IC, C_CI

5)  Parameter in control direction, P_ME

6) File transfer ( Both Monitor And Control Direction) F_FR, F_SR, F_SC


IEC 101 Client Simulator was originally developed to test the functionalities of IEC 60870-5-101 stack Client operation.

We can add up to 50 Client node in the simulator. Every Client node will work independently.

Simulator window shows the Connection status, connection port number.


## Features

 - Multiple Master / Client Simulation
 
 - Support both balanced and unbalanced mode

 - In a Single Client(link) simulate Multiple Stations (Common Address)

 - Data Mode, and Test mode connection type available

 - Supports "Select-Before-Operate" SBO or "Direct-execute" command execution modes

 - supports File Transfer ( Both Monitor And Control Direction), Directory commands

 - Clock synchronization, General Interrogation, counter interrogation, 

 - Parameter command


## [IEC 60870-5-101 Protocol Client Master Simulator User Manual](https://www.freyrscada.com/docs/FreyrSCADA-IEC-60870-5-101-Client-Simulator-User-Manual.pdf)



# [IEC 60870-5-101 Source Code Windows C C++ C# .net Linux Arm POSIX C C++](https://www.freyrscada.com/iec-60870-5-101-Source-Code-Library.html)


The most complete implementation of IEC 101 protocol stack including File transfer (Monitor and Control Direction), Directory Commnads, Supports all type of Monitoring, command , parameter ASDUs.

Low memory footprint, easy start on any hardware platform, can operate with or without an operating system, delivered as a source code,

high configurability allows to use required features only, royalty-free licensing.


[![IEC 60870-5-101 Code Windows C C++ C# .net Linux Arm POSIX](https://www.freyrscada.com/images/IEC-60870-5-101-source-code-library-stack.jpg)](https://www.freyrscada.com/iec-60870-5-101-Source-Code-Library.html)


## Salient Features


 - Written in ANSI-Standard C Source Code, under a strict corporate coding standard, and supports C++, C#

 - Transparent licensing scheme - No hidden costs, No deferred payments.

 - High performance, robust and scalable architecture

 - Provides a simple method for systems Integrators and OEMs to utilize standard tools to implement their systems

 - Our stacks are fully compliant with "POSIX" and tested in ubuntu, feroda, Debian, QNX, Linux Embedded OS and Various Cross compiler tool chains.

 - Our all protocol stack supports "POSIX compliant operating system"

 - Context-based event-driven model
 
 - Support both balanced and unbalanced mode

 - Multiple Server and Client Simulation

 - In a Single Server(link) simulate Multiple Stations (Common Address / Station Address)

 - Supports Background Scan, Cyclic Data Transmission, Double Transmission, Redundancy and File transfer.

 - Communication with redundant control systems and interruption-free switch over between redundant systems

 - Supports "Select-Before-Operate" and "Direct-Execute" command execution modes

 - Source Code Library allows a fast and cost efficient implementation

 - APIs are designed to be very easy to use and flexible


## Application Examples

 - Integrate existing devices to a modern control system with a field proven product

 - Use the IEC-101 event based communication instead of polling

 - Feeder automation

 - Substation automation

 - Utility automation

 - Reclosers

 - Protection relays
 
  
## Standard IEC 60870-5-101 ASDU - Typeids


Type            Dec             Description


M_SP_NA_1         1         Single-point information

M_SP_TA_1         2         Single-point information with time tag  ( IEC 101 Supported )

M_DP_NA_1         3         Double-point information

M_DP_TA_1         4         Double-point information with time tag ( IEC 101 Supported )

M_ST_NA_1         5         Step position information

M_ST_TA_1         6         Step position information with time tag ( IEC 101 Supported )

M_BO_NA_1         7         Bitstring of 32 bit

M_BO_TA_1         8         Bitstring of 32 bit with time tag ( IEC 101 Supported )

M_ME_NA_1         9         Measured value, normalised value

M_ME_TA_1         10        Measured value, normalized value with time tag ( IEC 101 Supported )

M_ME_NB_1         11        Measured value, scaled value

M_ME_TB_1         12        Measured value, scaled value wit time tag ( IEC 101 Supported )

M_ME_NC_1         13        Measured value, short floating point number

M_ME_TC_1         14        Measured value, short floating point number with time tag ( IEC 101 Supported )

M_IT_NA_1         15        Integrated totals

M_IT_TA_1         16        Integrated totals with time tag ( IEC 101 Supported )

M_EP_TA_1         17        Event of protection equipment with time tag

M_EP_TB_1         18        Packed start events of protection equipment with time tag

M_EP_TC_1         19        Packed output circuit information of protection equipment with time tag

M_PS_NA_1         20        Packed single point information with status change detection

M_ME_ND_1         21        Measured value, normalized value without quality descriptor

ASDU_TYPE_22..29  22..29    Reserved (standard area)

M_SP_TB_1         30        Single-point information with time tag CP56Time2a

M_DP_TB_1         31        Double-point information with time tag CP56Time2a

M_ST_TB_1         32        Step position information with time tag CP56Time2a

M_BO_TB_1         33        Bitstring of 32 bit with time tag CP56Time2a

M_ME_TD_1         34        Measured value, normalised value with time tag CP56Time2a

M_ME_TE_1         35        Measured value, scaled value with time tag CP56Time2a

M_ME_TF_1         36        Measured value, short floating point number with time tag CP56Time2a

M_IT_TB_1         37        Integrated totals with time tag CP56Time2a

M_EP_TD_1         38        Event of protection equipment with time tag CP56Time2a

M_EP_TE_1         39        Packed start events of protection equipment with time tag CP56Time2a

M_EP_TF_1         40        Packed output circuit information of protection equipment with time tag CP56Time2a

ASDU_TYPE_41..44  41..44    Reserved (standard area)

C_SC_NA_1         45        Single command

C_DC_NA_1         46        Double command

C_RC_NA_1         47        Regulating step command

C_SE_NA_1         48        Set-point Command, normalized value

C_SE_NB_1         49        Set-point Command, scaled value

C_SE_NC_1         50        Set-point Command, short floating point number

C_BO_NA_1         51        Bitstring 32 bit command

ASDU_TYPE_52..57  52..57    Reserved (standard area)

C_SC_TA_1         58        Single command with time tag CP56Time2a

C_DC_TA_1         59        Double command with time tag CP56Time2a

C_RC_TA_1         60        Regulating step command with time tag CP56Time2a

C_SE_TA_1         61        Measured value, normalised value command with time tag CP56Time2a

C_SE_TB_1         62        Measured value, scaled value command with time tag CP56Time2a

C_SE_TC_1         63        Measured value, short floating point number command with time tag CP56Time2a

C_BO_TA_1         64        Bitstring of 32 bit command with time tag CP56Time2a

ASDU_TYPE_65..69  65..69    Reserved (standard area)

M_EI_NA_1         70        End of Initialization

ASDU_TYPE_71..99  71..99    Reserved (standard area)

C_IC_NA_1         100       Interrogation command

C_CI_NA_1         101       Counter interrogation command

C_RD_NA_1         102       Read command

C_CS_NA_1         103       Clock synchronization command

C_TS_NA_1         101       Test command

C_RP_NA_1         105       Reset process command

C_CD_NA_1         106       Delay acquisition command

C_TS_TA_1         107       Test command with time tag CP56Time2a

ASDU_TYPE_108..109 108..109 Reserved (standard area)

P_ME_NA_1         110       Parameter of measured values, normalized value

P_ME_NB_1         111       Parameter of measured values, scaled value

P_ME_NC_1         112       Parameter of measured values, short floating point number

P_AC_NA_1         113       Parameter activation

ASDU_TYPE_114..119 114..119 Reserved (standard area)

F_FR_NA_1         120      File ready

F_SR_NA_1         121      Section ready

F_SC_NA_1         122      Call directory, select file, call file, call section

F_LS_NA_1         123      Last section, last segment

F_FA_NA_1         124      ACK file, ACK section

F_SG_NA_1         125      Segment

F_DR_TA_1         126      Directory

ASDU_TYPE_127..255  127..255  Reserved (user area)



## Knowledge Base - Interoperability

[IEC 60870-5-101 Protocol Server Interoperability](https://www.freyrscada.com/docs/FreyrSCADA-IEC-60870-5-101-Server-Interoperability.pdf)

[IEC 60870-5-101 protocol Client Interoperability](https://www.freyrscada.com/docs/FreyrSCADA-IEC-60870-5-101-Client-Interoperability.pdf)

 

## Licensing


### [Source Code License model:](https://www.freyrscada.com/iec-60870-5-101-Source-Code-Library.html)

In this License model, We deliver complete source code of the protocol implementation according to the customer specified operating system(Windows, Linux, QNX...).

Customer may embed the library into unlimited copies of Multiple end-use products for worldwide manufacturing, branding and distribution. Original equipment manufacturers choose this model. They usually have multiple products in their pipeline.


### Compiled Library License model:

In this License model, We deliver Dynamic/ Static compiled library (dll / lib) of the protocol implementation according to the customer specified operating system(Windows, Linux, QNX...).

Customer may embed the library into unlimited copies of Multiple end-use products for worldwide manufacturing, branding and distribution. Original equipment manufacturers choose this model. They usually have multiple products in their pipeline.


### Simulator License model:

Annual subscription Based license:

An Annual License allows the customer to use the licensed software for one year, download updates and request technical support. At the end of the year the customer must renew their term license to continue using the software.
In this License model, FreyrSCADA deliver Simulator Installer for Windows Operating System.
The Customer can use the software company wide. Customer can install the software in many systems. There is no restriction like Hardware key (Dongle) and software key. 

Unlimited year license:

A Perpetual License allows the customer to purchase a license to use the software forever. The Perpetual License also comes with an annual renewal fee that enables the customer to update the software to the latest version.
In this License model, FreyrSCADA deliver Simulator Installer for Windows Operating System.
The Customer can use the software company wide. Customer can install the software in many systems. There is no restriction like Hardware key (Dongle) and software key. 
For Unlimited year license, after a year, you will have the option to renew the Maintenance Plan to continue receiving technical support and upgrades.  The renewal price after a year is 10% of the product list price at the time of renewal (optional). Without renew the AMC also the software works. But for technical support and upgrades, the customer has an option for AMC.



# [IEC 60870-5 part 101 Protocol Video Tutorial](https://www.youtube.com/playlist?list=PL4tVfIsUhy1bx7TVjtZnqFB6tbZBhOlJP)

## [IEC 60870-5-101 Protocol Product Description Video](https://www.freyrscada.com/iec-60870-5-101-video.html)	
[![IEC 60870-5-101 Protocol Product Description Video](https://www.freyrscada.com/images/iec101videoicon.jpg)](https://www.freyrscada.com/iec-60870-5-101-video.html)

## [IEC 60870-5-101 Protocol Server Simulator test with third party tool](https://www.freyrscada.com/IEC101_Server_Simulator_Testing.html)	
[![IEC 60870-5-101 Protocol Server Simulator test with third party tool](https://www.freyrscada.com/images/iec101-server-simulator-testing.jpg)](https://www.freyrscada.com/IEC101_Server_Simulator_Testing.html)

## [IEC 60870-5-101 Protocol Client Master Simulator test with third party tool](https://www.freyrscada.com/IEC101_Client_Simulator_Testing.html)	
[![IEC 60870-5-101 Protocol Client Master Simulator test with third party tool](https://www.freyrscada.com/images/iec101-client-simulator-testing.jpg)](https://www.freyrscada.com/IEC101_Client_Simulator_Testing.html)

## [IEC 60870-5-101 Protocol Server and Client Simulator - File Transfer, Directory command operation](https://www.freyrscada.com/IEC-60870-5-101-Server-Client-File-Transfer-video.html)	
[![IEC 60870-5-101 Protocol Server and Client Simulator - File Transfer, Directory command operation](https://www.freyrscada.com/images/iec101-simulator-filetransfer.jpg)](https://www.freyrscada.com/IEC-60870-5-101-Server-Client-File-Transfer-video.html)

## [IEC 60870-5-101 Protocol Server Simulator with Kepware OPC](https://www.freyrscada.com/IEC101_Server_Simulator_Kepware_OPC.html)	
[![IEC 60870-5-101 Protocol Server Simulator with Kepware OPC](https://www.freyrscada.com/images/IEC101_Server_Simulator_Kepware_OPC.jpg)](https://www.freyrscada.com/IEC101_Server_Simulator_Kepware_OPC.html)

## [IEC 60870-5-101 Protocol Server in Beaglebone Arm Linux](https://www.freyrscada.com/IEC101_Server_Beaglebone_Arm_Linux.html)	
[![IEC 60870-5-101 Protocol Server in Beaglebone Arm Linux](https://www.freyrscada.com/images/IEC101_Server_Beaglebone_Arm_Linux.jpg)](https://www.freyrscada.com/IEC101_Server_Beaglebone_Arm_Linux.html)

## [IEC 101 RTU IED Server Simulator testing with Matrikon OPC](http://www.freyrscada.com/IEC101_Server_Simulator-Matrikon-OPC.html)	
[![IEC 101 RTU IED Server Simulator testing with Matrikon OPC](http://www.freyrscada.com/images/iec101-matrikon-opc-with-sub.JPG)](http://www.freyrscada.com/IEC101_Server_Simulator-Matrikon-OPC.html)




[facebook](https://www.facebook.com/IEC101/)

[linkedin](https://in.linkedin.com/showcase/iec-60870-5-101)  

[youtube](https://www.youtube.com/playlist?list=PL4tVfIsUhy1bsVPrJVW4nknHozdfcWE5u)

[twitter](https://twitter.com/FreyrScada)

[pinterest](https://in.pinterest.com/FreyrSCADA/iec-60870-5-101-protocol/)

[tumblr](https://freyrscada.tumblr.com)

[blog](https://iec60870-5-101.blogspot.in/)

[telegram](https://t.me/s/iec_60870_5_101_protocol)

[instagram](https://www.instagram.com/explore/tags/iec101_protocol/)


# [Download Evaluation Kit - IEC 101 Protocol Development Bundle](https://www.freyrscada.com/iec-60870-5-101.php#Download-IEC60870-5-101-Development-Bundle)

In the Development Bundle, We included IEC 60870-5 part 101 Protocol Server  Client Simulator, Windows and Linux SDK, C# projects, Doxygen documentation and Raspberry Pi, BeagleBone Demo library.
