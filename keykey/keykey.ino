/*
* Code for IUPUI course ECE47100
 * Embedded Systems
 * Spring 2013
 * Collaborators: Alex Shroyer, Mandeep Palia
 *
 *  The following code represents the software portion of a microcontroller based,
 *  embedded system project.  This project is like an electronic harpsichord.
 *  Keystrokes are intercepted via a serial interface, and then used
 *  to trigger musical note events.  Paramters of these musical notes are
 *  also adjustable via the keyboard interface.
 *  For the physical circuit, a single digital pin connected to a common-emitter 
 *  transistor amplifier buffers the output, and is then capacitively (10 uF)
 *  coupled to a 10k potentiometer for volume control.  The output impedance is
 *  approximately 1k ohms and can drive earbud-style headphones directly, or for
 *  greater amplification can be plugged into a "line in" amplifier input.
 *
 *  The seven-segment display driver is rather unusual: a CD4024 ripple counter.  
 *  The Clock and Reset inputs are controlled by Arduino pins A4 and A5.  To display
 *  a character, the ripple counter's Q1 through Q7 outputs connect to the segments of
 *  a MAN74A common-cathode LED display through 220 ohm resistors.  The counter is
 *  reset, then the value corresponding to the appropriate segments "on" is clocked 
 *  into the counter.
 */
#include <EEPROM.h>            // stock Arduino library
#include <EEPROMAnything.h>    // open-source library
#include <PS2Keyboard.h>       // open-source library
#include <DividerDisplay.h>    // our own library; large arrays are stored here

// define pins
const int audioOut = 13;    // also connected to Arduino LED
const int clk7 = 4;
const int rst7 = 5;
const int DataPin = 3;    // green wire on pigtail
const int IRQpin = 2;    // white wire on pigtail
PS2Keyboard keyboard;

// define variables
int i;
unsigned int counter;
int inByte = 0;
int noteDuration = 100;
boolean kbd;
int dsplyspd = 50;
int swirlspd = 50;

// assign pins and ports, initialize peripherals
void setup(){
  DDRC |= 0x30;  // Set pins A4 and A5 as outputs, all other PORTC pins as inputs
  // A4 connects to 4024(clk), A5 connects to 4024(reset)
  pinMode(audioOut, OUTPUT);    // alternative way of setting an individual bit of a port as output
  delay(1000);    // for ps/2 keyboard
  keyboard.begin(DataPin, IRQpin);
  hello();                  // Begin Serial communication
}

void loop(){
  // BIG counter for good frequency resolution
  for (counter = 0; counter < 65535; counter++){
    if(Serial.available()){    // do all these if connected via Serial UART.
      inByte = getkey();
      kbd = false;
      normalLoop();
    }
    if(keyboard.available()){    // do all these if an external PS/2 keyboard is attached
      inByte = keyboard.read();
      kbd = true;
      normalLoop();
    }
    noTone(audioOut);
  }
}
