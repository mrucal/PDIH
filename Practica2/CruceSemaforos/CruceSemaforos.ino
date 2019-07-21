// Mario Ruiz Calvo 05/05/2017

const int s1[3] = {3,4,5};
const int s2[3] = {6,7,8};
enum estado {R,A,V};

int led_modo = 10; // Pin para led que indica el modo. ENCENDIDO = automatico APAGADO = manual
int led_semaforo = 11; // Pin para led que indica el semaforo que esta en rojo en modo manual. ENCENDIDO = semaforo 1 rojo APAGADO = semaforo 2 rojo

int boton_modo = 2; // Pin del boton para cambiar de modo. (Pin 2 para interrupciones)
int boton_semaforo = 12; // Pin del boton para cambiar de semaforo en el modo manual

volatile bool modo = true; // TRUE = automatico FALSE = manual (Es volatile para que en cada aparicion de la variable se compruebe si se ha modificado el valor (mediante interrupción))
bool semaforo = true; // TRUE = semaforo 1 rojo FALSE = semaforo 2 rojo

void apagar_semaforos(){for (int i=0; i<3; i++){
    digitalWrite(s1[i], HIGH);  
    digitalWrite(s2[i], HIGH);    
  }   
}

// Funcion que cambia de modo
/*int bm_antrior=HIGH;
void CambiarModo(){
  int  bm_actual = digitalRead(boton_modo);
  if( bm_actual == LOW && bm_antrior == HIGH){ // Se ha pulsado el boton de modo
    digitalWrite(led_modo, modo); // Cambiar led de modo
    modo = !modo; // Cambiar modo
    bm_antrior = LOW; // Acualizar estado del boton de modo
    apagar_semaforos();
    // Preparar modo manual
    digitalWrite(s1[R], LOW); // Poner el semaforo 1 a rojo
    digitalWrite(s2[V], LOW); 
    semaforo = true; // Indicar que el primer semaforo esta encendido
    digitalWrite(led_semaforo, modo); // Encender led de semaforo
  }else
  if(bm_actual == HIGH && bm_antrior == LOW){
    bm_antrior=HIGH;
  }
}*/

void CambiarModo(){
    digitalWrite(led_modo, modo); // Cambiar led de modo
    modo = !modo; // Cambiar modo
    apagar_semaforos();
    // Preparar modo manual
    digitalWrite(s1[R], LOW); // Poner el semaforo 1 a rojo
    digitalWrite(s2[V], LOW); 
    semaforo = true; // Indicar que el primer semaforo esta encendido
    digitalWrite(led_semaforo, modo); // Encender led de semaforo
}

// Cambia el semaforo que esta a verde a rojo y viciversa. Si en algun punto se cambia de modo, para la ejecucion
void cambiar_trafico_automatico(const int s1[],const int s2[]){
  apagar_semaforos();
  if(!modo) return;
  digitalWrite(s1[R], LOW);
  if(!modo) return;
  digitalWrite(s2[V], LOW);
  if(!modo) return;
  delay(3000); 
  if(!modo) return;
  digitalWrite(s2[V], HIGH);
  if(!modo) return;
  digitalWrite(s2[A], LOW);
  if(!modo) return;
  delay(500);   
  if(!modo) return;
  digitalWrite(s2[A], HIGH);
  if(!modo) return;
  digitalWrite(s1[R], HIGH);
  if(!modo) return;
}

void modo_automatico(){
  apagar_semaforos(); 
  digitalWrite(led_semaforo, HIGH); // Apaga el led que indica el semaforo
  cambiar_trafico_automatico(s1,s2);
  cambiar_trafico_automatico(s2,s1);
}

// Cambia el semaforo que esta a verde a rojo y viciversa.
void cambiar_semaforo(const int s1[],const int s2[]){
  digitalWrite(s2[V], HIGH);
  digitalWrite(s2[A], LOW);
  delay(500);   
  digitalWrite(s2[A], HIGH);
  digitalWrite(s1[R], HIGH);
  digitalWrite(s2[R], LOW);
  digitalWrite(s1[V], LOW);
}

int estadoAnterior_botonSemaforo = LOW;
void ModoManual(){
  int  estadoActual_boton_semaforo = digitalRead(boton_semaforo);

  if( estadoActual_boton_semaforo == LOW && estadoAnterior_botonSemaforo == HIGH){ // Se ha pulsado el boton de semaforo 
    if(semaforo){ // Semaforo 1 rojo. Se cambia a verde.
      digitalWrite(led_semaforo, HIGH);
      cambiar_semaforo(s1,s2);
    }else{ // Semaforo 2 rojo. Se cambia a verde.
      digitalWrite(led_semaforo, LOW);
      cambiar_semaforo(s2,s1);
    }
    semaforo = !semaforo; // Cambiar semaforo
    estadoAnterior_botonSemaforo=LOW; // Acutalizar el estado anterior del boton de semaforo
  }else
  if(estadoActual_boton_semaforo == HIGH && estadoAnterior_botonSemaforo == LOW){
    estadoAnterior_botonSemaforo=HIGH;
  }
}

void setup() {
  for (int i=0; i<3; i++){
    pinMode(s1[i], OUTPUT);
    pinMode(s2[i], OUTPUT);
  }
  pinMode(led_modo, OUTPUT);
  pinMode(led_semaforo, OUTPUT);
  pinMode(boton_modo, INPUT_PULLUP);
  pinMode(boton_semaforo,INPUT);
  attachInterrupt(digitalPinToInterrupt(boton_modo), CambiarModo, RISING); // Definir una interrupcion que llamará a la funcion CambiarModo cuando se pulse el boton_modo
  apagar_semaforos(); 
  digitalWrite(led_modo, !modo); // Encender led modo para indicar que empieza en automatico
  digitalWrite(led_semaforo, HIGH); // Apagar el led de semaforo porque no empieza en modo manual
}

void loop() {
  if(modo)
    modo_automatico();
  else
    ModoManual();  
}
