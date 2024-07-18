#include "main.h"

/* Structure */

 LL_RTC_TimeTypeDef gTime;

/*******************************************************************************
FUNCTION NAME   : Set_Data
DESCRIPTION     : LCD DATA BITS SCANNING
INPUT           : NONE
OUTPUT          : NONE
*******************************************************************************/
void Set_Data(void)
{
  uint16_t SegMult = 0x01, 
  DISP_DATA[10];
  char hour[3], minute[3]; 
  
  /*---------- extracting hour minute second from RTC_Time Buffer -------*/
  /*sscanf(RTC_Time, "%2s:%2s:%2s", hour, minute, second);*/
   sscanf(RTC_Time, "%2s:%2s", hour, minute);
  
  /* taking bitmap of hour , minute */
  for (int i = 0 ; i < 2; i++)
  {
    DISP_DATA[i]  = Get_bitmap(hour  [i]);
    DISP_DATA[i+2]= Get_bitmap(minute[i]); 
  //DISP_DATA[i+4]= Get_bitmap(second[i]);
  }
  /** Description :- each controller having 2 8-bit shift register or we can consider each controller caring 16-bit shift  register. 
  hour minute  (for each digit we have 16 bit register)
  H   H     M   M   
  16-16bit 16-16bit shift register

  so total bit that need to send on shift register is 16x4.
  **/
  
  /* sending bit to the sift register */
  for(int i = 0 ; i < 4 ; i ++)
  {
    SegMult = 0x01;
    for(GP_Counter = 0;GP_Counter < 16; GP_Counter++)                           
    {
       if(DISP_DATA[i] & SegMult) SET_DATA; else RST_DATA;                       /* Compare with Multiplier */ // TBD
      Delay_Cycles(100);
      SET_CLK; Delay_Cycles(100); 
      RST_CLK; Delay_Cycles(100);			                        /* Set Clock Pulse */
      SegMult = SegMult << 1;							/* LEft Shift Multilplier */
    };
  }
  
  SET_LATCH; /* making latch pin high*/
  Delay_Cycles(100);
  RST_LATCH; /* making latch pin low*/
}




/*******************************************************************************
* Function Name  : Delay_Cycles
* Description    : Insert Delay of cycles
* Input          : val Number of cycle
* Output         : None
* Return         : None
*******************************************************************************/

void Delay_Cycles(unsigned int val)
{
  while(val) /*checking val*/
  {
    __NOP(); /*no operation perform */
    val--;   /*subtracting input value */
  };
}

/*******************************************************************************
* Function Name  : App_Init
* Description    : Initialize the basic functionality 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void App_Init (void)
{
  /* structure */
  LL_RTC_TimeTypeDef sTime = {0};
  
  /* Enable the Display*/
  DISP_ENB;
  
  /* taking time from External RTC ic */
 Get_Ex_Time();

  /* SET time in internal RTC  from Ex RTC ic*/
 
  sTime.Hours   = Time.hour;
  sTime.Minutes = Time.minutes;
  sTime.Seconds = Time.seconds;
  
  /* A function to set INTERNAL RTC time */
  
  LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BIN, &sTime);
  
  /* A function to set INTERNAL RTC  Dat*/
  
 
}
  
/*******************************************************************************
* Function Name  : Get_bitmap
* Description    : taking the bitmap of number
* Input          : number to display 
* Output         : None
* Return         : None
*******************************************************************************/

uint16_t Get_bitmap(char  TempChar)
{
  uint16_t BITMAP_VAL;
  switch(TempChar)
  {
    case '0' :{BITMAP_VAL = 0x7FFE;break;}/*0*/
    case '1' :{BITMAP_VAL = 0xF8  ;break;}/*1*/
    case '2' :{BITMAP_VAL = 0x6FB9;break;}/*2*/
    case '3' :{BITMAP_VAL = 0x6BF9;break;}/*3*/
    case '4' :{BITMAP_VAL = 0x38F9;break;}/*4*/
    case '5' :{BITMAP_VAL = 0x7BE9;break;}/*5*/
    case '6' :{BITMAP_VAL = 0x7FEF;break;}/*6*/
    case '7' :{BITMAP_VAL = 0x60F8;break;}/*7*/
    case '8' :{BITMAP_VAL = 0x7FFF;break;}/*8*/
    case '9' :{BITMAP_VAL = 0x7BFF;break;}/*9*/
  } 
  return BITMAP_VAL;
}

