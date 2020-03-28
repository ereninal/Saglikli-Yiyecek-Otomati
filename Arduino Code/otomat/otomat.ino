#include <LCD5110_Basic.h>
#include <MFRC522.h>
#include <SPI.h>
#include <SD.h>
//#include <RFID.h>
int ResetPin = 9;
int SsPin = 10;
int CsPin = 8;
byte id[4] = {0, 0, 0, 0};
MFRC522 kart(SsPin, ResetPin);
File file;
LCD5110 myGLCD(48, 47, 46, 45, 44);
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

void setup() {
  Serial.begin(9600);
  SPI.begin();
  SD.begin(CsPin);
  kart.PICC_HaltA();
  kart.PCD_SoftPowerDown();
  //myGLCD.InitLCD();
  //myGLCD.setFont(SmallFont);
  //pinMode(3,OUTPUT);
  if (!SD.begin(CsPin)) {
    Serial.println("SD Kart Takılı Değil!");
    return;
  }
  Serial.println("Cihaz Hazir");
  myGLCD.print("Cihaz Hazir.", CENTER, 16);
  kart.PCD_Init();
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
