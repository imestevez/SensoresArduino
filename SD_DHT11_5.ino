

#include "DHT.h"
#include <SD.h>


#define DHTPIN 2     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)



DHT dht(DHTPIN, DHTTYPE);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

File myFile;

void setup() {
  Serial.begin(9600); 
  if (!SD.begin(53)) {
                      Serial.println("ERROR INICIO");
                       Serial.println();
                        return;
  }
   while (!Serial) {
    
  }
   pinMode(53, OUTPUT);
 
  dht.begin();
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:

   Serial.println("Pulsa R para LEER");
   Serial.println("Pulsa W para ESCRIBIR");
   Serial.println("Pulsa L para LEER SD");
   Serial.println("Pulsa E para SALIR");
   Serial.println();
}


void loop() {

//  float h = dht.readHumidity();
  float t = dht.readTemperature();


  if (stringComplete) {
    Serial.println(inputString); 
    // clear the string:
   
    stringComplete = false;
  }
  
  while (Serial.available()) {
    // get the new byte:
    char A = (char)Serial.read();


    inputString += A;

    if (A == 'R') {
     
            Serial.println("LECTURA:");
            Serial.print("Temperatura= ");
            Serial.print(t);
            Serial.println(" *C");
            Serial.println();
    } 
  else if (A == 'W')
  {
            Serial.println("ESCRITURA:");
            Serial.print("Temperatura= ");
            Serial.print(t);
            Serial.println(" *C");
             Serial.println();

             Serial.println("Desea GUARDAR los datos?");
               Serial.println();
             Serial.print("Pulsar S para GUARDAR");
             Serial.println("\t Pulsar N para NO GUARDAR");
  }
  if (A == 'S')
  {
               Serial.println("Datos Guardados");       

            
               myFile = SD.open("VIERNES.txt", FILE_WRITE);
               if(myFile) {

                  myFile.print("Temperatura= ");
                  myFile.print(t);
                  myFile.println(" *C");
                  myFile.close();
   }
  }

 else if (A == 'N')
           {
             Serial.println("Datos NO Guardados");   
                 myFile.close();         
  
      }
  

      else if (A == 'L')
      {

       Serial.println("Lectura SD:");
      myFile = SD.open("VIERNES.txt");

  if (myFile) {
    Serial.println("SD TEST:");
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
    	Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
  	// if the file didn't open, print an error:
    Serial.println("ERROR SD TEST");
  }
      }
  else if (A == 'E')
  {
                   Serial.println("FIN");
  }
/* else
 {
                    Serial.println(" ELIJA LA OPCION CORRECTA !");
   }*/
Serial.println();
  }

  }
  

