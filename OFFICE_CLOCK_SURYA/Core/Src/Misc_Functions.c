



#include "main.h"

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
 if(LL_GPIO_IsInputPinSet(PORT_KPRG,KEY_PRG) == RESET && Key.PRG == RESET && Flag_KeyPrg == RESET)
  {
   Flag_KeyPrg = SET;
   Key.PRG = SET;
   key_press = PRG_KEY;
   
  };
 if(LL_GPIO_IsInputPinSet(PORT_KPRG,KEY_PRG) == SET)Flag_KeyPrg = RESET;

 if(LL_GPIO_IsInputPinSet(K12_24_GPIO_Port,K12_24_Pin) == RESET && Key.K1224 == RESET && Flag_Key1224 == RESET)
{
   Flag_Key1224 = SET;
   Key.K1224 = SET;
   key_press = K1224_KEY;
   
  };
 if(LL_GPIO_IsInputPinSet(K12_24_GPIO_Port,K12_24_Pin) == SET)Flag_Key1224 = RESET;

 // Keys for Multi Press
 if(LL_GPIO_IsInputPinSet(PORT_KINC,KEY_INC) == RESET && Key.INC == RESET)
  {
   Key.INC = SET;
   key_press = INC_KEY;  
  }

 else if(LL_GPIO_IsInputPinSet(PORT_KDEC,KEY_DEC) == RESET && Key.DEC == 0)
  {
   Key.DEC = SET;
   key_press = DEC_KEY;
   
  }
 else if(LL_GPIO_IsInputPinSet(PORT_KINT,KEY_INT) == RESET && Key.INT == 0)
  {
   Key.INT = SET;
   key_press = INT_KEY;
   
  };