/*******************************************************************************
* Function Name  : Get_RTC_Time
* Description    : taking time from internal RTC
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void Get_In_Time(void) 
{ 

  /* Get the RTC current Time */ 
   LL_RTC_TIME_Get(RTC);
 
  /* Display time Format: hh:mm */ 
  sprintf((char*)RTC_Time,"%02d:%02d",gTime.Hours, gTime.Minutes);
  
  /* Display time Format: hh:mm:ss */ 
  /*sprintf((char*)RTC_Time,"%02d:%02d:%02d",gTime.Hours, gTime.Minutes, gTime.Seconds)*/ 
 
  /* Display date Format: dd-mm-yy 
  sprintf((char*)RTC_Date,"%02d-%02d-%2d",gDate.Date, gDate.Month, 2000 + gDate.Year); */
}
 

/*******************************************************************************
* Function Name  : Get_Time
* Description    : Taking From external rtc  
* Input          : None
 * Output        : None
* Return         : None
*******************************************************************************/

void Get_Ex_Time (void)
{
   Time.hour       = Read_RTC(RTC_HH_REG);/* HOUR       */
   Time.minutes    = Read_RTC(RTC_MM_REG);/* MINUTE     */
   Time.seconds    = Read_RTC(RTC_SS_REG);/* SECOND     */
   
   /*
   Time.dayofweek  = Read_RTC(RTC_DD_REG);//DAY OF WEEK
   Time.dayofmonth = Read_RTC(RTC_DT_REG);//DAY        
   Time.month      = Read_RTC(RTC_MH_REG);//MONTH      
   Time.year       = Read_RTC(RTC_YY_REG);//YEAR       
  */
}

/*******************************************************************************
* Function Name  : Program_Clock
* Description    : Program Master & Slave Clock
* Input          : GPS STRUCTURE
* Output         : None
* Return         : None
*******************************************************************************/

