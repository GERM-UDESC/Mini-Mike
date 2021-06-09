#include <SparkFun_TB6612.h>
#include <Wire.h>
#include <VL53L0X.h>

int linha1 = 0;
int linha2 = 1;

int vira = 0;
int viralinha = 0;

int vald = 0;           // variable to store the value read
int vale = 0;

//pinos XSHUT dos sensores são utilizados para poder definir diferentes endereços
#define tofd 7     //XSHUT tof1
#define tofe 13     //XSHUT tof2

//Definindo os enfereços de cada sensor
#define idSensord 41
#define idSensore 42

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

//Criando um objeto para cada sensor
VL53L0X Sensord;
VL53L0X Sensore;

//criando um objeto para cada motor
Motor motord = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motore = Motor(BIN1, BIN2, PWMB, offsetB, STBY);



void setup() {

  pinMode(tofd, OUTPUT);
  pinMode(tofe, OUTPUT);

  Wire.begin();
  //definindo endereço do Sensor1
  Sensord.setAddress(idSensord);
  pinMode(tofd, INPUT);
  delay(10); //Dando um tempo pra não zoar
  Sensore.setAddress(idSensore);
  pinMode(tofe, INPUT);
  delay(10);

  //métodos da própria biblioteca utilizados para inicialização
  Sensord.init();
  Sensore.init();
  Sensord.setTimeout(300);
  Sensore.setTimeout(300);
  Sensord.startContinuous();
  Sensore.startContinuous();

  delay(4000);

}

void loop() {
  vald = analogRead(linha1);    // read the input pin
  vale = analogRead(linha2);


  if (vald > 100 && vale > 100) {

    if (Sensord.readRangeContinuousMillimeters() < 500 && Sensore.readRangeContinuousMillimeters() < 500) {
      motore.drive(200);
      motord.drive(200);

    } else if (Sensord.readRangeContinuousMillimeters() > 500 && Sensore.readRangeContinuousMillimeters() < 500) {
      motore.drive(100);
      motord.drive(200);

      vira = 1;

    } else if (Sensore.readRangeContinuousMillimeters() > 500 && Sensord.readRangeContinuousMillimeters() < 500) {
      motore.drive(200);
      motord.drive(100);

      vira = 0;

    } else if (Sensore.readRangeContinuousMillimeters() > 500 && Sensord.readRangeContinuousMillimeters() > 500 && vira == 0) {
      motore.drive(110);
      motord.drive(-110);
    } else {
      motore.drive(-110);
      motord.drive(110);
    }
  } else if (vald > 100 && vale < 100) {
    motore.drive(-180);
    motord.drive(-180);
    delay(400);
    motore.drive(-100);
    motord.drive(100);
    delay(350);
  } else {
    motore.drive(-180);
    motord.drive(-180);
    delay(300);
    motore.drive(100);
    motord.drive(-100);
    delay(300);

  }



}