return(key_press);
 
}
/*******************************************************************************
* Function Name  : Program Clock
* Description    : Program Master & Slave Clock
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Program_Clock(unsigned char Hour, unsigned char Min, unsigned char Sec)
{
 // Prograsm Master Clock
  Write_RTC(RTC_SS_REG,Sec);
  Write_RTC(RTC_MM_REG,Min);
  Write_RTC(RTC_HH_REG,Hour);

  // Program Slave Clock
//  RTC_ITConfig(RTC_IT_SEC, DISABLE);
//  RTC_Count = Hour*3600 + Min*60 + Sec;
//  RTC_SetCounter(RTC_Count);
//  RTC_WaitForLastTask();
//  RTC_ITConfig(RTC_IT_SEC, ENABLE);

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
  ModeCounter = 0;
  if(LL_GPIO_IsInputPinSet(PORT_LED_GRN,LED_GRN) == SET){RST_GRN;SET_RED;}
  else {RST_RED;SET_GRN;};
  switch (Prog_State)
   {
    case HOUR : switch(Key_Entry)
                 {
                  case INC_KEY : Key_Entry = NONE; PRG_HH++;
		                 if(PRG_HH > 23)PRG_HH = 0;
		                 break;
		  case DEC_KEY : Key_Entry = NONE; PRG_HH--;
		                 if(PRG_HH > 23)PRG_HH = 23;
		                 break;
                  case PRG_KEY : Key_Entry = NONE;Prog_State = MIN;
		                 break;
		  case INT_KEY : Key_Entry = NONE;Prog_State = INT_DAY;
                                 DayInt = (4 - DayInt)*25;
                                 NightInt = (4 - NightInt)*25;
                                 if(DayInt == 0)DayInt = 100;
                                 if(NightInt == 0)NightInt = 100;
		                 break;
                  default      : break;				
		  };
                 Flag_Toggle = SET;
                 Display_RAM[0] = PRG_HH/10;Display_RAM[1] = PRG_HH%10;
		 Display_RAM[2] = Display_RAM[3] = BLANK;
                 break;
     case MIN : switch(Key_Entry)
                 {
                  case INC_KEY : Key_Entry = NONE; PRG_MM++;
		                 if(PRG_MM > 59)PRG_MM = 0;
		                 break;
		  case DEC_KEY : Key_Entry = NONE; PRG_MM--;
		                 if(PRG_MM > 59)PRG_MM = 59;
		                 break;
                  case PRG_KEY : Key_Entry = NONE;Prog_State = HOLD;
		                 break;
		  default      : break;		
		  };
                 Flag_Toggle = SET;
                 Display_RAM[2] = PRG_MM/10;Display_RAM[3] = PRG_MM%10;
		         break;

    case HOLD : if(Flag_Toggle == SET)
                   {
		    Display_RAM[0] = PRG_HH/10;Display_RAM[1] = PRG_HH%10;
		    Display_RAM[2] = PRG_MM/10;Display_RAM[3] = PRG_MM%10;
		   }
		else
		   {
                    Display_RAM[0] = Display_RAM[1] = BLANK;
		    Display_RAM[2] = Display_RAM[3] = BLANK;
		   };
		
		if(Key_Entry == PRG_KEY){Program_Clock(PRG_HH,PRG_MM,0);Flag_Prog = RESET;Key_Entry = NONE;}
		
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
                 Flag_Toggle = SET;
                 if(DayInt == 100){Display_RAM[2] = 9;Display_RAM[3] = 9; }
		   else {Display_RAM[2] = DayInt/10;Display_RAM[3] = DayInt%10; }
                 Display_RAM[0] = I, Display_RAM[1] = d;

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
		                 
		
				 DayInt = (100 - DayInt)/25;
				 NightInt = (100 - NightInt)/25;
				
				 	
				 if(PRG_HH > 7 && PRG_HH < 19)DutyCycle = DayInt;
				 else DutyCycle = NightInt;
				 Flag_Intensity = SET;				
				 Flag_Prog = RESET;
                                 
                                 DayInt_self = DayInt;
                                 NightInt_self = NightInt;
                                 Save_Time = 5;
		                 break;
		   default      : break;		
		  };
                 Flag_Toggle = SET;
                 if(NightInt == 100){Display_RAM[2] = 9;Display_RAM[3] = 9; }
		  else {Display_RAM[2] = NightInt/10;Display_RAM[3] = NightInt%10; }
		 Display_RAM[0] = I, Display_RAM[1] = n;
                 
                
	          break;	
   };

}

/*******************************************************************************
* Function Name  : Manage_RcvData
* Description    : Manage recieved data
* Input          : none
* Output         : None
* Return         : None
*******************************************************************************/


void Manage_RcvData(void)
 {

   switch(RcvInput.Code)
	 {
	  case LNK_CHK :  memset(TxBuffer,0,10);
                          //SET_RxTx;
	                  TxBuffer[0] = 0xAA;TxBuffer[1] = 0xCC;                // Header
			  TxBuffer[2] = 4;TxBuffer[3] = BoardAddress;           // Length & Source
			  TxBuffer[4] = 0x00;                                   // Destination Master Clock
			  TxBuffer[5] = LNK_CHK;                                // Code - Link Check
			  TxBuffer[6] = 0x80 | (DutyCycle + 1);                 // Link & Duty Cycle
			  /* DMA Buffer Size */
			  //DMA1_Channel7->CNDTR = 7;
			  /* Enable DMA1 Channel7 */
			 // DMA_Cmd(DMA1_Channel7, ENABLE);
			  break;
			
	  case SET_CFG  : DayInt = Rcv_DataIn[0];
                          if(DayInt > 3)DayInt_Com = 0;
			  NightInt = Rcv_DataIn[1];
                          if(NightInt > 3)NightInt_Com = 2;

			  
                           
			  if(Clock_Mode == MASTER)
			   {
			    if(MST_HH > 7 && MST_HH < 19)DutyCycle = DayInt;
			    else DutyCycle = NightInt;
			   }
			  else if(Clock_Mode == SLAVE)
			   {
			    if(SLV_HH > 7 && SLV_HH < 19)DutyCycle = DayInt;
			      else DutyCycle = NightInt;
			   }
                          
                           DayInt_Com = DayInt;
                           NightInt_Com = NightInt;
                            Save_Time = 5;
			  Flag_Intensity = SET;	
			  break;
	
			
     };// End of Switch
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
  while(val)
    {
     __NOP();
     val--;
    };
}

