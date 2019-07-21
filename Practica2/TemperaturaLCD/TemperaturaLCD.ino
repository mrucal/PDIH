// Mario Ruiz Calvo 05/05/2017

#include <EEPROM.h>
#include <LiquidCrystal.h>

// Pines necesarios para la pantalla LCD
int sensorPin = A0; 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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
  int i;
  for(i = 0; i < lecturaEEPROM; i++){ // Leer hasta la última posición escrita.
    EEPROM.get(direccion_lectura, temperatura); // Obtener la temperatura de la EEPROM
    // Mostrar por el puerto serie el número de lectura y la temperatura obenida
    Serial.print(i);
    Serial.print(": ");
    Serial.println(temperatura);

    // Posicionar el cursor de la pantalla para imprimir la temperatura y el número de lecturas
    lcd.setCursor(0, 0); 
    lcd.print("Temp.: ");
    lcd.print(temperatura);
    lcd.print("      ");
    lcd.setCursor(0, 8);
    lcd.print("Lecturas: ");
    lcd.print(lecturaEEPROM);
    lcd.print("      ");

    direccion_lectura += sizeof(float); // Actualizar dirección auxiliar
  }  

  if(!i){
    lcd.setCursor(0, 0);
    lcd.print("Temp.: ---");    
    lcd.print("      ");
    lcd.setCursor(1, 8);
    lcd.print("Lecturas: 0");
    lcd.print("      ");
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

// Función que borra todas los datos de la EEPROM y lo muestra en la pantalla LCD
void borrarEEPROM(){
  // Escribir un 0 en cada posicion de la EEPROM
  for(int i = 0; i < EEPROM.length(); i++){
    EEPROM.write(i, 0);
  }
  // Reiniciar el indice de la EEPROM y la dirección
  lecturaEEPROM = 0;
  direccion = 0;
  // Mostrar en la pantalla LCD que se ha borrado la EEPROM
  lcd.setCursor(0, 0);
  lcd.print("Borrado EEPROM");    
  lcd.print("      ");
  lcd.setCursor(0, 8);
  lcd.print("Lecturas: 0");
  lcd.print("      ");
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Inicializar la pantalla LCD
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
      escribirEEPROM();
      break;
    // Si se ha puslado b/B borrar el contenido de la EEPROM
    case 'b':
    case 'B':
      borrarEEPROM();
      break;
  }
}
