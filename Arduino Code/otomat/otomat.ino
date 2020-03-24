#include <LCD5110_Basic.h>
#include <MFRC522.h>
#include <SPI.h>
#include <SD.h>
//#include <RFID.h>
int ResetPin = 8;
int SDAPin = 9;
byte id[4] = {0, 0, 0, 0};
MFRC522 kart(SDAPin, ResetPin);
//RFID rfid(SDAPin, ResetPin);
File file;
LCD5110 myGLCD(48, 47, 46, 45, 44);
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

void setup() {
  Serial.begin(9600);
  /*pinMode(ResetPin,OUTPUT);
    pinMode(SDAPin,OUTPUT);
    pinMode(53,OUTPUT);*/
  SPI.begin();
  kart.PCD_Init();
  Serial.println("Okuma Başladı..");
  //rfid.init();
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  //pinMode(3,OUTPUT);

  delay(1000);
  if (!SD.begin(53)) {
    Serial.println("SD Kart Takılı Değil!");
    myGLCD.print("SD Kart Hata", CENTER, 16);
    return;
  }
  Serial.println("Cihaz Hazir");
  myGLCD.print("Cihaz Hazir.", CENTER, 16);
}

void loop() {
  //CardRead();
  //LedYak(1000);

  //delay(100);
  /*digitalWrite(53,HIGH);//Sd Kart Kesildi
    digitalWrite(9,LOW);//*/

  /*if(rfid.isCard()){
    myGLCD.clrScr();
    myGLCD.print("Kart Okunuyor..",CENTER,16);
    }
    delay(1000);*/

  /*if(kart.PICC_IsNewCardPresent()){
    //myGLCD.clrScr();
    //myGLCD.print("Kart Okunuyor..",CENTER,16);
    delay(100);
    CardRead();//yeni kart gelene kadar okuma yapan metot
    //return;
    }*/

  if (!kart.PICC_IsNewCardPresent())
    return;
  if (!kart.PICC_ReadCardSerial()) //kart oklutulmama durumunda çalışır
    return;
  myGLCD.clrScr();
  CardRead();
  kart.PICC_HaltA();
  delay(10);
  //delay();
}
void CardRead() {
  String numara;
  //kart.PICC_ReadCardSerial();
  Serial.print("Id Numarasi: ");

  for (int i = 0; i < 4; i++) {
    Serial.print(kart.uid.uidByte[i]);
    numara += kart.uid.uidByte[i];

    myGLCD.clrScr();
    Serial.print(" ");
  }
  myGLCD.print(numara, CENTER, 16);
  Serial.println(" ");
  Serial.println(numara);
  delay(100);

}
void LedYak(int deger) {
  analogWrite(3, 50);
  delay(deger);
  analogWrite(3, 0);
  delay(deger);
}
