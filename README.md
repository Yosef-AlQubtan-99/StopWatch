# StopWatch
This project is for making a stop watch using 7SEG-MPx6-CC module in proteus drived by 74LS48 and 
using 3 push btns for stopwatch functionning:
INT0: RESET StopWatch
INT1: PAUSE
INT2: RESUME
with a mode changer to clock
using Polling technique on C7 Pin
Also in StopWatch mode :
C6 pin senses GND if PUSH BTN is pressed CountDown Timer activated and countdown is shown on 7SEG
and BUZZER on C5 is Activated
This project could be enhanced by adding ALARM clock to predefined pin C6 (in CLOCK MODE only)



NOTE : Time on Proteus is not the same time as the machine so tick time and CTC time is modified to suite my version of proteus
       one second in this programe is OCR value =250 , Local_u16Counter "in if condition in IncSec & DecSec" = 4000
