//Pin definitions
#define ledRPin     26 //heating status indicator
#define ledGPin     25
#define ledBPin     27
#define ENC_A       12
#define ENC_B       13 
#define ENC_SW      15
#define buzzerPin   14


#define DEBUG_SERIAL




//Periodic event timer periods
#define SEND_PERIOD 0.25
#define TEMP_READ_PERIOD 0.5
#define PID_PERIOD 1
#define LCD_UPDATE_PERIOD 0.5

//PWM definitions for heater
#define LEDC_CHANNEL_0     0
#define LEDC_TIMER_12_BIT  12
#define LEDC_BASE_FREQ     1000
#define HEATER_PIN         33

//thermistor temperature calculation parameters
#define THERMISTORNOMINAL 10000      
#define TEMPERATURENOMINAL 25   
#define BCOEFFICIENT 3900
#define SERIESRESISTOR 33000

//PRESETS
#define PRESET1_NAME "PRESET1"
#define PRESET1_TEMP 30
#define PRESET1_TIME 30

#define PRESET2_NAME "PRESET2"
#define PRESET2_TEMP 40
#define PRESET2_TIME 30

#define PRESET3_NAME "PRESET3"
#define PRESET3_TEMP 50
#define PRESET3_TIME 30

#define PRESET4_NAME "PRESET4"
#define PRESET4_TEMP 60
#define PRESET4_TIME 30

#define PRESET5_NAME "PRESET5"
#define PRESET5_TEMP 70
#define PRESET5_TIME 30 

#define PRESET6_NAME "PRESET6"
#define PRESET6_TEMP 70
#define PRESET6_TIME 30 
