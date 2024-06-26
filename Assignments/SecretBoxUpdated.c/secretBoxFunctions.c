//void __interrupt(irq(IRQ_INT0),base(0x4008)) INT0_ISR(void)
//{
//    if(PIR1bits.INT0IF == 1) {
//        for(int j=1;j<=3;j++)
//            {
//                //wait++;
//                for(int u=0;u<=50;u++)
//                {
//                PORTA = 0b00001000;
//                __delay_ms(1);
//                PORTA = 0;
//                __delay_ms(1);
//                }
//                for(int u=0;u<=30;u++)
//                {
//                PORTA = 0b00001000;
//                __delay_ms(2);
//                PORTA = 0;
//                __delay_ms(2);
//                }
//                for(int u=0;u<=20;u++)
//                {
//                PORTA = 0b00001000;
//                __delay_ms(3);
//                PORTA = 0;
//                __delay_ms(3);
//                }
//                for(int u=0;u<=10;u++)
//                {
//                PORTA = 0b00001000;
//                __delay_ms(4);
//                PORTA = 0;
//                __delay_ms(4);
//                }
//
//            //}
//        }
//}
//    PIR1bits.INT0IF = 0;
//        // Check if interrupt flag for INT0 is set to 1 - (note INT0 is your input)
//            // if so, do something
//                // e.g,blink an LED connected to  PORTDbits.RD0 for 10 times with a delay of __delay_ms(250)
//        // always clear the interrupt flag for INT0 when done
//        // turn off the led on PORTDbits.RD0 
//}

//void INTERRUPT_Initialize ()
//{
//    INTCON0bits.IPEN = 1; // Enable interrupt priority bit in INTCON0 (check INTCON0 register and find the bit)
//    INTCON0bits.GIEL = 1; // Enable high priority interrupts using bits in INTCON0
//    INTCON0bits.GIEH = 1; // Enable low priority interrupts using bits in INTCON0
//    INTCON0bits.INT0EDG = 1;// Interrupt on rising edge of INT0 pin using bits in INTCON0
//    IPR1bits.INT0IP = 1;// Set the interrup high priority (IP) for INT0 - INT0IP
//    PIE1bits.INT0IE = 1;// Enable the interrup (IE) for INT0
//
//    PIR1bits.INT0IF = 0; //Clear interrupt flag for INT01
//  
//    // Change IVTBASE by doing the following
//    IVTBASEU = 0x00; // Set IVTBASEU to 0x00 
//    IVTBASEH = 0x40;// Set IVTBASEH to  0x40; 
//    IVTBASEL = 0x08;// Set IVTBASEL to 0x08; 
//}


void countPhotoresists() 
{
    //Checks if photo resistor 1 is covered 
    if(PORTA == 0b00010000)
    {
        __delay_ms(100);
        photo1++;
        while(PORTA == 0b00010000)
        {
            //Wait for sensor to see light aftr dark
            PORTA = 2;
            PORTD = 0b10000000;
        }
        //PORTA = 0;
        //PORTD = 0;
        __delay_ms(500); //used for err in time between seeing dark to light
    }   
    //Checks if photo resistor 2 is covered 
    if(PORTA == 0b00100000)
    {
        photo2++;
        while(PORTA == 0b00100000)
        {
            //Wait for sensor to see light aftr dark
            PORTA = 2;
            PORTD = 0b10000000;

        }
        __delay_ms(500); //used for err in time between seeing dark to light
    }
    return;
}

void unlockAndBuzz()
{
        //Unlock function
        if(photo1 == 0|| photo2 == 0)
        {
            PORTA = 0b00000000;
        }
        else if(photo1 == hexToDigit_MAT[1][0] && photo2 == hexToDigit_MAT[1][1] ) 
        {
            PORTA = 0b00000101;
            PORTD = 0b10000000;
            __delay_ms(1500);
            PORTA = 1;
            reset();
            
        }
        
        //buzzer
        if(photo1 > hexToDigit_MAT[1][0] || photo2 > hexToDigit_MAT[1][1])
        {
            //buzzer sad tone
            //int i =0;
            for(int i=0;i<=3;i++)
            {
                //wait++;
                for(int j=0;j<=50;j++)
                {
                PORTA = 0b00001000;
                __delay_ms(1);
                PORTA = 0;
                __delay_ms(1);
                }
                for(int j=0;j<=25;j++)
                {
                PORTA = 0b00001000;
                __delay_ms(3);
                PORTA = 0;
                __delay_ms(3);
                }

            }
            //wait = 0;
            reset();
        }
}
                
void storeNumsPressed()
{
    //to store value pressed as the hex equivilant val to be displayed on 7 segment
    //int i = 0;
    for (int i = 0; i <=9; i++)
    {
        if (currentButton == i)
        {
            hexToDigit_MAT[0][whichDigit] = numsAndHexs_MAT[1][i]; 
            hexToDigit_MAT[1][whichDigit] = i;
        }
    }
    return;
}

