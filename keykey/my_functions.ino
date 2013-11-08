/*
 * Here we put the various functions for the project.  
 * The Arduino IDE simply concatenates these functions below the loop(). 
 */

void normalLoop(){
  if(inByte == 0){
    // No bytes in buffer, do something useful, like blink an LED.
  }
  else if((inByte > 0x60)&&(inByte < 0x7B)){
    // Play a tone for lowercase letters a through z, display some info.
    tone(audioOut, notes[inByte - 0x61], noteDuration);
    delay(noteDuration);
    printNote(inByte);
    segLetter(inByte);
  }
  else if (inByte == 0x4D){ 
    doMenu(kbd);  // Enter Menu
  }
  else{

  }
  //noTone(audioOut);
}

byte getkey(){  // Read Serial buffer, return ASCII value.
  int keyByteValue = Serial.read();
  return keyByteValue;
}

void resetMe(){
  // reset the counter to zero
  PORTC |= B00110000;    // first set both CLK and RST high,
  __asm__("nop\n\t");    // very short delay (one machine cycle at 16MHz clock frequency yields 62.5ns of delay)
  PORTC &= B11011111;    // then make RST low to enable counting
}

void cycleNumbers(){
  for (int i = 0; i < 17; i++){
    makeAlphaNum(i);
    delay(dsplyspd);
  }
}

void doSwirl(int reps){
  for (int j = 0; j < reps; j++){
    for (int i = 0; i < 6; i++){
      swirl(i);
      delay(swirlspd);
    }
  }
}

void swirl(int i){
  resetMe();  // reset counter
  for (int k = 0; k < swrl[i]; k++){
    digitalWrite(A4, HIGH);
    digitalWrite(A4, LOW);
  }
}

void segLetter(int inByte){
  switch (inByte){
  case 0x61:
  case 0x69:
  case 0x6B:
  case 0x6D:
  case 0x71:
    makeAlphaNum(10);
    break;
  case 0x6C:
  case 0x6F:
  case 0x73:
  case 0x77:
  case 0x7A:
    makeAlphaNum(11);
    break;
  case 0x64:
  case 0x65:
  case 0x70:
  case 0x78:
    makeAlphaNum(12);
    break;
  case 0x63:
  case 0x66:
  case 0x72:
    makeAlphaNum(13);
    break;
  case 0x67:
  case 0x74:
  case 0x76:
    makeAlphaNum(14);
    break;
  case 0x62:
  case 0x68:
  case 0x79:
    makeAlphaNum(15);
    break;
  case 0x6A:
  case 0x6E:
  case 0x75:
    makeAlphaNum(16);
    break;
  }   
}
void makeAlphaNum(int i){
  resetMe();  // reset counter
  if (i < 0) {
    return;  // passing no count to the counter = blank display
  }
  for (int k = 0; k < dsply[i]; k++){
    digitalWrite(A4, HIGH);
    digitalWrite(A4, LOW);
  }
}





