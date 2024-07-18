#include "App_RAM.h"





/***********************************STRUCTURE**********************************/


typedef_GPS    GPS;
TIME_STATUS    Time; 
Status 	Key;   		                 // Key Structure


/************************************uint16_t**********************************/


uint16_t
SegMult = 0,
GP_Counter = 0,
DISP_DATA1 = 0,
DISP_DATA2 = 0;


/************************************uint8_t***********************************/


uint8_t 
Temp,
Rx_Count = 0,
Minute_Counter = 0,
Second_counter = 0;


/***************************************char***********************************/


char 
RTC_Time[10],
GPS_Buffer[100];

 
/***********************************unsigned short*****************************/

unsigned short 
ticks = 0,
RTC_Count,
RcvIn,


Key_Time[4],                             // Key Time Input                                      
Scan_Time;                               // Key Scan Time                                        

/*********************************Flag Status**********************************/


FlagStatus 
Flag_Second,                             // Flag @ predefined time Interval
Flag_GPSFix,                             // Flag for GPS Fixing
Flag_GPSDataReady,                       // GPS Data Available
Flag_DataReady,                          // New Data Arrived
Flag_GPSActive,                          // Flag for GPS activation

Flag_Prog,                               // Flag for Programming Mode
Flag_TEST,                               // Flag for Test
Flag_KeyPrg,                             // Programming Key Debounce                             
Flag_GPIO_12_24,                         // 12/24 Key Debounce                                
Flag_Intensity,                          // Flag for setting Intensity                           
Flag_Toggle1;   



/****************************************Bool**********************************/


_Bool Flag_Toogle;                       // Flag for toggle


/*************************************unsigned char ***************************/


unsigned char
GPS_DataIn[100],                          // GPS Input Buffer
Rcv_DataIn[100],                          // Reciever Buffer
RcvCnt_GPS,

Key_Entry,                                // Key Entred by User
Prog_State,                               // Program Mode
DISP_DATA[10],                            // Display Data buffer                                       
DayInt,                                   // Day Time Intensity                                   
NightInt,                                 // Night Time Intensity                                 
DutyCycle;                                // Intensity Duty Cycle                                 

