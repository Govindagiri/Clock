/************************************************************************************************************************************************************************/

DATE : 28/06/2024
TIME : 11:14am

// UNDERSTANDING:
-> Their is project named as "SPNTC62_REV4" in this , this project we have GPS module which is recieving the NMEA string from satellite
we have to extract time from that string by using extracted time we will sychronise the Internal RTC of MCU then using that data send it 
to salve RTC or External_RTC.GPS having LED which gives blinking on connected with the Network kind of a indication. The Time will Sychronise in
every one minute of the interval. This will Display on the 3 led matrix display by using bit mapping method. Having key remote also to control 
multiple option.

//COMPONENTS:
-> STM32G030C8T6 - MCU
-> LC86G_GPS     - GPS Module
-> M41T83        - External RTC
-> LM1117-3.3    - Voltage Regulator
-> M74HC245      - Bus TX\Rx IC
-> MC74HC595A    - 8Bit Serial i/p to serial o/p and parallel o/p
-> GPS LED

//INTIALIZATION:
->RTC
->UART 1
->UART 2
->GPIO
->IWDG

//PIN CONFIGURATION:
->COL LAT IN  - PA0
->COL CLK IN  - PA1
->DATA1       - PA4
->DATA2       - PA5
->DISP ENB    - PA6
->DOT         - PA7
->INT         - PB0
->12/24       - 1PB1
->HH-TEN      - PB2
->HH-UNIT     - PB10
->MM-TEN      - PB11
->MM-UNIT     - PB12
->SS-TEN IN   - PB13
->SS-UNIT IN  - PB14
->PRG         - PB15
->DEC         - PA11
->INC         - PA12
->GPS ON      - PA15
->TEST        - PB5
->SCL         - PB6
->SDA         - PB7

//STEPS:
->Intialize the GPS module whichis rx the NMEA string and extracyt the TIME from it.
->Using that GPS Hour and Minute it will sychronise that the time of internal RTC of MCU by using Uart1.
->Then internal_RTC(Master) will sen the data to the external RTC by using the SCL and SDA line.
->Internal_RTC then send the data to the display by using the GPIO pins of the MCU.
->It have KEY(remote also ) to control the TEST, INC, DEC, PRG, 12/24, INT etc.
->Then the time or local RTC Sychronise in every one minute.
->Their is change then it would sychronise in absence of the network the rate date of the LED bliking is reduced
->And it Display the internal RTC time on the board.

#I2C try and check in ll if its works OK if not use HAL.

/*************************************************************************************************************************************************************************/

DATE : 29/06/2024
TIME : 6:12pm

//UPDATE:
->All things are intialised and used multiple places as required.
->The project build successfully without any error.
/////////////BITMAPPING IS PENDING///////////////.

/*************************************************************************************************************************************************************************/

DATE : 30/06/2024
TIME : 5:12am

->Do the remaining part of bitmapping is complete but ist showing an error and build failed.

/*************************************************************************************************************************************************************************/

DATE : 30/06/2024
TIME : 11:40am

->Bitmapping is done according to the requirement and it build successfully.

/*************************************************************************************************************************************************************************/

DATE : 17/07/24
TIME : 6:19pm

->Having an issue relate to it :
1. Multiple Error regareding the code
2. LL library is not their for get the time internal RTC
3. Having the issue in the bool reated to it 


/*************************************************************************************************************************************************************************/

DATE : 18/07/24
TIME : 1:19pm

-> Take care of issue related to it :
1. Resolved the issue related to the Lib error
2. Merge the key scan part in the main code as said before.
3. Add comment in the required lines.

/*************************************************************************************************************************************************************************/




