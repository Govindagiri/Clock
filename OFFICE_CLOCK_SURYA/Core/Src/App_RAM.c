/******************** (C) COPYRIGHT 2017 EDS INDIA  ********************
* File Name          : App_RAM.c
* Author             : DILEEP SINGH
* Date               : 14/06/2017
* Description        : This file provides all Application Initialization func.
*****************************************************************************/
#include "main.h"

/***********************************
 Display Segments
     D12
D11 .-- . D0
D10 | D6 | D1
D9 .-- . D2
D8 |   | D3
D7 .-- . D4
     D5

 Digit Formation
*************************************/
Status 			Key;   		                                        // Key Structure
RCVR_InitTypeDef     	RcvInput;	                                        // Recieved data structure
 
const int BitMap_DATA[16]={
                           0x7EFF,0x07C00,0x77EC,0x7F8F,0x7D3B,                 // 0,1,2,3,4
			   0x5FBF,0x5FFF,0x7C0F,0x7FFF,0x7FBF,                  // 5,6,7,8,9
			   0x0000,0x01F0,0xFFC0,0x3BB0,0x71FF,                  //  ,I,d,n,P
                           0x46FF,                                              // C,
                           };

/*********************** FLAG STATUS ******************************************/
FlagStatus
Flag_Tim_tick,//
Flag_Communication,//
Flag_GPSFix,
Flag_Keyscan,
Flag_mSick,
Flag_KeyPrg,                                    // Programming Key Debounce
Flag_Key1224,                                   // 12/24 Key Debounce
Flag_1224_self,
Flag_1224_Com,
Flag_Second,		                        // Flag @ predefined time Interval
Flag_Toggle,                                    // Flag to toggle LED
Flag_SegReady,                                  // Segment data Ready for display
Flag_DigitScan,	                                // Scan Column for next data
Flag_SegUpdate,                                 // Update Segemnt with Next Data
Flag_SLAVE,                                     // Flag to access Slave
Flag_MASTER,                                    // Flag to access Master
Flag_Prog,                                      // Flag for Programming Mode
Flag_1224,                                      // Flag for 12/14 mode
Flag_Intensity,                                 // Flag for setting Intensity
Flag_GPSActive,                                 // GPS Data Valid
Flag_RCVActive,                                 // Recieved Dat Valid
Flag_DataReady,                                 // New Data Arrived
Flag_GPSDataReady,                              // GPS Data Avilable
Flag_CheckTime,                                 // Check Time of Master Clock
Flag_Init,                                      // Initialization
Flag_RCVDataReady;   	                        // Recieved Data Avilable

// Variables Defination
unsigned char

GNSS_Buffer[150],

Comm_TimeOut,
Save_Time,

GPS_DataIn[GPS_BufferSize],                                                     // GPS Input Buffer
Rcv_DataIn[DATA_BufferSize],                                                    // Reciever Buffer
TxBuffer[25],                                                                   // Data to be transmitted

Clock_Mode,             // Clock Mode
ModeCounter,            // Counter to check clock status
ReCheck_Time,           // Recheck GPS avalibility

LED_Color,              // Mode LED indicator

Display_RAM[6],         // Data to be displayed

DISP_HH,		// For displaying Hour

GPS_HH,			// GPS Hour
GPS_MM,			// GPS Minute
GPS_SS,			// GPS Second

RCV_HH,                 // Recieved Data Hour
RCV_MM,                 // Recieved Data Min
RCV_SS,                 // Recieved Data Second

MST_HH,			// Master Hour
MST_MM,			// Master Minute
MST_SS,			// Master Second

SLV_HH,			// Slave Hour
SLV_MM,			// Slave Minute
SLV_SS,			// Slave Second

PRG_HH,                 // Program Hour
PRG_MM,                 // Program Minute

Old_SS,			// Previous Second Value

Key_State,              // Variable for Key Scan
Key_Entry,              // Key Entred by User

Prog_State,             // Program Mode

DayInt,                 // Day Time Intensity
DayInt_self,
DayInt_Com,

NightInt,               // Night Time Intensity
NightInt_self,
NightInt_Com,

DutyCycle,              // Intensity Duty Cycle

RcvState_GPS,		// GPS Reciever State
RcvState,               // Clock Reciever State

NextDigit,              // Next Digit to be scaned

BoardAddress,		// Board Physical Address

RcvCnt_GPS,		// Reciever Counter for Recieving GPS Data
RcvCnt,			// Reciever Counter for recieving data

DigitCount;		// Didit Scan Count



unsigned short
Tick,                                                                           // 1 MILI SECOND TICK
SegMult,                // Segment multiplier for scanning
DigitDisplay[2],        // Data to be displayed

Key_Time[4],             // Key Time Input

crc,                    // CRC for verifiation
Sec_Tick,               // Second Tick Counter

DisplayData,            // Data to Be displayed

Scan_Time,              // Key Scan Time


GP_Counter;		// General Purpose Counter

unsigned long
RTC_Count;              // Counter for Slave RTC

uint8_t Duty_Count = 0;