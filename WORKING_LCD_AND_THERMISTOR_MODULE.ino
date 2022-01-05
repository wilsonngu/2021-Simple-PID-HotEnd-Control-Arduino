#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>



#include "max6675.h"

//Pins for the SPI with MAX6675
int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

//Pins for the SPI with MAX6675
#define MAX6675_CS   5
#define MAX6675_SO   4
#define MAX6675_SCK  6

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int PWM_pin = 3;  //Pin for PWM signal to the MOSFET driver (the BJT npn with pullup)

/*    i2c LCD Module  ==>   Arduino
 *    SCL             ==>     A5
 *    SDA             ==>     A4
 *    Vcc             ==>     Vcc (5v)
 *    Gnd             ==>     Gnd      */

 
//Variables
float set_temperature = 210;            //Default temperature setpoint. Leave it 0 and control it with rotary encoder

float temperature_read = 0.0;
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev,timetot;
float PID_value = 0;
int button_pressed = 0;
int menu_activated=0;
float last_set_temperature = 0;

//PID constants
//////////////////////////////////////////////////////////
int kp = 40;   int ki = 3;   int kd = 80;//80
//ROSTOCK 36 -3 - 90
//21,3,51-80
//////////////////////////////////////////////////////////

int PID_p = 0;    int PID_i = 0;    int PID_d = 0;
float last_kp = 0;
float last_ki = 0;
float last_kd = 0;

int PID_values_fixed =0;



void setup() {
  pinMode(PWM_pin,OUTPUT);
  TCCR2B = TCCR2B & B11111000 | 0x03;    // pin 3 and 11 PWM frequency of 928.5 Hz
  Time = timetot = millis();
  
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  //delay(500);
}

void loop() {

  // First we read the real value of temperature
  Serial.print("Recent Actual TEMP:");
  temperature_read = readThermocouple();//thermocouple.readCelsius();

  Serial.println(temperature_read);
  //delay(1000);

  //Next we calculate the error between the setpoint and the real value
  PID_error = set_temperature - temperature_read + 5;
  //Calculate the P value
  PID_p = kp * PID_error;
  //Calculate the I value in a range on +-3

  if(PID_error > -3 && PID_error < 3)
  {
    PID_i = PID_i + (ki * PID_error);
  }
  

   //For derivative we need real time to calculate speed change rate
  timePrev = Time;                            // the previous time is stored before the actual time read
  Time = millis();                            // actual time read
  elapsedTime = (Time - timePrev) / 1000; 
  //Now we can calculate the D calue
  PID_d = 0.01*kd*((PID_error - previous_error)/elapsedTime);
  //Final total PID value is the sum of P + I + D
  PID_value = PID_p + PID_i + PID_d;

  //We define PWM range between 0 and 255
  if(PID_value < 0)
  {    PID_value = 0;    }
  if(PID_value > 255)  
  {    PID_value = 255;  }
  Serial.print("Storing new PID value");
  Serial.println(PID_value);
  Serial.println("P val:" +  (String)PID_p);
  Serial.println("I val:" +  (String)PID_i);
  Serial.println("D val:" +  (String)PID_d);
  
  //Now we can write the PWM signal to the mosfet on digital pin D3
  //Since we activate the MOSFET with a 0 to the base of the BJT, we write 255-PID value (inverted)
  analogWrite(PWM_pin,255-PID_value);
  previous_error = PID_error;     //Remember to store the previous error for next loop.

  delay(100); //Refresh rate + delay of LCD print
//   lcd.clear();
   Serial.print("ActualTEMP:"); 
   Serial.print("C = "); 
   Serial.println(temperature_read);
   Serial.print("SET TEMP:"); 
   Serial.print("C = "); 
   Serial.println(set_temperature);
   lcd.clear();
   lcd.print("REAL TEMP:");
   lcd.print(temperature_read);
   lcd.print("C");
   lcd.setCursor(0, 1);
   lcd.print("SET TEMP:");
   lcd.print(set_temperature);
   lcd.print("C");
   if( temperature_read >= set_temperature){
    Serial.print("Time taken total:" ); 
    Serial.print(timetot);
    Serial.println("ms");
    Serial.println("P val:" +  (String)PID_p);
    Serial.println("I val:" +  (String)PID_i);
    Serial.println("D val:" +  (String)PID_d);
    Serial.print("Actual TEMP:"); 
    Serial.print("C = "); 
    Serial.println(temperature_read);
    //delay(1000);
    Serial.print("SET TEMP:"); 
    Serial.print("C = "); 
    Serial.println(set_temperature);
   }
  // delay(250); //Refresh rate + delay of LCD print
   
//   lcd.print("C = ");
//   lcd.print(thermocouple.readCelsius());


//
//  ///////////////////////////////////////////////////////////////////////////OLD 
//  // basic readout test, just print the current temp
//   lcd.clear();
//   Serial.print("C = "); 
//   Serial.println(thermocouple.readCelsius());
//   lcd.print("C = ");
//   lcd.print(thermocouple.readCelsius());
//   Serial.print("F = ");
//   Serial.println(thermocouple.readFahrenheit());
// 
//   // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
//   delay(1000);
}



//The function that reads the SPI data from MAX6675
double readThermocouple() {

  uint16_t v;
  pinMode(MAX6675_CS, OUTPUT);
  pinMode(MAX6675_SO, INPUT);
  pinMode(MAX6675_SCK, OUTPUT);
  
  digitalWrite(MAX6675_CS, LOW);
  delay(1);

  // Read in 16 bits,
  //  15    = 0 always
  //  14..2 = 0.25 degree counts MSB First
  //  2     = 1 if thermocouple is open circuit  
  //  1..0  = uninteresting status
  
  v = shiftIn(MAX6675_SO, MAX6675_SCK, MSBFIRST);
  v <<= 8;
  v |= shiftIn(MAX6675_SO, MAX6675_SCK, MSBFIRST);
  
  digitalWrite(MAX6675_CS, HIGH);
  if (v & 0x4) 
  {    
    // Bit 2 indicates if the thermocouple is disconnected
    return NAN;     
  }

  // The lower three bits (0,1,2) are discarded status bits
  v >>= 3;

  // The remaining bits are the number of 0.25 degree (C) counts
  return v*0.25;
}