void Program_Clock(typedef_GPS *GPS)
{
  // Prograsm RTC IC Clock
  Write_RTC(RTC_SS_REG,GPS->SECOND);    /* SECOND */
  Write_RTC(RTC_MM_REG,GPS->MINUTE);    /* MINUTE */
  Write_RTC(RTC_HH_REG,GPS->HOUR);      /* HOUR   */
  
  
  /***************For Date*********************/
  /*
  Write_RTC(RTC_DT_REG,GPS->DAY);    // DAY    
  Write_RTC(RTC_MH_REG,GPS->MONTH);  // MONTH  
  Write_RTC(RTC_YY_REG,GPS->YEAR);   // YEAR 
*/  
  /********************************************/
 }

  
 /*******************************************************************************
* Function Name  : GP_Timer
* Description    : Calling this function every second and taking internal 
*                  and externalm RTC time
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
 void GP_Timer(void)
 {
   LL_IWDG_ReloadCounter(IWDG);
   /* FLAg_second reset FLag */
   Flag_Second = RESET;                     
   
   /* taking internal RTC TIME */
   Get_In_Time();   
   
   /* TAKING TIME FROM External RTC IC*/
   Get_Ex_Time();                               
   
   /* CHECKING GPS IS AVAILABLE OR NOT */
   if(Flag_GPSDataReady == SET)
   {
     /* extracting time from string */
     GPS.HOUR   = (GPS_DataIn[0] - '0')*10 + GPS_DataIn[1]  - '0';
     GPS.MINUTE = (GPS_DataIn[2] - '0')*10 + GPS_DataIn[3]  - '0';
     GPS.SECOND = (GPS_DataIn[4] - '0')*10 + GPS_DataIn[5]  - '0';
     
     /****************extracting date from string ***************/
     /*
     GPS.DAY    = (GPS_DataIn[50]- '0')*10 + GPS_DataIn[51] - '0';
     GPS.MONTH  = (GPS_DataIn[52]- '0')*10 + GPS_DataIn[53] - '0';
     GPS.YEAR   = (GPS_DataIn[54]- '0')*10 + GPS_DataIn[55] - '0';*/
     
     /***********************************************************/
     
     /* changing time in Indian format by adding time (+ 5:30) */
     if (GPS.HOUR < 24 && GPS.MINUTE < 60)
     {
       GPS.HOUR += 5;
       GPS.MINUTE += 30;
       if(GPS.MINUTE > 59){GPS.MINUTE -= 60;GPS.HOUR++;};
       if(GPS.HOUR > 23)GPS.HOUR -= 24;
       Flag_GPSActive = SET;
     }
     
     if(Second_counter == 0)
     {
       /*assigning minute value*/
       Second_counter = 60;
       
       if((Time.hour != GPS.HOUR) || (Time.minutes != GPS.MINUTE) || (Time.seconds != GPS.SECOND))
       {
         Program_Clock(&GPS);
         RTC_SET_DateTime(GPS_Time);
       }
     }
     Flag_GPSDataReady = RESET;
   }
   else
   {
     if(Minute_Counter == 0)
     {
        /*assigning minute value*/
        Minute_Counter = 2;
        
       /* checking if internal ic time doesn't match with RTC IC time then RTC IC will assign in internal RTC */
       if((gTime.Hours != Time.hour)||( gTime.Minutes != Time.minutes)||( gTime.Seconds != Time.seconds))
       {
         /* SET time in internal RTC  from RTC ic*/
         gTime.Hours   = Time.hour;
         gTime.Minutes = Time.minutes;
         gTime.Seconds = Time.seconds;
         
         /* A function to set time */
         LL_RTC_TIME_Init(RTC,LL_RTC_FORMAT_BIN ,&gTime);
         
         /****** SET Date in internal RTC  from RTC ic*******/
         /*
         gDate.Date    = Time.dayofmonth;
         gDate.Month   = Time.month;
         gDate.Year    = Time.year;*/
         
         
         /***************************************************/
         
       } 
     }
   }
 }
 void RTC_SET_DateTime(uint8_t DateTime_Type)
 {
    if(DateTime_Type == 0)
    {
      gTime.Hours   = GPS.HOUR;
      gTime.Minutes = GPS.MINUTE;
      gTime.Seconds = GPS.SECOND;
      
      /*************************for date**********************/
      /*
      gDate.Date    = GPS.DAY;
      gDate.Month   = GPS.MONTH;
      gDate.Year    = GPS.YEAR;*/
      
      /*******************************************************/
      
    }
    else
    {
      if((gTime.Hours != Time.hour)||( gTime.Minutes != Time.minutes)||( gTime.Seconds != Time.seconds))
       {
         /* SET time in internal RTC  from RTC ic*/
         gTime.Hours   = Time.hour;
         gTime.Minutes = Time.minutes;
         gTime.Seconds = Time.seconds;
         
         /* SET Date in internal RTC  from RTC ic
         gDate.Date    = Time.dayofmonth;
         gDate.Month   = Time.month;
         gDate.Year    = Time.year;*/
       } 
    }

      LL_RTC_TIME_Init(RTC,LL_RTC_FORMAT_BIN ,&gTime);
    if((Time.hour != GPS.HOUR) || (Time.minutes != GPS.MINUTE) || (Time.seconds != GPS.SECOND)){Program_Clock(&GPS);}
 }
 
void Prg_clk(LL_RTC_TimeTypeDef gTime)
{
  // Prograsm Master Clock
  
  //Write_RTC(RTC_SS_REG,Sec);
  Write_RTC(RTC_MM_REG,gTime.Minutes);
  Write_RTC(RTC_HH_REG,gTime.Hours);
  
  // Program Slave Clock
  RTC_Count = Time.hour*3600 + Time.minutes *60 + Time.seconds;
  //RTC_SetCounter(RTC_Count);
  //RTC_WaitForLastTask();
  //RTC_ITConfig(RTC_IT_SEC, ENABLE);
  
 }

