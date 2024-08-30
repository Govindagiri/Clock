/******************** (C) COPYRIGHT 2008 DAN ELECTRONICS ********************
* File Name          : App_init.c
* Author             :
* Date               : 15/04/2009
* Description        : This file provides all Application Initialization func.
*****************************************************************************/
#include "main.h"

void INIT_APP(void)
{
  
  while(LL_GPIO_IsInputPinSet(K12_24_GPIO_Port, K12_24_Pin) == RESET)
  {
   SegMult = 0x01;

   DisplayData = BitMap_DATA[DigitCount] << 1;
   for(GP_Counter = 0;GP_Counter < 16; GP_Counter++)
      {
        if(DisplayData & SegMult)SET_DATA; else RST_DATA;
	SET_CLOCK;Delay_Cycles(300);   RST_CLOCK;Delay_Cycles(300);
        SegMult = SegMult << 1;
      };

     NextDigit++;SegMult = 0x01;   
    for(GP_Counter = 0;GP_Counter < 16; GP_Counter++)
      {
        if(DisplayData & SegMult)SET_DATA; else RST_DATA;
	SET_CLOCK; Delay_Cycles(300);   RST_CLOCK;Delay_Cycles(300);
        SegMult = SegMult << 1;
      };
    
      DISABLE_CLOCK();                           				// Turn OFF all ROWS First
      Delay_Cycles(10);								// Delay to remove ghost Image
      SET_LATCH;Delay_Cycles(10); RST_LATCH;					// Set Latch for nect data set
      if(Flag_Intensity == SET)
      {Flag_Intensity = RESET;Sec_Tick = 0;/*INIT_TIMER();*/};                  // Set Intensity
      switch (DigitCount)							// Select Digit & enable
          {
           case 0 : SET_SEG1; NextDigit = 1; break;			        // Display Hour Tenth
	   case 1 : SET_SEG2; NextDigit = 2; break;			        // Display Houm Unit
	   case 2 : SET_SEG3; NextDigit = 0; break;			        // Display Min Tenth
	 };

      DigitCount++;								// Increment Counter
      if(DigitCount >= 3){DigitCount = 0;Flag_CheckTime = SET;};		// if all digits scaned reset

  }; // For Address display at Startup
    
  ModeCounter = 0;
  Clock_Mode = MASTER;
  Flag_SegUpdate = SET;
 
  //if(BKP_ReadBackupRegister(BKP_DR1) == 0xAA
//  if(LL_RTC_BKP_GetRegister(TAMP, LL_RTC_BKP_DR1)== 0xAA)
//   {
//   DayInt = LL_RTC_BKP_GetRegister(TAMP, LL_RTC_BKP_DR2);
//   if(DayInt > 3)DayInt = 0;
//   NightInt = LL_RTC_BKP_GetRegister(TAMP, LL_RTC_BKP_DR3);
//   if(NightInt > 3)NightInt = 2;
//   }
//  else
//   {
//    DayInt = 0;
//    NightInt = 2;
//    };
//  
//  if(LL_RTC_BKP_GetRegister(TAMP, LL_RTC_BKP_DR3) == 'U')Flag_1224 = SET;
//    else Flag_1224 = RESET;
//
//  SLV_HH = RTC_Count / 3600;
//  if(SLV_HH > 7 && SLV_HH < 19)DutyCycle = DayInt;
//   else DutyCycle = NightInt;

  Flag_Intensity = SET;
  NextDigit = 1;
  DISPLAY_ENABLE;
}