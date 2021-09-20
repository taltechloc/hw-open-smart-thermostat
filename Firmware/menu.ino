/*
 * to do:
 * use defined preset names
 * clear at proper places
 */

void updateLCD(){
  if ((menuPos < 299 || menuPos > 301) && menuPos != 3000) tempSetpoint = setpoint;
  switch (menuPos){
    case 0:
      menuPos = 3;
      break;
    case  1:
      oled.setTextXY(0,0);
      if (state == 1) oled.putString("Heating: ON ");
      if (state == 0) oled.putString("Heating: OFF ");
      oled.setTextXY(1,0);
      oled.putString("SET:  ");
      oled.putFloat(setpoint);
      oled.setTextXY(2,0);
      oled.putString("TEMP:  ");
      oled.putFloat((float)temp);
      oled.setTextXY(4,0);
      oled.putString(">Presets ");
      oled.setTextXY(5,0);
      oled.putString("Settings ");
      oled.setTextXY(6,0);
      oled.putString("Heating ");
      break;
      //Presets menu----------------------------------------
     case 9:
      menuPos = 16;
      break;
     case  10:
      oled.setTextXY(0,0);
      oled.putString(">Preset1 ");
      oled.setTextXY(1,0);
      oled.putString("Preset2 ");
      oled.setTextXY(2,0);
      oled.putString("Preset3 ");
      oled.setTextXY(3,0);
      oled.putString("Preset4 ");
      oled.setTextXY(4,0);
      oled.putString("Preset5 ");
      oled.setTextXY(5,0);
      oled.putString("Preset6 ");
      oled.setTextXY(6,0);
      oled.putString("Back ");
      break;
    case 100:
      setpoint = PRESET1_TEMP;
      timeRemaining = minSecToMs(PRESET1_TIME, 0);
      menuPos = 1;
      break;
    case  11:
      oled.setTextXY(0,0);
      oled.putString("Preset1 ");
      oled.setTextXY(1,0);
      oled.putString(">Preset2 ");
      oled.setTextXY(2,0);
      oled.putString("Preset3 ");
      oled.setTextXY(3,0);
      oled.putString("Preset4 ");
      oled.setTextXY(4,0);
      oled.putString("Preset5 ");
      oled.setTextXY(5,0);
      oled.putString("Preset6 ");
      oled.setTextXY(6,0);
      oled.putString("Back ");
      break;
    case 110:
      setpoint = PRESET2_TEMP;
      timeRemaining = minSecToMs(PRESET2_TIME, 0);
      menuPos = 1;
      break;
    case  12:
      oled.setTextXY(0,0);
      oled.putString("Preset1 ");
      oled.setTextXY(1,0);
      oled.putString("Preset2 ");
      oled.setTextXY(2,0);
      oled.putString(">Preset3 ");
      oled.setTextXY(3,0);
      oled.putString("Preset4 ");
      oled.setTextXY(4,0);
      oled.putString("Preset5 ");
      oled.setTextXY(5,0);
      oled.putString("Preset6 ");
      oled.setTextXY(6,0);
      oled.putString("Back ");
      break;
    case 120:
      setpoint = PRESET3_TEMP;
      timeRemaining = minSecToMs(PRESET3_TIME, 0);
      menuPos = 1;
      break;
    case  13:
      oled.setTextXY(0,0);
      oled.putString("Preset1 ");
      oled.setTextXY(1,0);
      oled.putString("Preset2 ");
      oled.setTextXY(2,0);
      oled.putString("Preset3 ");
      oled.setTextXY(3,0);
      oled.putString(">Preset4 ");
      oled.setTextXY(4,0);
      oled.putString("Preset5 ");
      oled.setTextXY(5,0);
      oled.putString("Preset6 ");
      oled.setTextXY(6,0);
      oled.putString("Back ");
      break;
    case 130:
      setpoint = PRESET4_TEMP;
      timeRemaining = minSecToMs(PRESET4_TIME, 0);
      menuPos = 1;
      break;
    case  14:
      oled.setTextXY(0,0);
      oled.putString("Preset1 ");
      oled.setTextXY(1,0);
      oled.putString("Preset2 ");
      oled.setTextXY(2,0);
      oled.putString("Preset3 ");
      oled.setTextXY(3,0);
      oled.putString("Preset4 ");
      oled.setTextXY(4,0);
      oled.putString(">Preset5 ");
      oled.setTextXY(5,0);
      oled.putString("Preset6 ");
      oled.setTextXY(6,0);
      oled.putString("Back ");
      break;
    case 140:
      setpoint = PRESET5_TEMP;
      timeRemaining = minSecToMs(PRESET5_TIME, 0);
      menuPos = 1;
      break;
    case  15:
      oled.setTextXY(0,0);
      oled.putString("Preset1 ");
      oled.setTextXY(1,0);
      oled.putString("Preset2 ");
      oled.setTextXY(2,0);
      oled.putString("Preset3 ");
      oled.setTextXY(3,0);
      oled.putString("Preset4 ");
      oled.setTextXY(4,0);
      oled.putString("Preset5 ");
      oled.setTextXY(5,0);
      oled.putString(">Preset6 ");
      oled.setTextXY(6,0);
      oled.putString("Back ");
      break;
    case 150:
      setpoint = PRESET6_TEMP;
      timeRemaining = minSecToMs(PRESET6_TIME, 0);
      menuPos = 1;
      break;
    case  16:
      oled.setTextXY(0,0);
      oled.putString("Preset1 ");
      oled.setTextXY(1,0);
      oled.putString("Preset2 ");
      oled.setTextXY(2,0);
      oled.putString("Preset3 ");
      oled.setTextXY(3,0);
      oled.putString("Preset4 ");
      oled.setTextXY(4,0);
      oled.putString("Preset5 ");
      oled.setTextXY(5,0);
      oled.putString("Preset6 ");
      oled.setTextXY(6,0);
      oled.putString(">Back ");
      break;
    case 160:
      menuPos = 1;
      break;
    case 17:
      menuPos = 10;
      break;
   
    //Presets menu end------------------------------------
    
    case  2:
      oled.setTextXY(0,0);
      if (state == 1) oled.putString("Heating: ON ");
      if (state == 0) oled.putString("Heating: OFF ");
      oled.setTextXY(1,0);
      oled.putString("SET:  ");
      oled.putFloat(setpoint);
      oled.setTextXY(2,0);
      oled.putString("TEMP:  ");
      oled.putFloat((float)temp);
      oled.setTextXY(4,0);
      oled.putString("Presets ");
      oled.setTextXY(5,0);
      oled.putString(">Settings ");
      oled.setTextXY(6,0);
      oled.putString("Heating ");
      break;
      
    //settings menu--------------------------------------
    case 19:
      menuPos = 24;
      break;
    case 20:
      oled.setTextXY(0,0);
      oled.putString(">Setpoint ");
      oled.setTextXY(1,0);
      oled.putString("Duration ");
      oled.setTextXY(2,0);
      oled.putString("Bluetooth ");
      oled.setTextXY(3,0);
      oled.putString("Debug Mode ");
      oled.setTextXY(4,0);
      oled.putString("Back ");
      break;
    case 21:
      oled.setTextXY(0,0);
      oled.putString("Setpoint ");
      oled.setTextXY(1,0);
      oled.putString(">Duration ");
      oled.setTextXY(2,0);
      oled.putString("Bluetooth ");
      oled.setTextXY(3,0);
      oled.putString("Debug Mode ");
      oled.setTextXY(4,0);
      oled.putString("Back ");
      break;
    case 22:
      oled.setTextXY(0,0);
      oled.putString("Setpoint ");
      oled.setTextXY(1,0);
      oled.putString("Duration ");
      oled.setTextXY(2,0);
      oled.putString(">Bluetooth ");
      oled.setTextXY(3,0);
      oled.putString("Debug Mode ");
      oled.setTextXY(4,0);
      oled.putString("Back ");
      break;
    case 23:
      oled.setTextXY(0,0);
      oled.putString("Setpoint ");
      oled.setTextXY(1,0);
      oled.putString("Duration ");
      oled.setTextXY(2,0);
      oled.putString("Bluetooth ");
      oled.setTextXY(3,0);
      oled.putString(">Debug Mode ");
      oled.setTextXY(4,0);
      oled.putString("Back ");
      break;
    case 230:
      oled.setTextXY(0,0);             
      oled.putString("Temp: ");
      oled.putFloat((float)temp);
      oled.setTextXY(1,0);
      oled.putString("Set: ");
      oled.putFloat(setpoint);
      oled.setTextXY(2,0);
      oled.putString("Bat: ");
      oled.putFloat(batteryVoltage);
      oled.setTextXY(3,0);
      oled.putString("Cur: ");
      oled.putFloat(current);
      oled.setTextXY(4,0);
      oled.putString("PWM: ");
      oled.putFloat(duty);
      oled.setTextXY(5,0);
      oled.putString("Prop: ");
      oled.putFloat(proportional);
      oled.setTextXY(6,0);
      oled.putString("Der: ");
      oled.putFloat(derivative);
      oled.setTextXY(7,0);
      oled.putString("Int: ");
      oled.putFloat(integral);
      break;
    case 2300:
      menuPos = 23;
      break;
    case 24:
      oled.setTextXY(0,0);
      oled.putString("Setpoint ");
      oled.setTextXY(1,0);
      oled.putString("Duration ");
      oled.setTextXY(2,0);
      oled.putString("Bluetooth ");
      oled.setTextXY(3,0);
      oled.putString("Debug Mode ");
      oled.setTextXY(4,0);
      oled.putString(">Back ");
      break;
    case 240:
      menuPos = 1;
      break;
    case 25:
      menuPos = 20;
      break;
    //settings menu end----------------------------------
    
    case  3:
      oled.setTextXY(0,0);
      if (state == 1) oled.putString("Heating: ON ");
      if (state == 0) oled.putString("Heating: OFF ");
      oled.setTextXY(1,0);
      oled.putString("SET:  ");
      oled.putFloat(setpoint);
      oled.setTextXY(2,0);
      oled.putString("TEMP:  ");
      oled.putFloat((float)temp);
      oled.setTextXY(4,0);
      oled.putString("Presets ");
      oled.setTextXY(5,0);
      oled.putString("Settings ");
      oled.setTextXY(6,0);
      oled.putString(">Heating ");
      break;
    //heating screen------------------
    case 29:
      menuPos = 33;
      break;
    case  30:
      oled.setTextXY(0,0);
      if (state == 1) oled.putString("Heating: ON ");
      if (state == 0) oled.putString("Heating: OFF ");
      oled.setTextXY(1,0);
      oled.putString(">SET:  ");
      oled.putFloat(setpoint);
      oled.setTextXY(2,0);
      oled.putString("TEMP:  ");
      oled.putFloat((float)temp);
      oled.setTextXY(3,0);
      oled.putString("TR:  ");
      oled.setTextXY(4,0);
      oled.putString("TE:  ");
      oled.setTextXY(5,0);
      oled.putString("Bat:  ");  
      oled.putFloat(batteryVoltage);
      oled.setTextXY(6,0);
      oled.putString("Start/Stop ");
      oled.setTextXY(7,0);
      oled.putString("Back ");  
      break;   
    case  300:
      oled.setTextXY(0,0);
      oled.putString("OLD:  ");
      oled.putFloat(setpoint);
      oled.setTextXY(1,0);
      oled.putString("NEW:  ");
      oled.putFloat(tempSetpoint);
      break;
    case 299:
      tempSetpoint = tempSetpoint + 1;
      menuPos = 300;
      break;
    case 301:
      tempSetpoint = tempSetpoint - 1;
      menuPos = 300;
      break;
    case 3000:
      setpoint = tempSetpoint;
      menuPos = 30;   
    case  31:
      oled.setTextXY(0,0);
      if (state == 1) oled.putString("Heating: ON ");
      if (state == 0) oled.putString("Heating: OFF ");
      oled.setTextXY(1,0);
      oled.putString("SET:  ");
      oled.putFloat(setpoint);
      oled.setTextXY(2,0);
      oled.putString("TEMP:  ");
      oled.putFloat((float)temp);
      oled.setTextXY(3,0);
      oled.putString(">TR:  ");
      oled.setTextXY(4,0);
      oled.putString("TE:  ");
      oled.setTextXY(5,0);
      oled.putString("Bat:  ");  
      oled.putFloat(batteryVoltage);
      oled.setTextXY(6,0);
      oled.putString("Start/Stop ");
      oled.setTextXY(7,0);
      oled.putString("Back ");  
      break;  
    case  310: 
      menuPos = 31;
      break;   
    case  32:
      oled.setTextXY(0,0);
      if (state == 1) oled.putString("Heating: ON ");
      if (state == 0) oled.putString("Heating: OFF ");
      oled.setTextXY(1,0);
      oled.putString("SET:  ");
      oled.putFloat(setpoint);
      oled.setTextXY(2,0);
      oled.putString("TEMP:  ");
      oled.putFloat((float)temp);
      oled.setTextXY(3,0);
      oled.putString("TR:  ");
      oled.setTextXY(4,0);
      oled.putString("TE:  ");
      oled.setTextXY(5,0);
      oled.putString("Bat:  ");  
      oled.putFloat(batteryVoltage);
      oled.setTextXY(6,0);
      oled.putString(">Start/Stop ");
      oled.setTextXY(7,0);
      oled.putString("Back  ");  
      break;
    case 320:
      if (state == 0) state = 251;
      if (state == 1) state = 252;
      menuPos = 32;
      break;
    case 33:
      oled.setTextXY(0,0);
      if (state == 1) oled.putString("Heating: ON ");
      if (state == 0) oled.putString("Heating: OFF ");
      oled.setTextXY(1,0);
      oled.putString("SET:  ");
      oled.putFloat(setpoint);
      oled.setTextXY(2,0);
      oled.putString("TEMP:  ");
      oled.putFloat((float)temp);
      oled.setTextXY(3,0);
      oled.putString("TR:  ");
      oled.setTextXY(4,0);
      oled.putString("TE:  ");
      oled.setTextXY(5,0);
      oled.putString("Bat:  ");  
      oled.putFloat(batteryVoltage);
      oled.setTextXY(6,0);
      oled.putString("Start/Stop ");
      oled.setTextXY(7,0);
      oled.putString(">Back  ");  
      break;
    case  330: 
      menuPos = 3;
      break;
    case 34:
      menuPos = 30;
      break;    
    case 4:
      menuPos = 1;
      break;
    default:
      menuPos = 1;
      oled.clearDisplay();
      break;  
  }
}