/*******************************************************************************
* Function Name  : DISABLE_ROW
* Description    : Disable All Rows
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void DISABLE_CLOCK(void)
{
 RST_SEG2;
 RST_SEG3;
 RST_SEG1;
}

/*******************************************************************************
* Function Name  : GP_Timer
* Description    : General Purpose TImer Decrements every 1 second
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GP_Timer(void)
 {
   if(Save_Time)Save_Time--;   
   if(Save_Time == 1) Write_Config();
   
  if(ReCheck_Time)ReCheck_Time--;                                               // Re check for Mode
  else
   {
    if(Flag_Init == SET)
    {
      Flag_Init = RESET;
      Flag_Intensity = SET;
    };
 
    ReCheck_Time = 5;
    Flag_GPSActive = RESET;Flag_RCVActive = RESET;
    if(Flag_GPSDataReady == SET)
     {
      Flag_GPSDataReady = RESET;

      GPS_HH = (GPS_DataIn[0]- '0')*10 + GPS_DataIn[1] - '0';
      GPS_MM = (GPS_DataIn[2]- '0')*10 + GPS_DataIn[3] - '0';
      GPS_SS = (GPS_DataIn[4]- '0')*10 + GPS_DataIn[5] - '0';
      
         
      if((Flag_1224_Com == RESET) && (Rcv_DataIn[6] == 'U')){Flag_1224_Com = SET; Save_Time = 5;}
      else if((Flag_1224_Com == SET) && (Rcv_DataIn[6] != 'U')){Flag_1224_Com = RESET; Save_Time = 5;}
      
      
       if (GPS_HH < 24 && GPS_MM < 60)
	{
	 GPS_HH += 5;GPS_MM += 30;
         if(GPS_MM > 59){GPS_MM -= 60;GPS_HH++;};
         if(GPS_HH > 23)GPS_HH -= 24;
         if(Clock_Mode == MASTER)
          {
          MST_MM = Read_RTC(RTC_MM_REG);
          MST_HH = Read_RTC(RTC_HH_REG);
          if(GPS_HH != MST_HH || GPS_MM != MST_MM)Program_Clock(GPS_HH,GPS_MM,GPS_SS);
	  }
         else
          {
           SLV_MM = (RTC_Count % 3600) / 60;
           SLV_HH = RTC_Count / 3600;
           if(GPS_HH != SLV_HH || GPS_MM != SLV_MM)Program_Clock(GPS_HH,GPS_MM,GPS_SS);
           Clock_Mode = MASTER;
          };
          Flag_GPSActive = SET;
          GPS_DataIn[11] = 'V';
        };
     }
    else if(Flag_RCVDataReady == SET)
     {
      Flag_RCVDataReady = RESET;
      RCV_HH = Rcv_DataIn[0]*10 + Rcv_DataIn[1];
      RCV_MM = Rcv_DataIn[2]*10 + Rcv_DataIn[3];
      RCV_SS = Rcv_DataIn[4]*10 + Rcv_DataIn[5];
      
      if((Flag_1224_Com == RESET) && (Rcv_DataIn[6] == 'U')){Flag_1224_Com = SET; Save_Time = 5;}
      else if((Flag_1224_Com == SET) && (Rcv_DataIn[6] != 'U')){Flag_1224_Com = RESET; Save_Time = 5;}
      
      if (RCV_HH < 24 && RCV_MM < 60)
	{
	 if(Clock_Mode == MASTER)
          {
          MST_MM = Read_RTC(RTC_MM_REG);
          MST_HH = Read_RTC(RTC_HH_REG);
          if(RCV_HH != MST_HH || RCV_MM != MST_MM)Program_Clock(RCV_HH,RCV_MM,RCV_SS);
	  }
         else
          {
           SLV_MM = (RTC_Count % 3600) / 60;
           SLV_HH = RTC_Count / 3600;
           if(RCV_HH != SLV_HH || RCV_MM != SLV_MM)Program_Clock(RCV_HH,RCV_MM,RCV_SS);
           Clock_Mode = MASTER;
          };
         Flag_RCVActive = SET;
        };
     };
   };


 ModeCounter++;                                                                 // Check Mode of Clock
  if(ModeCounter > 5)                                                           // If not reset by clock mode for 6 times
     {
      if(Clock_Mode < SLAVE)Clock_Mode = SLAVE;
      ModeCounter = 0;                                                          //  Reset Mode Counter
     };
 }



void Key_Function(void)
{
  if (Key_Entry == PRG_KEY && Flag_Prog == RESET)
     {
       if(Clock_Mode == MASTER){PRG_HH = MST_HH; PRG_MM = MST_MM;}
        else {PRG_HH = SLV_HH; PRG_MM = SLV_MM;}
       Prog_State = HOUR;
       Flag_Prog = SET;
       Key_Entry = NONE;
       Key.RST = SET;
       Sec_Tick = 0;
     }
    else if(Key_Entry == K1224_KEY)
     {
      if(LL_GPIO_IsInputPinSet(K12_24_GPIO_Port,K12_24_Pin) == RESET)
        { 
        if(Flag_1224_self == SET)Flag_1224_self = RESET;
        else Flag_1224_self = SET; 
        
        Save_Time = 5;
        Key.RST = SET;Sec_Tick = 0;
        };
     }
    else if(Key_Entry == INT_KEY && Flag_Prog == RESET)
     {
      DutyCycle ++;
      if(DutyCycle > 3)DutyCycle = 0;
      if(Clock_Mode == MASTER)
       {
        if(MST_HH > 7 && MST_HH < 19)DayInt = DutyCycle;
         else NightInt = DutyCycle;
         
       }
      else if(Clock_Mode == SLAVE)
       {
        if(SLV_HH > 7 && SLV_HH < 19)DayInt = DutyCycle;
          else NightInt = DutyCycle;
       }
       
      
      DayInt_self = DayInt;
      NightInt_self = NightInt;
      Save_Time = 5; 
      Flag_Intensity = SET;
      Key.RST = SET;Sec_Tick = 0;
     };
}
/*******************************************************************************
* Function Name  : Get_Config
* Description    : Get The Configuration Values
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Get_Config(void)
  {
    unsigned short FlashData;
   
     uint32_t FlashAddress;
    /****** FLASH READING *****************************************************/
    FlashAddress = EndAddr-FLASH_PAGE_SIZE; 
    FlashData = (*(uint32_t*) FlashAddress);FlashAddress += 2;                      // VERIFY FLASH DATA 
    if(FlashData == 0x00ED)                                                     // Signature Byte
    {
      // communication 
      /*----- SERVER HIT TIMES--------------------------------------------------*/ 
      DayInt_Com        = 0x0000FFFF & (*(uint32_t*) FlashAddress);FlashAddress += 2;       // DAY TIME INTENSITY OF MASTER COMMUNICATION 
      NightInt_Com      = 0x0000FFFF & (*(uint32_t*) FlashAddress);FlashAddress += 2;       // NIGHT TIME INTENSITY OF MASTER COMMUNICATION 
      FlashData         = 0x0000FFFF & (*(uint32_t*) FlashAddress);FlashAddress += 2;       // CLOCK TIME FORMAT OF MASTER COMMUNICATION 
      if(FlashData == 1)Flag_1224_Com = SET;
      else Flag_1224_Com = RESET;
      
      // self setting 
      DayInt_self    = 0x0000FFFF & (*(uint32_t*) FlashAddress);FlashAddress += 2;      // SELF DAY TIME INTENSITY
      NightInt_self  = 0x0000FFFF & (*(uint32_t*) FlashAddress);FlashAddress += 2;      // SELF NIGHT TIME INTENSITY
      FlashData      = 0x0000FFFF & (*(uint32_t*) FlashAddress);FlashAddress += 2;     // SELF SET CLOCK TIME FORMET
      if(FlashData == 1)Flag_1224_self = SET;
      else Flag_1224_self = RESET;
    }
    else 
    {
      DayInt = 0; 
      NightInt = 2; 
      Flag_1224 = RESET;
        
      DayInt_Com        = 0;
      NightInt_Com      = 2;
      Flag_1224_Com     = RESET;
      
      DayInt_self        = 0;
      NightInt_self      = 2;
      Flag_1224_self     = RESET;
      
      Write_Config();
    }
  }
  
