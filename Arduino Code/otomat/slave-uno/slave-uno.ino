#include <SPI.h>
#include <SD.h>

#define CS_PIN 10

void setup() {
  Serial.begin(9600);
  SPI.begin();
  SD.begin(CS_PIN);
  if (!SD.begin(CS_PIN)) {
    Serial.println("SD Kart Takılı Değil!");
    return;
  }
  Serial.println("Cihaz Hazir");
}

void loop() {
  
  Serial.write("a");
  delay(5);
  
  

}
