// Mario Ruiz Calvo 05/05/2017

int leds[7] = {3,4,5,6,7,8,9}; // Pin para leds del dado
int boton = 11; // Botón para hacer una tirada

void apagar_todos(){
  for(int i=0;i<7;i++)
    digitalWrite(leds[i], HIGH);
}

// Funciones que apagan y encienden los leds correspondientes para mostrar el número indicado
void muestra_uno(){
  apagar_todos();
  digitalWrite(leds[3], LOW);
}

void muestra_dos(){
  apagar_todos();
  digitalWrite(leds[4], LOW);
  digitalWrite(leds[2], LOW);
}

void muestra_tres(){
  apagar_todos();
  digitalWrite(leds[4], LOW);
  digitalWrite(leds[2], LOW);
  digitalWrite(leds[3], LOW);
}

void muestra_cuatro(){
  apagar_todos();
  digitalWrite(leds[4], LOW);
  digitalWrite(leds[2], LOW);
  digitalWrite(leds[0], LOW);
  digitalWrite(leds[6], LOW);
}

void muestra_cinco(){
  apagar_todos();
  digitalWrite(leds[4], LOW);
  digitalWrite(leds[2], LOW);
  digitalWrite(leds[0], LOW);
  digitalWrite(leds[6], LOW);
  digitalWrite(leds[3], LOW);
}

void muestra_seis(){
  apagar_todos();
  digitalWrite(leds[4], LOW);
  digitalWrite(leds[2], LOW);
  digitalWrite(leds[0], LOW);
  digitalWrite(leds[6], LOW);
  digitalWrite(leds[1], LOW);
  digitalWrite(leds[5], LOW);
}

// Función que muestra el número indicado como parámetro
void MostrarNumero(int i){
  Serial.println(i); // Imprimir por el puerto serie el número que se va a mostrar
  switch(i){
    case 1:
      muestra_uno();
      break;
    case 2:
      muestra_dos();
      break;
    case 3:
      muestra_tres();
      break;
    case 4:
      muestra_cuatro();
      break;
    case 5:
      muestra_cinco();
      break;
    case 6:
      muestra_seis();
      break;      
  }
}

// Función para realizar una tirada de 200 números elegidos al azar.
void ProbadorDado(){
  apagar_todos();
  Serial.println("Tirada:");
  for(int i=0;i<200;i++){
    MostrarNumero(random(1,7));
    delay(100);
  }
}

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  for(int i=0;i<7;i++)
    pinMode(leds[i],OUTPUT);
  pinMode(boton,INPUT);
  apagar_todos();
  ProbadorDado();
}

void loop() {}
