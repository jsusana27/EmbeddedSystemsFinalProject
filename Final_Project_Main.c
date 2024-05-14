#include <xc.h>
#include "Configuration.h"
#define _XTAL_FREQ 31000

#define NS_RedLight RD1
#define NS_YellowLight RD2
#define NS_GreenLight RD3

#define EW_RedLight RD0
#define EW_YellowLight RE2
#define EW_GreenLight RC5

#define NS_WalkRed RC2
#define NS_WalkGo RC6

#define EW_WalkRed RC0
#define EW_WalkGo RD4

//Global variables so that both ISR's and main can read/use them
int global_phase = 1;
int NS_WalkFlag = 0;
int EW_WalkFlag = 0;
int Startup = 1;



void __interrupt(high_priority) high_ISR() {  
       
    if(INT0IF == 1) { 
        /*For the NS walk button, if the NS axis is either green or yellow, then
          set the NS_WalkFlag and clear the interrupt flag. Otherwise, set the
          NS_WalkFlag, but turn WalkRed LED on and WalkGo LED off*/
        if(global_phase == 1) {
            NS_WalkFlag = 1;
            INT0IF = 0;
            return;
        }
        /*Different for this phase for some reason, since without the first 2
          lines in the if-statement, WalkRed LED turns on and WalkGo LED turns
          off.*/
        if(global_phase == 2) {
            NS_WalkRed = 0;
            NS_WalkGo = 1;
            NS_WalkFlag = 1;
            INT0IF = 0;
            return;
        }
        if(global_phase == 3) {
            NS_WalkFlag = 1;
            INT0IF = 0;
            return;
        }
        if(global_phase == 4) {
            NS_WalkRed = 1;
            NS_WalkGo = 0;
            NS_WalkFlag = 1;
            INT0IF = 0;
            return;
        }
        if(global_phase == 5 || global_phase == 6) {
            NS_WalkRed = 1;
            NS_WalkGo = 0;
            NS_WalkFlag = 1;
            INT0IF = 0;
            return;
        }
        if(global_phase == 7) {
            NS_WalkRed = 1;
            NS_WalkGo = 0;
            NS_WalkFlag = 1;
            INT0IF = 0;
            return;
        }
        if(global_phase == 8) {
            NS_WalkRed = 1;
            NS_WalkGo = 0;
            NS_WalkFlag = 1;
            INT0IF = 0;
            return;
        }
    }

    
    if(INT1IF == 1) {
        /*For the EW walk button, if the EW axis is either green or yellow, then
          set the EW_WalkFlag and clear the interrupt flag. Otherwise, set the
          EW_WalkFlag, but turn WalkRed LED on and WalkGo LED off*/
        if(global_phase == 1) {
            EW_WalkRed = 1;
            EW_WalkGo = 0;
            EW_WalkFlag = 1;
            INT1IF = 0;
            return;
        }
        if(global_phase == 2) {
            EW_WalkRed = 1;
            EW_WalkGo = 0;
            EW_WalkFlag = 1;
            INT1IF = 0;
            return;
        }
        if(global_phase == 3) {
            EW_WalkRed = 1;
            EW_WalkGo = 0;
            EW_WalkFlag = 1;
            INT1IF = 0;
            return;
        }
        if(global_phase == 4) {
            EW_WalkRed = 1;
            EW_WalkGo = 0;
            EW_WalkFlag = 1;
            INT1IF = 0;
            return;
        }
        if(global_phase == 5) {
            EW_WalkFlag = 1;
            INT1IF = 0;
            return;
        }
        /*Different for this phase for some reason, since without the first 2
          lines in the if-statement, WalkRed LED turns on and WalkGo LED turns
          off.*/
        if(global_phase == 6) {
            EW_WalkRed = 0;
            EW_WalkGo = 1;
            EW_WalkFlag = 1;
            INT1IF = 0;
            return;
        }
        if(global_phase == 7) {
            EW_WalkFlag = 1;
            INT1IF = 0;
            return;
        }
        if(global_phase == 8) {
            EW_WalkRed = 1;
            EW_WalkGo = 0;
            EW_WalkFlag = 1;
            INT1IF = 0;
            return;
        }
    }
}



void  __interrupt(low_priority) low_ISR() {
    if(TMR0IF == 1) {
        /*Note that global_phases in reverse order, since otherwise it will 
         increment 1 through 8 and execute all of the if-statements at once*/
        if(global_phase == 8) {
            NS_RedLight = 1;
            NS_YellowLight = 0;
            NS_GreenLight = 0;
            EW_RedLight = 1;
            EW_YellowLight = 0;
            EW_GreenLight = 0;
        
            /*Note that this is the only if-statement we use the return 
              keyword. Otherwise, it will execute this if-statement, then the
              code in the if(global_phase == 1) statement*/
            global_phase = 1;
            TMR0IF = 0;
            return;
        }
        
        if(global_phase == 7) {
            NS_RedLight = 1;
            NS_YellowLight = 0;
            NS_GreenLight = 0;
            EW_RedLight = 0;
            EW_YellowLight = 1;
            EW_GreenLight = 0;
            
            /*If EW WalkGo LED is on, detected through EW_WalkFlag, then make
              sure EW_WalkRed LED turns on and EW_WalkGo LED off immediately*/
            if(EW_WalkFlag == 1) {
                EW_WalkRed = 1;
                EW_WalkGo = 0;
                EW_WalkFlag = 0;
            }
            
            global_phase++;
        }
        
        if(global_phase == 5 || global_phase == 6) {
            NS_RedLight = 1;
            NS_YellowLight = 0;
            NS_GreenLight = 0;
            EW_RedLight = 0;
            EW_YellowLight = 0;
            EW_GreenLight = 1;
            
            /*If EW push button was pressed before this axis turns green, 
              detected through EW_WalkFlag, then immediately turn WalkGo LED
              on.*/
            if(EW_WalkFlag == 1) {
                EW_WalkRed = 0;
                EW_WalkGo = 1;
            }
            
            global_phase++;
        }
        if(global_phase == 4) {
            NS_RedLight = 1;
            NS_YellowLight = 0;
            NS_GreenLight = 0;
            EW_RedLight = 1;
            EW_YellowLight = 0;
            EW_GreenLight = 0;
            
            global_phase++;
        }
        
        if(global_phase == 3) {
            NS_RedLight = 0;
            NS_YellowLight = 1;
            NS_GreenLight = 0;
            EW_RedLight = 1;
            EW_YellowLight = 0;
            EW_GreenLight = 0;
            
            /*If NS WalkGo LED is on, detected through NS_WalkFlag, then make
              sure NS_WalkRed LED turns on and NS_WalkGo LED off immediately*/
            if(NS_WalkFlag == 1) {
                NS_WalkRed = 1;
                NS_WalkGo = 0;
                NS_WalkFlag = 0;
            }
            
            global_phase++;
        }
        
        if(global_phase == 1 || global_phase == 2) {
            NS_RedLight = 0;
            NS_YellowLight = 0;
            NS_GreenLight = 1;
            EW_RedLight = 1;
            EW_YellowLight = 0;
            EW_GreenLight = 0;
            
            /*If NS push button was pressed before this axis turns green, 
              detected through NS_WalkFlag, then immediately turn WalkGo LED
              on.*/
            if(NS_WalkFlag == 1) {
                NS_WalkRed = 0;
                NS_WalkGo = 1;
            }
            
            if(Startup == 1) {
                NS_WalkRed = 1;
                NS_WalkGo = 0;
                EW_WalkRed = 1;
                EW_WalkGo = 0;
                Startup = 0;
            }
            global_phase++;
        }  
        TMR0IF = 0;    
    }
}



void main(void) {
    //For crystal frequency
    IRCF2 = 0;
    IRCF1 = 0;
    IRCF0 = 0;
    
    
    //Setting LED's as output
    TRISD1 = 0;
    TRISD2 = 0;
    TRISD3 = 0;
    
    TRISD0 = 0;
    TRISE2 = 0;
    TRISC5 = 0;
    
    TRISC2 = 0;
    TRISC6 = 0;
    
    TRISC0 = 0;
    TRISD4 = 0;
    
    
    //Initializing all LED's to on
    NS_RedLight = 1;
    NS_YellowLight = 1;
    NS_GreenLight = 1;
    
    EW_RedLight = 1;
    EW_YellowLight = 1;
    EW_GreenLight = 1;
    
    NS_WalkRed = 1;
    NS_WalkGo = 1;
    
    EW_WalkRed = 1;
    EW_WalkGo = 1;
    
    
    RCON = 0b10000000;      //Setting IPEN bit in RCON register
    
    T0CON = 0b11000101;     //Enabling timer as 8-bit with prescale value of
                            //1:64
    
    INTCON = 0b11110000;    //Setting GIE, PEIE, TMR0IE, and INT0 bits
    
    INTCON2 = 0b01100000;   //Setting INT0 and INT1 on rising edge, and setting
                            //TMR0 as a low priority interrupt
    
    //INTCON2 = 0b00000000;   //Falling edge
    
    INTCON3 = 0b01001000;   //Enabling INT1 external interrupt as high priority
                            //Note that the INT0 external interrupt is always
                            //high priority.
    
    while(1);
    
    return;
}
