Date:30/08/2024

OFFICE CLK:-
Write a program of a Office clock->shows correct time on display->when connected to GPS->When NOt; display inter. rtc time->Its update time in every 1 minute->Having keys <INC,DEC,PRG,INT,TEST,12/24> with differnet functionality.

COMPONENTS:-
->Micro(STM32G030C8T6)
->Drtiving IC(TC62D748CFNAG)
->Mosfet(FDS4953)
->GPS Module(LC86G)
->External RTC(M41T83)
->Leds

PROCESS:-
->Intilise the required pheripheral.
->Make Macros of different pins.
->Take Nmea String from satellite using GPS Module when gps connected
->Extract time from nmea convert into Indian format
->Synch that time to internal and external rtc
->When GPS not connected it display time from internal RTC 
->Having keys for different function :
                                     - INC(For increment +1   )
                                     - DEC(For Decrement -1   )
                                     - Test(For checking all LED )
                                     - PRG(For program clock  )
                                     - INT(For Intensity      )->changes at every press<25%, 50%, 75%, 100%>
                                     - 12/24(For format change)
->Used the comment for the future reference.
->Compile and debug the program.
->Run the program.
                   
                   
PROBLEM AND SOLUTION:-
P1- Intially the code is building properly but not displaying the data in display.Check the Pin mode Pushpull
S1- Having the problem from code side do the changes and check all the pins again
S2- Check the pins that is data pin going to the drving IC checked it supply when we doing set or reset

P2- GPS data not coming into the buffer
S1-Checking the interrupt is coming into the given Usart or not.
S2-Check the buffer in which we have to give into it
S3-Check Nmea is coming or not using TX and RX pin

P3- Data is coming but not in the right manner
S1- Check the bit map using to display the digit is correct or not

P4-External RTC timing is not moving it shows 110 or fixed value
S1-Check the power supply or the RTC
S2-Change RTC or it resistance and capacitor
S3- Check the GPIO SCL and SDA pin configuration is pushpull or open drain 
S4- Check the buffer you are choosing to put data into it

P5-Driving IC is getting HOT
S1-Check voltage aross the IC take UPDATED SCHEMATIC check again in this its 3.3V
S2-Chck on pair or segment one by one .
S3-Check the data sheet that how much current goes through it.

P6- Keypad section showing error 
S1- Check the Pin configuration again key might be changed 

P7-Hardware validation Defination
S1-Validation of the IC, mosfet, micro, external rtc etc CHECK IT FROM THE SOFTWARE SIDE BY HIGH OR LOW THE PIN CHECK THE VOLTAGE AND FUNCTION DOING THROUGH IT. 