/*******************************************************************************
* Function Name  : Write_Default
* Description    : Write Default Data in Flash Memory
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Write_Config(void){}
//  {
//    unsigned short FlashData;
//    volatile uint32_t FLASHStatus;
//    uint32_t FirstPage = 0, NbOfPages = 0;
//    uint32_t Address = 0, PageError = 0;
//    __IO uint32_t data32 = 0 , MemoryProgramStatus = 0;
//    uint32_t FlashAddress;
//    
//    FLASH_EraseInitTypeDef EraseInitStruct;
//    /*---- UNLOCK THE FLASH PROGRAM ERASE CONTROLLER ----------------------------*/
//    HAL_FLASH_Unlock();								// UNLOCK FLASH
//      
//    /*----- CLEAR ALL PENDING FLAGS ---------------------------------------------*/
//    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGAERR | FLASH_FLAG_WRPERR);	
//    FlashAddress = Flash_ADD;
//    
//    /*----- ERASE THE FLASH PAGES -----------------------------------------------*/				        // ERASE FLASH PAGES 
//  FLASH_PageErase(FLASH_BANK_1, ((FlashAddress - FLASH_BASE) / FLASH_PAGE_SIZE));
//  if (FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE) == HAL_OK) {}
// 
//    
//    /*----- FLASH HALFWORD PROGRAM ----------------------------------------------*/
//    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,FlashAddress,  0xED);FlashAddress += 2;	             // SIGNATURE 
//    
//    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,FlashAddress,DayInt_Com);FlashAddress += 2;               // DAY TIME INTENSITY OF MASTER COMMUNICATION 
//    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,FlashAddress,NightInt_Com);FlashAddress += 2;             // NIGHT TIME INTENSITY OF MASTER COMMUNICATION
//    
//    if(Flag_1224_Com == SET)FlashData = 1;
//    else FlashData = 0;
//    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,FlashAddress,FlashData);FlashAddress += 2;                // CLOCK TIME FORMAT OF MASTER COMMUNICATION 
//    
//    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,FlashAddress,DayInt_self);FlashAddress += 2;              // SELF DAY TIME INTENSITY
//    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,FlashAddress,NightInt_self);FlashAddress += 2;            // SELF NIGHT TIME INTENSITY
//    
//    if(Flag_1224_self == SET)FlashData = 1;
//    else FlashData = 0;
//    HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,FlashAddress,FlashData);FlashAddress += 2;                // SELF SET CLOCK TIME FORMET
//    
//    
//    HAL_FLASH_Lock();
//    Delay_Cycles(1000); // 5000
//  }

