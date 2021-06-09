#include <SparkFun_TB6612.h>
#include <Wire.h>
#include <VL53L0X.h>

//definindos os pinos para controle da ponte h
#define AIN1 1
#define BIN1 4
#define AIN2 0
#define BIN2 5
#define PWMA 3
#define PWMB 6
#define STBY 2

// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

//criando um objeto para cada motor
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);



void setup() {
}

void loop() {

  motor1.drive(250);
  motor2.drive(250);
  delay(1000);
  motor1.drive(-100);
  motor2.drive(-100);
  delay(1000);
}
