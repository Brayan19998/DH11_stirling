////////////////////////////////////////////////
////////////// BIOGAS - MATHPHYSICS ////////////
// UNIVERSIDAD NACIONAL ABIERTA Y A DISTACNIA //
////////////////////////////////////////////////
////// POR : FREDDY TORRES, RAFAEL RAMIREZ /////
////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////

int Sensor = A0;
#include "DHT.h"
#include <SD.h>
#define DHTPIN 5 
#define DHTTYPE DHT11   // DHT 11 
// CONFIGURACION POR TIPO SENSOR ABIERTO PARA DHT
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

//CREAR CARPETA  
File myFile;
// LLAMADO DEL SENSOR
DHT dht(DHTPIN, DHTTYPE, 5);

void setup() {
  // BEATS DE TRANSMISION DE DATOS 
  Serial.begin(115200); 
  Serial.println("DHTxx test!");
  Serial.begin(115200);
  Serial.print("Iniciando SD.....");
  // TRANSMISION DE DATOS SD 
  if (SD.begin(4)){
    Serial.println("No se pudo Inicializar");
    return;
    }

    Serial.println("Inicializacion Exitosa");
    // CREAR CARPETA ALMACENADA EN LA SD 
    if (SD.exists("datalog.csv")){
      myFile = SD.open("datalog.csv", FILE_WRITE);
      if(myFile){
        Serial.println("archivo nuevo, escribiendo encabezado (fila 1)");
        myFile.println("tiempo(ms), DH11 1,Sensor_voltaje2,Sensor3");
        myFile.close();
        } else {
          Serial.println("error creando el archivo datalog.csv");
          }
      }
  dht.begin();
}

void loop() {
  float voltaje =  (float)25*analogRead(A0)/1023;
  Serial.print("Voltaje medido =  ");
  Serial.println(voltaje);
  delay(500);
  
  delay(500);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
  
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");

  myFile = SD.open("datalog.csv", FILE_WRITE);//abrimos  el archivo
  
  if (myFile) { 
        Serial.print("Escribiendo SD: ");
        int sensor1 = analogRead(0);
        int sensor2 = analogRead(1);
        int sensor3 = analogRead(2);
        myFile.print(millis());
        myFile.print(",");
        myFile.print(sensor1);
        myFile.print(",");
        myFile.print(sensor2);
        myFile.print(",");
        myFile.println(sensor3);
        
        myFile.close(); //cerramos el archivo
        
        Serial.print("Tiempo(ms)=");
        Serial.print(millis());
        Serial.print(",DH11 1=");
        Serial.print(sensor1);
        Serial.print(",Sensor_voltaje2=");
        Serial.print(sensor2);
        Serial.print(",sensor3=");
        Serial.println(sensor3);       
                    
  
  } else {
    Serial.println("Error al abrir el archivo");
  }
  delay(500);
}
