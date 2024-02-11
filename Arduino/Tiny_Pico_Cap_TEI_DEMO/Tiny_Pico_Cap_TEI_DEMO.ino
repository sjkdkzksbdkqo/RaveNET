/* TODO LIST
  # Figuring the range of the sensors (HB & Z-Axis) to have max amplitidue at the 8bit dac output
  # Integrate push buttons output
  # Have the GSR multiply / divide the HB (must figure GSR range then)
  # Offset must be dynamic to adapt to body movement (range of the sensor is kinda static)
  # write down every sensor range 
*/
#include <Wire.h>
#include "TinyPICO.h"

TinyPICO tp = TinyPICO();

int debugMode;

int EMG;
int x_axis;
int y_axis;
int z_axis;
int DAC_Out_1;
int DAC_Out_2;

void setup() {
  Serial.begin(115200);   // baud rate 

  debugMode = 0;          // Setting up the debugMode (to stream data via serial)
}


void loop() {

  tp.DotStar_CycleColor(25); // shiny shiny LED

  // Getting the reading of the sesnors
  int EMG = analogRead(4);
  int x_axis = analogRead(14);
  int y_axis = analogRead(15);
  int z_axis = analogRead(27);
  //*/

// Normalizing sensor value to an 8 bit range for DAC Output

  unsigned long DAC_Out_1_min = 0;
  unsigned long DAC_Out_1_max = 1000;
  unsigned long DAC_Value_1 = EMG;  // L
  DAC_Value_1 = constrain(DAC_Value_1, DAC_Out_1_min, DAC_Out_1_max);
  DAC_Out_1 = map(DAC_Value_1, DAC_Out_1_min, DAC_Out_1_max, 0, 255);

  unsigned long DAC_Out_2_min = 360;
  unsigned long DAC_Out_2_max = 700;
  unsigned long DAC_Value_2 = x_axis;  // L
  DAC_Value_2 = constrain(DAC_Value_2, DAC_Out_2_min, DAC_Out_2_max);
  DAC_Out_2 = map(DAC_Value_2, DAC_Out_2_min, DAC_Out_2_max, 0, 255);

  // --- DAC output (8bit) --- //
  dacWrite(25,DAC_Out_1);
  dacWrite(26,DAC_Out_1);
  //dacWrite(26,DAC_Out_2);
  

    // Data to serial for debug //
  if (debugMode == 1){
    Serial.printf("%i,%i,%i,%i,%i,%i",
      (int)EMG,
      (int)x_axis,
      (int)y_axis,
      (int)z_axis,
      (int)DAC_Out_1,
      (int)DAC_Out_2
    );
    Serial.println();
  }

  // delay
  if (debugMode == 1){
    delay(50); // delay for visibility in the plotter 
  }
  else{
    delay(2); // smol delay to prevent data overide
  }
}
