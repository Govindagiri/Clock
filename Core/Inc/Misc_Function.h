#ifndef MISC_FUNCTION_H
#define MISC_FUNCTION_H

#ifdef __cplusplus
extern "C"{
#endif






#include "main.h"
  typedef enum
{
 GPS_Time,
 External_RTC
}DateTimeSet_Type;
 
void Set_Data(void);

//void Get_In_Time(void);
 
void Prg_clk(LL_RTC_TimeTypeDef gTime);
void Program_Mode(void);
void Delay_Cycles(unsigned int val);
void App_Init (void);
uint16_t Get_bitmap(char  TempChar);
void Get_In_Time(void);
void Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
//void Set_Time (TIME_STATUS *Time);
uint8_t decToBcd(int val);
int bcdToDec(uint8_t val);
unsigned char Key_Scan(void);
void Get_Ex_Time (void);
void GP_FUNCTION(void);
void GP_Timer(void);
void RTC_SET_DateTime(uint8_t DateTime_Type);
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */