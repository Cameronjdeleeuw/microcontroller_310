/*
 * ---------------------
 * Title: SecretBoxAssignemnt
 * ---------------------
 * Program Details:
 *  The purpose of this program is to enter a special code by interfacing with photoresistors and a keypad to turn a motor.
 * Inputs: PORTB(keypad)
 * Outputs: PORTD(segments of 7segment), PORTA(digit activation)
 * Setup: C- Simulator
 * Date: April 24, 2024
 * File Dependencies / Libraries: It is required to include the 
 * Configuration Header File 
 * Compiler: xc8, 2.4
 * Author: Cameron deLeeuw
 * Versions:
 *      V1.0: Added function to read keypad (4/6/24)
 *      V1.1: Added functions to calculate and display value
 *      Notes:
 *              
 */


#include <xc.h> // must have this


#include "secretBoxInitialization.h"
#include "secretBoxConfig.h"
#include "C:\Users\624ca\MPLABXProjects\secretBoxAssignment.X\secretBoxFunctions.h"
   
void main (void){
    //Port initializations
    TRISB = 0b11110001; LATB = 0; ANSELB = 0;
    PORTB = 0b00000000;
    TRISA = 0b00110000; LATA = 0; ANSELA = 0;
    PORTA = 0b00000000;
    TRISD = 0b00000000; LATD = 0; ANSELD = 0;
    PORTD = 0b00000000;                     //turns off PORTB outputs so that the LED is initially off
    INTERRUPT_Initialize();


    while(1)
    {
        ///*
        currentButton = readKeypad();
        storeNumsPressed();
        displayNums();
        countPhotoresists();
        unlockAndBuzz();
        //*/
        //testDisplay();
    }
}
