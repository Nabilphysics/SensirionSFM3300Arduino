/*
  Sensirion SFM3300 Flow Sensor interfacing
  Syed Razwanul Haque(Nabil), https://github.com/Nabilphysics/SensirionSFM3000Arduino/
  https://www.nabilbd.com
  https://www.cruxbd.com
  Sensor Datasheet: https://www.sensirion.com/fileadmin/user_upload/customers/sensirion/Dokumente/5_Mass_Flow_Meters/Datasheets/Sensirion_Mass_Flow_Meters_SFM3300_Datasheet.pdf
  Credit:
  Modified From: https://www.14core.com/wiring-sfm3000-air-gas-flow-meter/
*/
#include <Wire.h>
#include "SFM3300.h"

SFM3300 sensirionFlow(64);
//Left to Right- VDD,SCL(A5),GND,SDA(A4)
long int sensirion3300Offset = 32768; // Offset for Sensirion 3300 Flow Sensor
float scaleFactor = 120.0; //For Air
uint8_t sensorPowerPin = 5; // Since Sensor only consume 5mw power we could power it from Microcontroller Pin, You may use Transistor Switching
int ret;
void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(sensorPowerPin, OUTPUT);
  sensirionFlow.hardReset(sensorPowerPin);
  delay(1000); 
  sensirionFlow.init();
  delay(1000);
  Serial.println("Sensor initialized!");
  
}

void loop() {
 /////////// Flow /////////////// 
  unsigned int result = sensirionFlow.getvalue();
  float flow = (float(result) - sensirion3300Offset) / scaleFactor;
  Serial.println(flow);
  delay(100);

  if(flow < -270.00){
  sensirionFlow.softReset(); 
  sensirionFlow.init();
  delay(1000);
  }

  

/*
////////////////// Temp /////////////
unsigned int temp = sensirionFlow.tempRead();
float actualTemp = (float(temp) - 20000)/100;
  Serial.print("temp= ");
  Serial.println(actualTemp);
  delay(100);

  */
  

}