/*******************************************************************************
* Function Name  : Key Scan
* Description    : Scan Telephonic Key Board
* Input          : None
* Output         : Key Pressed
* Return         : None
*******************************************************************************/
 
unsigned char Key_Scan(void)
{

unsigned char key_press = 0;

// Keys for Single Press

 if(LL_GPIO_IsInputPinSet(PRG_GPIO_Port, PRG_Pin) == RESET && Flag_KeyPrg == RESET)                                                                     // Checking PRG pin pressed or not
  {
   Flag_KeyPrg = SET;
   // Key.PRG = TRUE;
   key_press = PRG_KEY;
   Scan_Time = 150;
  };
 if(LL_GPIO_IsInputPinSet(PRG_GPIO_Port, PRG_Pin) == SET)Flag_KeyPrg = RESET;
 

 if(LL_GPIO_IsInputPinSet(GPIO_12_24_GPIO_Port, GPIO_12_24_Pin) == RESET /*&& Key.GPIO_12_24 == FALSE*/ && Flag_GPIO_12_24 == RESET)                    // Checking 12/24 pin pressed or not
  {
   Flag_GPIO_12_24 = SET;
   // Key.GPIO_12_24 = TRUE;
   key_press = GPIO_12_24_KEY;
   Scan_Time = 500;
  };
 if(LL_GPIO_IsInputPinSet(GPIO_12_24_GPIO_Port, GPIO_12_24_Pin) == SET)Flag_GPIO_12_24 = RESET;

 
// if(LL_GPIO_IsInputPinSet(TEST_GPIO_Port, TEST_Pin) == RESET /*&& Key.TEST == FALSE*/ && Flag_TEST == RESET)                                            // Checking TEST pin pressed or not
//  {
//   Flag_TEST = SET;
//   // Key.TEST = TRUE;
//   key_press = TEST_KEY;
//   Scan_Time = 500;
//  };
// if(LL_GPIO_IsInputPinSet(TEST_GPIO_Port, TEST_Pin) == SET)Flag_TEST = RESET;

 
// Keys for Multi Press
 
 if(LL_GPIO_IsInputPinSet(INC_GPIO_Port, INC_Pin) == RESET /*&& Key.INC == FALSE*/)                                                                       // Checking INC pin pressed or not
  {
   //Key.INC = TRUE;
   key_press = INC_KEY;
   Scan_Time = 150;
  }

 
 else if(LL_GPIO_IsInputPinSet(DEC_GPIO_Port, DEC_Pin) == RESET /*&& Key.DEC == FALSE*/)                                                                   // Checking DEC pin pressed or not
  {
   //Key.DEC = TRUE;
   key_press = DEC_KEY;
   Scan_Time = 150;
  }
 

 else if(LL_GPIO_IsInputPinSet(INT_GPIO_Port, INT_Pin) == RESET /*&& Key.INT == FALSE*/)                                                                    // Checking INT pin pressed or not
  {
   //Key.INT = TRUE;
   key_press = INT_KEY;
   Scan_Time = 150;
  };

 
return(key_press);
}

