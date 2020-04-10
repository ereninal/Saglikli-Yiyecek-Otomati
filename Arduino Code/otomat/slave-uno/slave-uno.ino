#include <SPI.h>
#include <SD.h>

#define CS_PIN 10
File data;
void setup() {
  String post_data="";
  Serial.begin(9600);
  SPI.begin();
  SD.begin(CS_PIN);
  if (!SD.begin(CS_PIN)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void loop() {
  
  data = SD.open("student.txt");
  if(data)
  {
    while(data.available())
    {
     Serial.write(data.read());
     //Serial.println(" ");
    }
    Serial.println(" ");
  }
  
  data.close();
  delay(1000);
  
  

}
