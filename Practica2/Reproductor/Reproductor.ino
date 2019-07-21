// Mario Ruiz Calvo 05/05/2017

#include "pitches.h"

int pinBuzzer = 8; // Pin para el Buzzer

int pinBoton = 2; // Pin para el boton (Pin 2 para interrupciones)

volatile bool play = true; // Indicar que se esta reproduciendo la cancion. TRUE = play FALSE = pause. (Es volatile para que en cada aparicion de la variable se compruebe si se ha modificado el valor (mediante interrupción))

int i=0;

int mario[] = { // melodia
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};
int mario_duracion[] = { // duraciones de cada nota
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

void Play_Pause(){
  play = !play; // Activar el play/pausa. TRUE = play FALSE = pausa
}

void setup() {Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(pinBoton), Play_Pause, FALLING); // Definir una interrupcion que llamará a la funcion que indica el play y la pausa
}

int *melodia = mario, *duracion = mario_duracion, n = sizeof(mario) / sizeof(int);;
void loop() {
  int duracion_act, pausa_entre_notas;

  // Si el boton no ha activado la pausa
  if(play) {
    // Calcular la duracion de la nota
    duracion_act = 1000 / duracion[i];
    // Hacer que suene la nota
    tone(pinBuzzer, melodia[i], duracion_act);      
    pausa_entre_notas = duracion_act * 1.30;
    // Hacer una pausa entre nota y nota
    delay(pausa_entre_notas);
    noTone(pinBuzzer);
    if(i==n-1) {i=0; delay(2000);} // Si se ha llegado al final de la melodia, esperar 2 segundos y empezar desde el principio
    else i++; // Siguiente nota
 }  
}