uint32_t GetPage(uint32_t Addr)
{
  return (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;;
}

void KeyPad_Functionality(void)
{
    /* sensing button input here  */
    if(Flag_Keyscan)
    {
      Flag_Keyscan = RESET;
      Key_Entry = Key_Scan();
      if(Key_Entry)Key_Function();
    } /* end of button sensing */ 
    
    /* enter in program mode */
    if(Flag_Prog == SET){Program_Mode();Key.RST = SET;}
    else
    {
      /* Clock Mode Selection*/
      switch(Clock_Mode)
      {
      case MASTER :  if(Flag_CheckTime == SET)
      {
        Flag_CheckTime = RESET;
        MST_SS = Read_RTC(RTC_SS_REG);
      };
      if(MST_SS != Old_SS)
      {
        ModeCounter = 0;
        if(Flag_GPSActive == SET)LED_Color = GREEN_BLK;
        else if(Flag_RCVActive == SET)LED_Color = GREEN_STB;
        else LED_Color = RED_BLK;
        
        MST_MM = Read_RTC(RTC_MM_REG);
        MST_HH = Read_RTC(RTC_HH_REG);
        
        if(Flag_Communication){if(Flag_1224_Com)Flag_1224 = SET; else Flag_1224 = RESET;}
        else {if(Flag_1224_self)Flag_1224 = SET; else Flag_1224 = RESET;}
        
        if(MST_HH > 7 && MST_HH < 19)
        {
          if((Flag_Communication) && (DayInt != DayInt_Com))
          {
            DayInt = DayInt_Com;Flag_Intensity = SET; 
            DutyCycle = DayInt;
          }
          else if((Flag_Communication == RESET) && (DayInt != DayInt_self))
          {
            DayInt = DayInt_self; Flag_Intensity = SET; 
            DutyCycle = DayInt;
          }
        }
        else 
        {
          if((Flag_Communication) && (NightInt != NightInt_Com))
          {
            NightInt = NightInt_Com;Flag_Intensity = SET; 
            DutyCycle = NightInt;
          }
          else if((Flag_Communication == RESET) && (NightInt != NightInt_self))
          {
            NightInt = NightInt_self;Flag_Intensity = SET; 
            DutyCycle = NightInt;
          }
        }
        
        if(Flag_1224 == SET && (MST_HH > 12))DISP_HH = MST_HH-12; //for bypassing 12/24
        else DISP_HH = MST_HH;
        
        
        Display_RAM[0] = DISP_HH/10;Display_RAM[1] = DISP_HH%10;
        Display_RAM[2] = MST_MM/10;Display_RAM[3] = MST_MM%10;
        
        Old_SS = MST_SS;
        
        if(MST_HH == 7 && MST_MM == 0 && MST_SS == 0)
        {DutyCycle = DayInt;Flag_Intensity = SET;};
        
        if(MST_HH == 19 && MST_MM == 0 && MST_SS == 0)
        {DutyCycle = NightInt;Flag_Intensity = SET;};
      }
      break;
      
      case SLAVE  : if(Flag_SLAVE == SET)
      {
        Flag_SLAVE = RESET;
        ModeCounter = 0;
        LED_Color = RED_STB;
        
        SLV_SS = (RTC_Count % 3600) % 60;
        SLV_MM = (RTC_Count % 3600) / 60;
        SLV_HH = RTC_Count / 3600;
        
        if(Flag_Communication){if(Flag_1224_Com)Flag_1224 = SET; else Flag_1224 = RESET;}
        else {if(Flag_1224_self)Flag_1224 = SET; else Flag_1224 = RESET;}
        
        if(SLV_HH > 7 && SLV_HH < 19)
        {
          if((Flag_Communication) && (DayInt != DayInt_Com))
          {
            DayInt = DayInt_Com;Flag_Intensity = SET; 
            DutyCycle = DayInt;
          }
          else if((Flag_Communication == RESET) && (DayInt != DayInt_self))
          {
            DayInt = DayInt_self; Flag_Intensity = SET; 
            DutyCycle = DayInt;
          }
        }
        
        else 
        {
          if((Flag_Communication) && (NightInt != NightInt_Com))
          {
            NightInt = NightInt_Com;Flag_Intensity = SET; 
            DutyCycle = NightInt;
          }
          else if((Flag_Communication == RESET) && (NightInt != NightInt_self))
          {
            NightInt = NightInt_self;Flag_Intensity = SET; 
            DutyCycle = NightInt;
          }
        }
        if(Flag_1224 == SET && (SLV_HH > 12))DISP_HH = SLV_HH-12;//for bypassing 12/24
        else DISP_HH = SLV_HH;
        
        Display_RAM[0] = DISP_HH/10;Display_RAM[1] = DISP_HH%10;
        Display_RAM[2] = SLV_MM/10;Display_RAM[3] = SLV_MM%10;
        
        
        if(SLV_HH == 7 && SLV_MM == 0 && SLV_SS == 0)
        {
          DutyCycle = DayInt;Flag_Intensity = SET;
        };
        if(SLV_HH == 19 && SLV_MM == 0 && SLV_SS == 0)
        {
          DutyCycle = NightInt;Flag_Intensity = SET;
        };
      };
      break;
      
      };// End of Switch 	
      
    };// End of Else Prog
    
}


void Scan_Display(void)
{
    /* Segment Scan Start Here */
    if(Flag_SegUpdate == SET)
    {
      if(Display_RAM[0] == 0)Display_RAM[0] = BLANK;
      Flag_SegUpdate = RESET;							// Reset Flag
      
      DisplayData = BitMap_DATA[Display_RAM[NextDigit]];
      SegMult = 0x01;
      
      for(GP_Counter = 0;GP_Counter < 16; GP_Counter++)                         // check 24 bits
      {
        // reset data segment
        if(DisplayData & SegMult)SET_DATA; else RST_DATA;		        // Compare wuth Multiplier
        Delay_Cycles(100);SET_CLOCK; Delay_Cycles(100);RST_CLOCK;               // Set Clock Pulse
        
        SegMult = SegMult << 1;						        // LEft Shift Multilplier
      }
      
      DisplayData = BitMap_DATA[Display_RAM[NextDigit]];
      for(GP_Counter = 0;GP_Counter < 16; GP_Counter++)                         // check 24 bits
      {
        // reset data segment
        if(DisplayData & SegMult)SET_DATA; else RST_DATA;		        // Compare wuth Multiplier
        Delay_Cycles(100);SET_CLOCK; Delay_Cycles(100);RST_CLOCK;               // Set Clock Pulse
        
        SegMult = SegMult << 1;						        // Left Shift Multilplier
      }      
      Flag_SegReady = SET;							// Seg Data is Ready for next digit
    };/* End of scanning */
    
    /*change bysinc duty */
   if(Flag_Tim_tick == SET)
   {
      Flag_Tim_tick = RESET;
      Duty_Count++;
      if(Duty_Count > DutyCycle)DISABLE_CLOCK();
      if(Duty_Count > 3)   {Flag_DigitScan = SET; Duty_Count = 0;}
    }
    
    /* Digit Scan Start Here */
    if(Flag_DigitScan == SET)
    {
      Flag_DigitScan = RESET;							// Reset Digit Scan Flag	
      Flag_SegReady = RESET;							// Reset Segment Data Ready Flag
      DISABLE_CLOCK();            		                                // Turn OFF all ROWS First
      SET_LATCH;Delay_Cycles(20); RST_LATCH;					// Set Latch for nect data set
      if(Flag_Intensity == SET){Flag_Intensity = RESET;};                       // Set Intensity
      switch (DigitCount)							// Select Digit & enable
      {
      case 0 : SET_SEG1; NextDigit = 1; break;			                // Display Hour Tenth
      case 1 : SET_SEG2; NextDigit = 2; break;			                // Display Houm Unit
      case 2 : SET_SEG3; NextDigit = 0; break;			                // Display Min Tenth
      };
      DigitCount++;								// Increment Counter
      if(DigitCount > 3){DigitCount = 0;Flag_CheckTime = SET;};		 	// if all digits scaned reset
      Flag_SegUpdate = SET;							// Set flag for next scan
    };
}

