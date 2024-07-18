#ifndef RAM_H
#define RAM_H

#ifdef __cplusplus
extern "C"{
#endif

#include "main.h"

  typedef struct
  {
    unsigned char                       
      HOUR,		                // GPS Hour
      MINUTE,	                        // GPS Minute
      SECOND;	                        // GPS Second
  }typedef_GPS;
  
  
  typedef struct 
  {
    uint8_t 
      seconds,
      minutes,
      hour;    
  } TIME_STATUS ;
  
  
/************************************/
/* DEFINATION FOR LED Inidcator     */
/************************************/
#define RED_BLK           0
#define RED_STB           1
#define GREEN_BLK         2
#define GREEN_STB         3
  

/************************************/
/* KEY DEFINATION FOR Programming   */
/************************************/
  
#define NONE              0
#define TEST_KEY          2
#define GPIO_12_24_KEY    3
#define DEC_KEY		  4
#define INT_KEY           5
#define INC_KEY           6
#define NU                7
#define PRG_KEY           8




/************************************/
/* DEFINATION Clock Progmming       */
/************************************/

#define HH                  1
#define MM                  2
#define HLD                 3
#define INT_DAY             4
#define INT_NIGHT           5
#define BLANK		    10 
#define I		    11
#define d		    12
#define n		    13
#define BLANK		    10 
  

typedef union Key_Status
  {
   unsigned char KeyStatus;
   struct Bits {
                bool PRG   : 1;		// Program Key
                bool INC   : 1;		// Increment Key
                bool DEC   : 1;		// Decrement Key
                bool K1224 : 1;		// 1224 Key
                bool INT   : 1;         // Intensity Programming					
                bool RST   : 1;         // Reset Key State
                };
  }Status;


extern typedef_GPS  GPS;
extern TIME_STATUS  Time;
extern Status        Key;


extern uint16_t
SegMult,
GP_Counter,
DISP_DATA1,
DISP_DATA2;

extern uint8_t 
Temp,
Rx_Count,
Minute_Counter,
Second_counter;
 
extern char 
RTC_Time[10],
GPS_Buffer[100];


extern unsigned short 
ticks ,
RTC_Count,
RcvIn,
Key_Time[4],                            // Key Time Input                                      
Scan_Time;                              // Key Scan Time 






extern _Bool Flag_Toogle; 

extern FlagStatus 
Flag_Second,
Flag_GPSFix,
Flag_GPSDataReady,
Flag_DataReady,
Flag_GPSActive,

Flag_Toggle1,           
Flag_Prog,                              // Flag for Programming Mode
Flag_TEST,                              // Flag for the test key
Flag_KeyPrg,                            // Programming Key Debounce                             
Flag_GPIO_12_24,                        // 12/24 Key Debounce                                
Flag_Intensity;                         // Flag for setting Intensity 




// Variables Defination
extern unsigned char
GPS_DataIn[100],
Rcv_DataIn[100],
RcvCnt_GPS,

DISP_DATA[10],

Key_Entry,                               // Key Entred by User
ModeCounter,                             // Counter to check clock status
Prog_State,                              // Program Mode
Clock_Mode,                              // Clock Mode
DayInt,                                  // Day Time Intensity                                   
NightInt,                                // Night Time Intensity                                 
DutyCycle;                               // Intensity Duty Cycle 


#ifdef __cplusplus
}
#endif
#endif
