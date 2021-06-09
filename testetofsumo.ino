#include <SparkFun_TB6612.h>
#include <Wire.h>
#include <VL53L0X.h>


//2 é esquerda 1 é direita


int val1 = 0;           // variable to store the value read
int val2 = 0;

//pinos XSHUT dos sensores são utilizados para poder definir diferentes endereços
#define tof1 7     //XSHUT tof1
#define tof2 13     //XSHUT tof2

//Definindo os enfereços de cada sensor
#define idSensor1 41
#define idSensor2 42

//Criando um objeto para cada sensor
VL53L0X Sensor1;
VL53L0X Sensor2;

void setup(){

  Serial.begin(9600);
  
  pinMode(tof1, OUTPUT);
  pinMode(tof2, OUTPUT);
  
  Wire.begin();
  //definindo endereço do Sensor1
  Sensor1.setAddress(idSensor1);
  pinMode(tof1, INPUT);
  delay(10); //Dando um tempo pra não zoar
  Sensor2.setAddress(idSensor2);
  pinMode(tof2, INPUT);
  delay(10);
 
  //métodos da própria biblioteca utilizados para inicialização
  Sensor1.init();
  Sensor2.init();
  Sensor1.setTimeout(300);
  Sensor2.setTimeout(300);
  Sensor1.startContinuous();
  Sensor2.startContinuous();

}

void loop(){

val1 = Sensor1.readRangeContinuousMillimeters();
val2 = Sensor2.readRangeContinuousMillimeters();

Serial.print(val1);
Serial.print("\t");
Serial.println(val2);
}
