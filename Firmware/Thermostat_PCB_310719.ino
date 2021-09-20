



//W.I.P. code for BT enabled microheating thermostat
//By Henri Sink
//
//Uses a logic level Mosfet driving a resistive heater
//thermistor for feedback and OLED display UI
//BT disabled for more accurate power measurements


#include "defines.h"

#include <Ticker.h>
//#include <MAX6675_Thermocouple.h>
#include <Wire.h>
#include <ESP32Encoder.h>
#include <ACROBOTIC_SSD1306.h>
#include <ADS1115_async.h>
#include "driver/adc.h"
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#diff Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif




//external ADC config
const byte I2C_ADS1115                = 0x48;       // the I2C address of the device
const byte ADS1115_inputSelect        = B01000110;  // input enable configuration 
const unsigned long ADS1115_inputGain = 0x00053100; // set the gain for each input
const byte ADS1115_autoGainAdjust     = B00000000;  // enable/disable Auto Gain Adjust




//MAX6675_Thermocouple* thermocouple = NULL;
BluetoothSerial SerialBT;
Ticker sender;
Ticker tempReader;
Ticker lcdUpdater;
ADS1115_async ADS(I2C_ADS1115, ADS1115_inputSelect, ADS1115_autoGainAdjust, ADS1115_inputGain);
ESP32Encoder encoder;



int state = 0;
int menuPos = 1;
float tempSetpoint = 0;
int timeRemaining = 0;
int timeButtonPressed = 0;
int logTimeElapsed = 0; 
int logTimeBefore = 0;
volatile bool upButtonPressed = false;
volatile bool downButtonPressed = false;
volatile bool okButtonPressed = false;

//PID variables
int duty = 0;
float P = 1000;
float I = 0.1;
float D = 2200000;
float proportional = 0;
float integral = 0;
float derivative = 0;
float setpoint = 30;
float diff = 0;
float oldDiff = 0;
int interval = 0;
int newTime = 0;
int oldTime = 0;
int encoderCountDif;
int encoderOldCount;

double temp;
float batteryVoltage;
float Vdd;

float voltage = 0.0;  // Voltage measured by ADS1015 for 8 different input configurations
float gain = 0.0;     // Gain used for the conversion
byte precision = 0;

//ext ADC 
byte result;
float tempVoltage = 0;
float current = 0;

//functions
void sendBTData();
void receiveBTData();
//void readTemp();
void computePID();
void updateLCD();
float convertTemperature(float voltage);

void IRAM_ATTR buttonUpISR();
void IRAM_ATTR buttonDownISR();
void IRAM_ATTR buttonOkISR();

//------------------------------------------------------------------------------------------------------------------------------------------------------//

void setup() {
  pinMode(ledRPin, OUTPUT);
  pinMode(ledGPin, OUTPUT);
  pinMode(ledBPin, OUTPUT);
  delay(100);
  digitalWrite(ledRPin, HIGH);
  delay(100);
  digitalWrite(ledGPin, HIGH);
  delay(100);
  digitalWrite(ledBPin, HIGH);
  delay(100);
  digitalWrite(ledBPin, LOW);
  delay(100);
  digitalWrite(ledBPin, HIGH);
  digitalWrite(ledRPin, LOW);
  delay(100);
  digitalWrite(ledRPin, HIGH);
  digitalWrite(ledGPin, LOW);
  delay(100);
  digitalWrite(ledGPin, HIGH);
  
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);
  encoder.attachHalfQuad(ENC_A, ENC_B);

  
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_DB_11);
  adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_11);

  ledcAttachPin(HEATER_PIN, LEDC_CHANNEL_0);
  ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_12_BIT);
    
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  Wire.begin();

  oled.init();                      // Initialze SSD1306 OLED display
  oled.clearDisplay();              // Clear screen  

  //external ADC for current and temp sensing
  result = ADS.begin();  // initialize ADS1015 and start first conversion
  if ( result ) {
    Serial.print("Error in initializing ADS1015, error#: ");
    Serial.println(result);
    while(1);
  }


  //interrupts
  //attachInterrupt(BUTTON_UP, buttonUpISR, FALLING);
  //attachInterrupt(BUTTON_DOWN, buttonDownISR, FALLING);
  attachInterrupt(ENC_SW, buttonOkISR, FALLING);

  //Periodic events setup
  sender.attach(SEND_PERIOD, sendBTData);
  //tempReader.attach(TEMP_READ_PERIOD, readTemp);
  //lcdUpdater.attach(LCD_UPDATE_PERIOD, updateLCD);

}

//------------------------------------------------------------------------------------------------------------------------------------------------------//

