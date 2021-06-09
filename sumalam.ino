#include <SparkFun_TB6612.h>
#include <Wire.h>
#include <VL53L0X.h>

#define linha0 A0    //Definindo A0 como o sensor de cor da direita 
#define linha1 A1    //Definindo A1 como o sensor de cor da esquerda 

int vira = 0;       //A variável "vira" será usada para escolher para qual lado o robo ira girar, depende de qual foi o último sensor que avistou o robo adversario 
int viralinha = 0;

int valDIR = 0;           // variavel do sensor de distancia da direita
int valESQ = 0;           //variavel do sensor de distancia da esquerda 

//pinos XSHUT dos sensorESQs são utilizados para poder definir diferentes endereços
#define tofDIR 7        //XSHUT tof1
#define tofESQ 13      //XSHUT tof2

//Definindo os enfereços de cada sensor
#define idsensorDIR 41
#define idsensorESQ 42

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
VL53L0X sensorDIR;
VL53L0X sensorESQ;

//criando um objeto para cada motor
Motor motorDIR = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorESQ = Motor(BIN1, BIN2, PWMB, offsetB, STBY);



void setup() {

  pinMode(tofDIR, OUTPUT);
  pinMode(tofESQ, OUTPUT);

  Wire.begin();
  //definindo endereço do Sensor1
  sensorDIR.setAddress(idsensorDIR);
  pinMode(tofDIR, INPUT);
  delay(10); //Dando um tempo pra não zoar
  sensorESQ.setAddress(idsensorESQ);
  pinMode(tofESQ, INPUT);
  delay(10);

  //métodos da própria biblioteca utilizados para inicialização
  sensorDIR.init();
  sensorESQ.init();
  sensorDIR.setTimeout(300);
  sensorESQ.setTimeout(300);
  sensorDIR.startContinuous();
  sensorESQ.startContinuous();

  delay(4000);

}

void loop() {
//  valDIR = analogRead(linha0);    // read the input pin
//  valESQ = analogRead(linha1);




//-------------------------------------- LOGICA DE COMBATE -------------------------------------------------------//


//caso 1: os dois sensores de cor estando no preto//

//if (valDIR > 100 && valESQ > 100){ 
valDIR = sensorDIR.readRangeContinuousMillimeters();
valESQ = sensorESQ.readRangeContinuousMillimeters();

    
    if (valDIR < 500 && valESQ < 500){
      motorESQ.drive(200);
      motorDIR.drive(200);
    }
    
    else if (valDIR > 500 && valESQ < 500){
      motorESQ.drive(100);
      motorDIR.drive(200);
      vira = 1;
    }
    
    else if (valDIR < 500 && valESQ > 500){
      motorESQ.drive(200);
      motorDIR.drive(100);
      vira = 0;
    }
    
    else if (valDIR > 500 && valESQ > 500 && vira == 0){
      motorESQ.drive(110);
      motorDIR.drive(-110);
    }
    
    else {
      motorESQ.drive(-110);
      motorDIR.drive(110);
    }
//  }

//caso 2: esquerda no branco //  
//else if (valDIR > 100 && valESQ < 100){
//   motorESQ.drive(-180);
//   motorDIR.drive(-180);
//   delay(400);
//   motorESQ.drive(-100);
//   motorDIR.drive(100);
//   delay(350);
//  }

//caso 3: direita no branco //
//else {
//   motorESQ.drive(-180);
//   motorDIR.drive(-180);
//   delay(300);
//   motorESQ.drive(100);
//   motorDIR.drive(-100);
//   delay(300);
//  }
}
