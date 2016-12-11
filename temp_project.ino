/*

*/
#include "DHT.h"
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
File myFile;

const int chipSelect = 4;// needed by SD card reader


double myArray[10] = {0.0};
int readings = 0;

void setup() {
    dht.begin();
    //SD.begin();
    Serial.begin(9600);

    Serial.print("Initializing SD card...");

    if (!SD.begin(4)) {
      Serial.print("Initialization failed!");
      return;
      } else{
          Serial.println("initialization done.");  
      }

    if (SD.exists("temp.txt")) {
      Serial.print("temp.txt");
      Serial.print(" file exists.");
      SD.remove("temp.txt");
      Serial.println();
      Serial.print("File removed!");
      Serial.println();
  } else {
      Serial.print("File doesn't exist.");
      Serial.println();
  }
}

void loop() {
  
  double sum = 0.0;
  double average;

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
    
    
    for (int i = 9; i > 0; i--) {
        double x = myArray[i-1];
        myArray[i] = x;
        
    }
    
 myArray[0] = t;
 readings++;

        if (readings < 10) {

          for (int i = 0; i < 10; i++) {
            sum += myArray[i];
            average = sum/ readings;
            }   
          } else {

                for (int i = 0; i < 10; i++) {
                  sum += myArray[i];
                  average = sum / 10;
                }
            }
    
    
    Serial.print("temp: ");
    Serial.println(myArray[0]);
    Serial.print("Sum: ");
    Serial.println(sum);
    Serial.print("readings: ");
    Serial.println(readings);
    Serial.print("Average: ");
    Serial.println(average);
    Serial.println(" ");
    
    Serial.print("myArray[0]: ");
        Serial.println(myArray[0]);
        Serial.print("myArray[1]: ");
        Serial.println(myArray[1]);
        Serial.print("myArray[2]: ");
        Serial.println(myArray[2]);
        Serial.print("myArray[3]: ");
        Serial.println(myArray[3]);
        Serial.print("myArray[4]: ");
        Serial.println(myArray[4]);
        Serial.print("myArray[5]: ");
        Serial.println(myArray[5]);
        Serial.print("myArray[6]: ");
        Serial.println(myArray[6]);
        Serial.print("myArray[7]: ");
        Serial.println(myArray[7]);
        Serial.print("myArray[8]: ");
        Serial.println(myArray[8]);
        Serial.print("myArray[9]: ");
        Serial.println(myArray[9]);
        Serial.println(" ");
        delay(2500);

    //open text file
    myFile = SD.open("temp.txt", FILE_WRITE);
    //myFile.print(" %\t");
    myFile.print("Temperature: ");
    myFile.print(t);
    myFile.println(" *C ");

    //close text file
    myFile.close();
}   
