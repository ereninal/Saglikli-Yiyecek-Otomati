#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 49

MFRC522 kart(SS_PIN,RST_PIN);
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  SPI.begin();
  kart.PCD_Init();
  
}

void loop() {
  if(Serial.available()>0)
    {
      Serial.print(Serial.read());
      Serial.println(" ");
      
    }
    else
    {
      Serial.println("Hata alındı."); 
      delay(1000);   
    }
  /*if (!kart.PICC_IsNewCardPresent())
    return;
  if (!kart.PICC_ReadCardSerial()) //kart oklutulmama durumunda çalışır
    return;
  CardRead();
  kart.PICC_HaltA();
  delay(10);*/

}
void CardRead() {
  String numara;
  //kart.PICC_ReadCardSerial();
  Serial.print("Id Numarasi: ");

  for (int i = 0; i < 4; i++) {
    Serial.print(kart.uid.uidByte[i]);
    numara += kart.uid.uidByte[i];
    
    Serial.print(" ");
  }
  
  Serial.println(" ");
  Serial.println(numara);
  delay(100);

}
