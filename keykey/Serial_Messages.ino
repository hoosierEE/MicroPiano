void hello(){
  // Go on, introduce yourself.
  Serial.begin(9600);  
  Serial.println("Microcontroller Piano Project");
  Serial.println("\nPress M for Menu.");

  // get the most recently saved noteDuration from the EEPROM
  EEPROM_readAnything(0, noteDuration);
  if(noteDuration < 20){
    noteDuration = 100;    // default value if note duration somehow gets too short
    Serial.println("Using default note duration value (100)");
  }
  else{
    Serial.print("Note duration (from EEPROM) value = ");
    Serial.println(noteDuration);
  }
  // startup animations, whee!
  doSwirl(2);
  cycleNumbers();
  makeAlphaNum(-1); 
}

void printNote(int inByte){
  // Send this function a byte and it will print it in hex and decimal formts.
  Serial.print("Hex: ");
  Serial.print(inByte, HEX);
  Serial.print("\tDecimal: ");
  Serial.println(inByte, DEC);
}

void doMenu(boolean k){
  // If the user sends a serial 'M' it toggles the Menu on/off
  // display something ()
  Serial.println("\nMenu");
  Serial.println("For a list of commands press L");
  Serial.println("Press M to exit Menu, W to save data to EEPROM\n");
  doSwirl(1);
  makeAlphaNum(-1);
  while(inByte != -2){
    if (k == true){
      inByte = keyboard.read();
    }
    else{
      inByte = getkey();
    }
    if(inByte == 0x31){
      // 1 key decreases noteDuration
      if(noteDuration > 20)
        noteDuration = noteDuration - 10;
      Serial.print("Note Duration = ");
      Serial.println(noteDuration);
    }
    if(inByte == 0x32){
      // 2 key increases noteDuration
      if(noteDuration < 500)
        noteDuration = noteDuration + 10;
      Serial.print("Note Duration = ");
      Serial.println(noteDuration);

    }
    if(inByte == 0x4C){
      Serial.println("Commands:");
      Serial.println("1: decrease note duration\t2: increase note duration");
    }
    if(inByte == 0x4D){
      // M character: prompt then exit
      Serial.println("Exiting Menu\n");
      inByte = -2;
      // display something ()
    }
    if(inByte == 0x57){
      // W character: write data to EEPROM
      EEPROM_writeAnything(0, noteDuration);
      doSwirl(1);
      makeAlphaNum(-1);
      Serial.print("Wrote value ");
      Serial.print(noteDuration);
      Serial.println(" to EEPROM location 0");
    }
  }
}



