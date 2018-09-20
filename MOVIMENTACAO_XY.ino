#include <AccelStepper.h>
int velocidade_motor = 600; //400
int aceleracao_motor = 20000; //20000
int sentido_horario = 0;
int sentido_antihorario = 0;
int numero = 0;

int esquerda = A0;
int direita = A1;

int sensor_x_max = 11;
int sensor_x_min = 12;

int estado_esquerda = 0;
int estado_direita = 0;

int estado_x_max = 1;
int estado_x_min = 1;

// Definicao pino ENABLE
int pino_enable = 4;
int pino_enableB = 7;

// Definicao pinos STEP e DIR
AccelStepper eixo_x(1,3,2);
AccelStepper eixo_xB(1,6,5);

void setup() {

  Serial.begin(9600);
  pinMode(pino_enable, OUTPUT);
  pinMode(pino_enableB, OUTPUT);
  digitalWrite(pino_enable, HIGH);
  digitalWrite(pino_enableB, HIGH);
  
  // Configuracoes iniciais motor de passo
  eixo_x.setMaxSpeed(velocidade_motor);
  eixo_x.setSpeed(velocidade_motor);
  eixo_x.setAcceleration(aceleracao_motor);

  eixo_xB.setMaxSpeed(velocidade_motor);
  eixo_xB.setSpeed(velocidade_motor);
  eixo_xB.setAcceleration(aceleracao_motor);

  pinMode(esquerda, INPUT);
  pinMode(direita, INPUT);
  pinMode(sensor_x_max, INPUT);
  pinMode(sensor_x_min, INPUT);

}

void loop() {
  estado_esquerda = digitalRead(esquerda);
  estado_direita = digitalRead(direita);
  checa_sensor_x();
  

  while (estado_direita == 1 && estado_x_max == 0) {
    estado_direita = digitalRead(direita);
    checa_sensor_x();
    gira_direita();
    
  }
  
  while (estado_esquerda == 1 && estado_x_min == 0) {
    estado_esquerda = digitalRead(esquerda);
    checa_sensor_x();
    gira_esquerda();
        
  }

  eixo_x.moveTo(0);
  digitalWrite(pino_enable, HIGH);
  digitalWrite(pino_enableB, HIGH);
  

}

//FIM DA VOID LOOP

//INICIO FUNCOES AUXILIARES

void checa_sensor_x(){
  estado_x_max = digitalRead(sensor_x_max);
  estado_x_min = digitalRead(sensor_x_min);

}

void gira_direita() {
  digitalWrite(pino_enable, LOW);
  digitalWrite(pino_enableB, LOW);
  eixo_x.moveTo(10000);
  eixo_xB.moveTo(10000);
  eixo_x.run();
  eixo_xB.run();
    
}

void gira_esquerda() {
  digitalWrite(pino_enable, LOW);
  digitalWrite(pino_enableB, LOW);
  eixo_x.moveTo(-10000);
  eixo_xB.moveTo(-10000);
  eixo_x.run();
  eixo_xB.run();  
 
}