/*******************************************************************************
* Function Name  : Program_Mode
* Description    : Programming fo Master Clock
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void Program_Mode(void)
{
  switch (Prog_State)
   {
    case HH : switch(Key_Entry)
                 {
                  case INC_KEY : Key_Entry = NONE; gTime.Hours++;
		                 if(gTime.Hours > 23)gTime.Hours = 0;
		                 break;
		  case DEC_KEY : Key_Entry = NONE; gTime.Hours--;
		                 if(gTime.Hours > 23)gTime.Hours = 23;
		                 break;
                  case PRG_KEY : Key_Entry = NONE;Prog_State = gTime.Minutes;
		                 break;
		  case INT_KEY : Key_Entry = NONE;Prog_State = INT_DAY;
                                 DayInt = DayInt*25;
                                 NightInt = NightInt*25;
                                 if(DayInt == 0)DayInt = 100;
                                 if(NightInt == 0)NightInt = 100;
		                 break;
                  default      : break;	
		  };
              
                 Flag_Toggle1= SET;
                 DISP_DATA[0] = gTime.Hours/10;
                 DISP_DATA[1] = gTime.Hours%10;
		 DISP_DATA[2] = DISP_DATA[3] = BLANK;
                 break;
                 
     case MM : switch(Key_Entry)
                 {
                  case INC_KEY : Key_Entry = NONE; gTime.Minutes++;
		                 if(gTime.Minutes > 59)gTime.Minutes = 0;
		                 break;
		  case DEC_KEY: Key_Entry = NONE; gTime.Minutes--;
		                 if(gTime.Minutes > 59)gTime.Minutes = 59;
		                 break;
                  case PRG_KEY: Key_Entry = NONE;Prog_State = HLD;
		                 break;
		  default      : break;		
		  };
               
                 Flag_Toggle1 = SET;
                 DISP_DATA[2] = gTime.Minutes/10;
                 DISP_DATA[3] = gTime.Minutes%10;
		 break;

    case HLD : if(Flag_Toggle1 == SET)
                   {
		    DISP_DATA[0] = gTime.Hours/10;
                    DISP_DATA[1] = gTime.Hours%10;
		    DISP_DATA[2] = gTime.Minutes/10;
                    DISP_DATA[3] = gTime.Minutes%10;
		   }
		else
		   {
                    DISP_DATA[0] = DISP_DATA[1] = BLANK;
		    DISP_DATA[2] = DISP_DATA[3] = BLANK;
		   };
		
		if(Key_Entry == PRG_KEY)
                {Prg_clk(gTime);
                Flag_Prog = RESET;Key_Entry = NONE;}
		
		break;

 case INT_DAY : switch(Key_Entry)
                 {
                  case INC_KEY : Key_Entry = NONE; DayInt += 25;
		                 if(DayInt > 100)DayInt = 25;
				 break;
		  case DEC_KEY : Key_Entry = NONE; DayInt -= 25;
		                 if(DayInt > 100 || DayInt == 0)DayInt = 100;
				 break;
                  case PRG_KEY : Key_Entry = NONE;Prog_State = INT_NIGHT;
		                 break;
		  default      : break;		
		  };
                
                 Flag_Toggle1 = SET;
                 if(DayInt == 100){DISP_DATA[2] = 9;DISP_DATA[3] = 9; }
		   else {DISP_DATA[2] = DayInt/10;DISP_DATA[3] = DayInt%10; }
                 DISP_DATA[0] = I, DISP_DATA[1] = d;
                 break;		
		
case INT_NIGHT : switch(Key_Entry)
                 {
                  case INC_KEY : Key_Entry = NONE; NightInt += 25;
		                 if(NightInt > 100)NightInt = 25;
				 break;
		  case DEC_KEY : Key_Entry = NONE; NightInt -= 25;
		                 if(NightInt > 100 || NightInt == 0)NightInt = 100;
				 break;
                  case PRG_KEY : Key_Entry = NONE;
		                 LL_RTC_BKP_SetRegister(TAMP, LL_RTC_BKP_DR1, 'N');
				 DayInt = (100 - DayInt)/25;
				 NightInt = (100 - NightInt)/25;
				
				LL_RTC_BKP_SetRegister(TAMP, LL_RTC_BKP_DR2, DutyCycle);
                                  LL_RTC_BKP_SetRegister(TAMP, LL_RTC_BKP_DR3, DutyCycle);
		                 			
				 if(gTime.Hours > 7 && gTime.Hours < 19)DutyCycle = DayInt;
				   else DutyCycle = NightInt;
				 Flag_Intensity = SET;				
				 Flag_Prog = RESET;
		                 break;
		   default      : break;		
		  };
                 
                 Flag_Toggle1 = SET;
                 if(NightInt == 100){DISP_DATA[2] = 9;DISP_DATA[3] = 9; }
		  else {DISP_DATA[2] = NightInt/10;DISP_DATA[3] = NightInt%10; }
		 DISP_DATA[0] = I, DISP_DATA[1] = n;
	          break;	
   };

}

