#include "Wire.h"
#include "FDC2214.h"
#include "TinyPICO.h"

TinyPICO tp = TinyPICO();

FDC2214 capsense(FDC2214_I2C_ADDR_0); // Use FDC2214_I2C_ADDR_1
int DAC_Out_1;  // DAC L
int DAC_Out_2;  // DAC R

void setup() {
  
  // ### Start I2C 
  Wire.begin();
//  Wire.setClock(400000L);
  
  // ### Start serial
  Serial.begin(115200);
  Serial.println("\nFDC2x1x test");
  
  // ### Start FDC
  // Start FDC2212 with 2 channels init
  //bool capOk = capsense.begin(0x3, 0x4, 0x5, false); //setup first two channels, autoscan with 2 channels, deglitch at 10MHz, external oscillator , 30-40ms
  // Start FDC2214 with 4 channels init
  //bool capOk = capsense.begin(0xF, 0x6, 0x5, false); //setup all four channels, autoscan with 4 channels, deglitch at 10MHz, external oscillator, 90-100ms
  bool capOk = capsense.begin(0x4, 0x5, 0x5, false);  // setup 3 channels, 80ms
  // Start FDC2214 with 4 channels init
//  bool capOk = capsense.begin(0xF, 0x6, 0x5, true); //setup all four channels, autoscan with 4 channels, deglitch at 10MHz, internal oscillator 
  if (capOk) Serial.println("Sensor OK");  
  else Serial.println("Sensor Fail");  

}

// ### Tell aplication how many chanels will be smapled in main loop
#define CHAN_COUNT 3
// capa[0] = R
// capa[1] = L
// capa[2] = F


// ### 
void loop() {
  tp.DotStar_CycleColor(25); // shiny shiny LED

  unsigned long capa[CHAN_COUNT]; // variable to store data from FDC
  for (int i = 0; i < CHAN_COUNT; i++){ // for each channel
    // ### read 28bit data
    capa[i]= capsense.getReading28(i);//  
    // ### Transmit data to serial in simple format readable by SerialPlot application.
    //Serial.print(capa[i]);  
    //if (i < CHAN_COUNT-1) Serial.print(", ");
    //else Serial.println("");
  }
  //capa[0]= capsense.getReading28(0);
  //Serial.println(capa[0]);
  
        //
unsigned long Sensor_Right = capa[0];// R
unsigned long Sensor_Left = capa[1];// L
unsigned long Sensor_Front = capa[2];// F

// Normalizing DAC output value from xxx to a 8 bit range

unsigned long DAC_Out_1_min = 10800000;
unsigned long DAC_Out_1_max = 11000000;
//if(Sensor_Front < DAC_Out_1_min){
// DAC_Out_1_min == Sensor_Front;
//  }
//if(Sensor_Front > DAC_Out_1_max){
//  DAC_Out_1_max == Sensor_Front;
//  };
unsigned long DAC_Value_1 = Sensor_Front;  // 
DAC_Value_1 = constrain(DAC_Value_1, DAC_Out_1_min, DAC_Out_1_max);
unsigned long DAC_Out_1 = map(DAC_Value_1, DAC_Out_1_min, DAC_Out_1_max, 0, 255);

dacWrite(26,DAC_Out_1);
//DAC_Out_2 = capa[0];      // value between 0 and 255
dacWrite(25,DAC_Out_1);

Serial.print(DAC_Out_1);
Serial.print(",");
Serial.print(Sensor_Front);
Serial.print(",");
Serial.print(Sensor_Right);
Serial.print(",");
Serial.println(Sensor_Left);
//delay(20);

// restin R = 24861362, Inhal R = 24662874
}