void displayNums()
{
        //display numPressed on display
        for (int i=0; i<=3; i++)
        {
            PORTB = power(i); //make own power function
            PORTD = hexToDigit_MAT[0][i];
            __delay_us(1000); //delay 1mSeconds
            PORTB = 0;
        }
        
        //checks every loop if a 5 digit was pressed, if true, reset
        if (whichDigit == 4)
        {
            reset();
        }
        return;

}

int power(int j)
{
    if (j == 0)
    {
        return 1;
    }
    if (j == 1)
    {
        return 2;
    }
    if (j == 2)
    {
        return 4;
    }
    if (j == 3)
    {
        return 8;
    }
}

void reset() //reset function
{
    photo1 = 0;
    photo2 = 0;
    int i = 0;
    currentButton = -1;
    whichDigit = -1;
    for(i=0; i<=3; i++)
    {
        hexToDigit_MAT[0][i] = 0;
        hexToDigit_MAT[1][i] = 0;
    }
    return;
}

int readKeypad()
{   
        /*
        PORTB = 0b00000001;
        if(PORTB == 0b10000001) {
            currentButton = A;  //ASCII equivilant of +
            __delay_ms(250);
            return currentButton;
        }
        if(PORTB == 0b01000001) {
            currentButton = B;  //ASCII equivilant of -
            //whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        if(PORTB == 0b00100001) {
            currentButton = C;  //ASCII equivilant of x
            //whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        if(PORTB == 0b00010001) {
            currentButton = D;  //ASCII equivilant of /
            //whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        */
        PORTA = 0b00000010;
        if(PORTA == 0b10000010) {
            currentButton = three;  //ASCII equivilant of 3
            whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        if(PORTA == 0b01000010) {
            currentButton = six;  //ASCII equivilant of 6
            whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        if(PORTA == 0b00100010) {
            currentButton = nine;  //ASCII equivilant of 9
            whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        if(PORTA == 0b00010010) {
            currentButton = pound;  //ASCII equivilant of #(equ)
            //whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        PORTA = 0b00000100;
        if(PORTA == 0b10000100) {
            currentButton = two;  //ASCII equivilant of 2
            whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        if(PORTA == 0b01000100) {
            currentButton = five;  //ASCII equivilant of 5
            whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        if(PORTA == 0b00100100) {
            currentButton = eight;  //ASCII equivilant of 8
            whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        if(PORTA == 0b00010100) {
            currentButton = zero;  //ASCII equivilant of 0
            whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        PORTA = 0b00001000;
        if(PORTA == 0b10001000) {
            currentButton = one;  //ASCII equivilant of 1
            whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        if(PORTA == 0b01001000) {
            currentButton = four;  //ASCII equivilant of 4
            whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        if(PORTA == 0b00101000) {
            currentButton = seven;  //ASCII equivilant of 7
            whichDigit++;
            __delay_ms(250);
            return currentButton;
        }
        if(PORTA == 0b00011000) {
            currentButton = star;  //ASCII equivilant of *(result)
            //whichDigit++;
            __delay_ms(250);
            reset();
            return currentButton;
        }
        PORTA = 0b00000000;
        return -1;
}

void testDisplay()
{
            PORTB = 1;
            PORTD = 0b11000001;
            __delay_ms(50);
            PORTD = 0b11000010;
            __delay_ms(50);
            PORTD = 0b11000100;
            __delay_ms(50);
            PORTD = 0b11001000;
            __delay_ms(50);
            PORTD = 0b11010000;
            __delay_ms(50);
            PORTD = 0b11100000;
            __delay_ms(50);
            PORTD = 0b11000001;
            __delay_ms(50);
            PORTB = 2;
            PORTD = 0b11000001;
            __delay_ms(50);
            PORTD = 0b11000010;
            __delay_ms(50);
            PORTD = 0b11000100;
            __delay_ms(50);
            PORTD = 0b11001000;
            __delay_ms(50);
            PORTD = 0b11010000;
            __delay_ms(50);
            PORTD = 0b11100000;
            __delay_ms(50);
            PORTD = 0b11000001;
            __delay_ms(50);
            PORTB = 4;
            PORTD = 0b11000001;
            __delay_ms(50);
            PORTD = 0b11000010;
            __delay_ms(50);
            PORTD = 0b11000100;
            __delay_ms(50);
            PORTD = 0b11001000;
            __delay_ms(50);
            PORTD = 0b11010000;
            __delay_ms(50);
            PORTD = 0b11100000;
            __delay_ms(50);
            PORTD = 0b11000001;
            __delay_ms(50);
            PORTB = 8;
            PORTD = 0b11000001;
            __delay_ms(50);
            PORTD = 0b11000010;
            __delay_ms(50);
            PORTD = 0b11000100;
            __delay_ms(50);
            PORTD = 0b11001000;
            __delay_ms(50);
            PORTD = 0b11010000;
            __delay_ms(50);
            PORTD = 0b11100000;
            __delay_ms(50);
            PORTD = 0b11000001;
            __delay_ms(50);
        }