//main loop
void loop() {
  receiveBTData();
  updateLCD();
  if (millis() - timeButtonPressed > 50){
    encoderCountDif = encoder.getCount() - encoderOldCount;
    encoderOldCount = encoder.getCount();
    if (encoderCountDif < 0) {
      menuPos -= 1;
      timeButtonPressed = millis();    
    }
    if (encoderCountDif > 0) {
      menuPos += 1;
      timeButtonPressed = millis();
    }
    if (okButtonPressed){
      menuPos = menuPos * 10;
      timeButtonPressed = millis();
      oled.clearDisplay();
    }
  }
  downButtonPressed = false;
  upButtonPressed = false;
  okButtonPressed = false;
  
  //batteryVoltage = (float)adc1_get_raw(ADC1_CHANNEL_4)*3.53*2/4096; //adc is inaccurate, should be 3.9 FS but is 3.53
  //Vdd = (float)adc1_get_raw(ADC1_CHANNEL_6)*3.56*2/4096; //adc is inaccurate, should be 3.9 FS but is 3.53
  
  //ext.ADC
  result = ADS.poll(); //returns number of input that has conversion ready
  /*if (result != 0) {
    precision = ADS.getPrecision();     // get the number of significant decimals after the decimal point
    gain = ADS.getGain();               // get the gain in Volt/digit
    voltage = ADS.getVoltage();         // get the Voltage in Volt
    Serial.print(result);
    Serial.print("\t");
    Serial.print(voltage);
    Serial.print("\t");
    Serial.println(gain, precision);
    
  }*/
  if (result == 2){
    tempVoltage = ADS.getVoltage();
    if (temp == 0) temp = convertTemperature(tempVoltage, batteryVoltage);
    temp = 0.33*convertTemperature(tempVoltage, batteryVoltage)+0.67*temp;
  }
  if (result == 7){
    current = 5*ADS.getVoltage(); //0.2ohm shunt => 1v = 5A
  }
  if (result == 3){
    batteryVoltage = ADS.getVoltage();
  }
  //heater pwm calc
  if (state == 1) computePID();
  else duty = 0;
  #ifdef DEBUG_SERIAL
    logTimeElapsed = millis() - logTimeBefore;
    if (logTimeElapsed > 500)  {
      Serial.println("set = " + String(setpoint) + "\t temp = " + String(temp) + "\t duty = " + String(duty) + "\t proportional = " + String(proportional) + "\t derivative = " + String(derivative)+ "\t integral = " + String(integral) + "\t current = " + String(current) + "\t Vdd = " + String(Vdd) + "\t voltage = " + String(batteryVoltage) +  "\t time = " + String(millis()));
      logTimeBefore += 500;
    }
  #endif
    
  ledcWrite(LEDC_CHANNEL_0, duty);
  
  //mode control
  if (state <= 100 && state >= 20){ //temp control over BT
    setpoint = state;
    if (digitalRead(ledRPin)) state = 1; //if it was heating before, keep heating.
  }
  if (state == 252) {
    digitalWrite(ledRPin, HIGH); // Turn LED OFF
    state = 0;
  }
  else if (state == 251) {
    digitalWrite(ledRPin, LOW);
    state = 1;
    integral = 0;
    derivative = 0;
    diff = setpoint-temp;
    oldDiff = diff;
    oldTime = millis();
  } 

}

//------------------------------------------------------------------------------------------------------------------------------------------------------//

//Function to send serial data over bluetooth
void sendBTData(){
    if(digitalRead(ledRPin) == LOW ){
      SerialBT.print("LED: ON;");
    }
    else {
      SerialBT.print("LED: OFF;");
    }
    SerialBT.println("C = " + String(temp));
    //Serial.println("setpoint = " + String(setpoint) + "\t temp = " + String(temp) + "\t bat = " + String(batteryVoltage)); //debugging information
}

//------------------------------------------------------------------------------------------------------------------------------------------------------//

//Function to receive serial data over bluetooth
void receiveBTData(){
  if(SerialBT.available() > 0){ // Checks whether data is comming from the serial port
    state = SerialBT.read(); // Reads the data from the serial port
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------//
/*
//Function to read temperature
void readTemp(){
  temp = thermocouple->readCelsius();
}*/ //this was for thermocouple, now using thermistor

//------------------------------------------------------------------------------------------------------------------------------------------------------//
float convertTemperature(float voltage, float vdd){
  float resistance;
  float steinhart;
  if (voltage == 0) return 0;
  if (vdd == 0) return 0;
  resistance = SERIESRESISTOR / ((vdd / voltage)-1);
  steinhart = resistance / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;
  return steinhart;      
}

//------------------------------------------------------------------------------------------------------------------------------------------------------//

//PID function
void computePID(){
  newTime = millis();
  interval = newTime-oldTime;
  if (interval >= PID_PERIOD){
    oldDiff = diff;
    diff = setpoint - temp;
    proportional = P*diff;
    if (abs(diff) < 2) integral += diff * I * interval;
    if (abs(diff) > 10) integral = 0;
    derivative = 0.2*((oldDiff - diff) * D / interval) + 0.8*derivative;
    if (integral > 4096) integral = 4096;
    if (integral < -4096) integral = -4096;
    if (derivative > 4096) derivative = 4096;
    if (derivative < -4096) derivative = -4096;
    duty = proportional + integral - derivative; 
    if (duty < 0) duty = 0;
    if (duty > 4096) duty = 4096;
    if (!(temp > 10 && temp < 90)) duty = 0;
    oldTime = newTime;
  }  
}

/*//------------------------------------------------------------------------------------------------------------------------------------------------------//

void updateLCD(){
  
  oled.setTextXY(0,0);              // Set cursor position, start of line 0
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
  
  
}
*/
int minSecToMs(int minutes, int seconds){
  return (minutes*60+seconds)*1000;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------//

void IRAM_ATTR buttonUpISR(){
  upButtonPressed = true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------//'

void IRAM_ATTR buttonDownISR(){
  downButtonPressed = true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------//'

void IRAM_ATTR buttonOkISR(){
  okButtonPressed = true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------//'
