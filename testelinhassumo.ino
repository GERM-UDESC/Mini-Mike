#include <SparkFun_TB6612.h>
#include <Wire.h>
#include <VL53L0X.h>

int linhad = 0;
int linhae = 1;  

int vald = 0;           // variable to store the value read
int vale = 0;

void setup(){ 

  Serial.begin(9600);

}

void loop(){
  vald = analogRead(linhad);    // read the input pin
  vale = analogRead(linhae);

Serial.print(vald);
Serial.print("\t");
Serial.println(vale);

   
}
