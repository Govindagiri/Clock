
#include "I2C_RTC.h"

/*******************************************************************************
* Function Name  : INIT_RTC
* Description    : Initialize MASTER RTC
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void INIT_RTC(void)
{
  unsigned char Data_In;
  /* Clear HT bit on power Up*/
  Write_RTC(RTC_A1HH_REG,0x00);
  Data_In = Read_RTC(RTC_SS_REG);
   /* if Stop Bit is SET then Clear */
  if(Data_In > 0x7F)Write_RTC(RTC_SS_REG,(Time.seconds & 0x7F));
  
}


/*******************************************************************************
* Function Name  : Write_RTC
* Description    : Write Data to RTC Register
* Input          : Register address, Data
* Output         : None
* Return         : None
*******************************************************************************/
void Write_RTC(unsigned char RTC_REG,unsigned char RTC_Data)
{
  unsigned char RTC_Data_Out = 0,
                Data_MSB     = 0,
                Data_LSB     = 0;

  Data_MSB = RTC_Data/10;
  Data_LSB = RTC_Data%10;

  RTC_Data_Out = (Data_MSB<<4) + Data_LSB;

  I2C_START();
  Serial_Out(RTC_ADDRESS_Wr); /* device address 11010000 */
  SET_SDA;I2C_ACK();
  Serial_Out(RTC_REG);
  SET_SDA;I2C_ACK();
  Serial_Out(RTC_Data_Out);
  RST_SDA;I2C_ACK();
  I2C_STOP();

  //Delay_1us(10000); // 10 ms delay to write
  HAL_Delay(10);
}


/*******************************************************************************
* Function Name  : Read_RTC
* Description    : Read Data from RTC Register
* Input          : Register address
* Output         : None
* Return         : Register content
*******************************************************************************/
unsigned char Read_RTC(unsigned char RTC_REG)
{
  unsigned char RTC_Data_Out = 0,
                Data_MSB     = 0,
                Data_LSB     = 0;
  unsigned char Data_In;

 /*--------------------- Dummy Write --------------------------*/
  I2C_START();
  Serial_Out(RTC_ADDRESS_Wr);        // device address 11010000 
  SET_SDA;I2C_ACK();
  Serial_Out(RTC_REG);
  SET_SDA;I2C_ACK();

  /*-------------------- Read --------------------------------*/
  I2C_START();
  Serial_Out(RTC_ADDRESS_Rd);        // device address 11010001 
  SET_SDA;I2C_ACK();                 // Ackn

  Data_In = Serial_In();
  SET_SDA;I2C_ACK();                 // No Ack
  I2C_STOP();

  /*-------------------- Convert to BCD -----------------------*/
   Data_MSB = ((Data_In & 0xF0)>>4)*10;
   Data_LSB = Data_In & 0x0F;

   RTC_Data_Out = Data_MSB + Data_LSB;

   if(RTC_Data_Out > 60)RTC_Data_Out = 110; // for blanking Display

 return(RTC_Data_Out);
}
