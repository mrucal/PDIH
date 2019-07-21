// Mario Ruiz Calvo 05/05/2017

#include <EEPROM.h>

int sensorPin = A0;

int lecturaEEPROM = 0; // Contador que indica la posición de la EEPROM en la que nos encontramos.
int direccion = 0; // Dirección de la EEPROM.

// Función que obtiene la temperatura en grados centígrados a partir de la lectura del sensor pasada por parámetro.
float calcularTemperatura(float lectura){ 
  return ((lectura*5/1024)-0.5)/0.01;  
}

// Función que muestra por el puerto serie todas las temperaturas que se han escrito hasta el momento en la EEPROM
void leerEEPROM(){
  float temperatura = 0;
  int direccion_lectura = 0; // Dirección auxiliar para recorrer toda la EEPROM
  Serial.println("Lectura EEPROM:");
  for(int i = 0; i < lecturaEEPROM; i++){ // Leer hasta la última posición escrita.
    EEPROM.get(direccion_lectura, temperatura); // Obtener la temperatura de la EEPROM
    // Mostrar por el puerto serie el número de lectura y la temperatura obenida
    Serial.print(i);
    Serial.print(": ");
    Serial.println(temperatura);
    direccion_lectura += sizeof(float); // Actualizar dirección auxiliar
  }  
}

// Función para obtener una temperatura, y almacenarla en la EEPROM
void escribirEEPROM(){
  if (lecturaEEPROM < 128){ // Controlar que se han hecho menos de 128 escrituras para no llenar la EEPROM
    EEPROM.put(direccion, calcularTemperatura(analogRead(sensorPin))); // Escribir la temperatura obtenida a partir de la lectura del sensor
    lecturaEEPROM ++; // Actualizar el número de escrituras
    direccion += sizeof(float); // Actualizar la dirección actual
  }  
}

// Función para obtener 50 temperaturas a intervalos de 15 minutos y almacenarlos en la EEPROM
void escribirEEPROM_auto(){
  int temperatura;
  for (int i=0; i< 50; i++){
    if (lecturaEEPROM < 128){ // Controlar que se han hecho menos de 128 escrituras para no llenar la EEPROM
      temperatura = calcularTemperatura(analogRead(sensorPin)); // Obtener temperatura a partir de la lectura del sensor 
      EEPROM.put(direccion, temperatura); // Escribir la temperatura obtenida
      // Mostrar por el puerto serie el número de lectura y la temperatura obenida
      Serial.print(i);
      Serial.print(": ");
      Serial.println(temperatura);
      lecturaEEPROM ++; // Actualizar el número de escrituras
      direccion += sizeof(float); // Actualizar la dirección actual
      // Esperar 15 minutos
      for(int j = 0; j < 60; j++)
        for(int k = 0; k < 15; k++)
          delay(1000);
    }
  }  
}

// Función que borra todas los datos de la EEPROM
void borrarEEPROM(){
  // Escribir un 0 en cada posicion de la EEPROM
  for(int i = 0; i < EEPROM.length(); i++){
    EEPROM.write(i, 0);
  }
  // Reiniciar el indice de la EEPROM y la dirección
  lecturaEEPROM = 0;
  direccion = 0;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Leer del puerto serie una orden
  switch(Serial.read()){
    // Si se ha pulsado r/R mostrar el contenido de la EEPROM por el puerto serie
    case 'r':
    case 'R':
      leerEEPROM();
      break;
    // Si se ha pulado w/W obtener temperatura y escribirla en la EEPROM
    case 'w':
    case 'W':
      escribirEEPROM_auto();
      //escribirEEPROM();
      break;
    // Si se ha puslado b/B borrar el contenido de la EEPROM
    case 'b':
    case 'B':
      borrarEEPROM();
      break;
  }
}
