#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

// This code is intended for outputin the z_axis an 8 bit value // 

int GSR;
int Heart;
int x_axis;
int y_axis;
int z_axis;
int DAC_Out_1;

void setup() {

  Serial.begin(115200);   // baud rate 
  Serial.println("Initializing...");  // init process for the i2C

  // Initialize sensor
  /*
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  //Setup to sense a nice looking saw tooth on the plotter
  byte ledBrightness = 0x1F; //Options: 0=Off to 255=50mA
  byte sampleAverage = 8; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 3; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  int sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings

  //Take an average of IR readings at power up
  const byte avgAmount = 64;
  long baseValue = 0;
  for (byte x = 0 ; x < avgAmount ; x++)
  {
    baseValue += particleSensor.getIR(); //Read the IR value
  }
  baseValue /= avgAmount;

  //Pre-populate the plotter so that the Y scale is close to IR values
  for (int x = 0 ; x < 500 ; x++)
    Serial.println(baseValue);
  */
}


void loop() {
  
  // --- Getting the reading of the sensors --- //
  //int Heart = (particleSensor.getIR());  
  //int EMG = analogRead(24);
  //int GSR = analogRead(27);
  int x_axis = analogRead(15);
  int y_axis = analogRead(14);
  int z_axis = analogRead(4); 

  // --- normalizing signal to an 8-bit value --- //
  unsigned long y_axis_min = 1900; // arbitrary values - to adjust before performance
  unsigned long y_axis_max = 2000;
  y_axis = constrain(y_axis, y_axis_min, y_axis_max);
  int DAC_Out_1 = map(y_axis, y_axis_min, y_axis_max, 0, 255);

  // --- Sending data to plotters --- //
  Serial.print(x_axis);
  Serial.print(",");
  Serial.print(y_axis);
  Serial.print(",");
  Serial.print(z_axis);
  Serial.print(",");
  Serial.print(DAC_Out_1); // z data to plotter
  //Serial.print(Heart); //Send raw data of heartbeat senslor to plotter
  //Serial.print(",");
  //Serial.print(GSR); // GSR data to plotter
  //Serial.print(","); 
  //Serial.print(x_axis); // x data to plotter
  //Serial.print(","); 
  //Serial.print(y_axis); // y data to plotter
  //Serial.print(","); 
  //Serial.print(z_axis); // z data to plotter
  //Serial.print(",");
  //Serial.print(0);
  //Serial.print(",");
  Serial.println();

  dacWrite(26,DAC_Out_1);
  dacWrite(25,DAC_Out_1);

  delay(5);
}
