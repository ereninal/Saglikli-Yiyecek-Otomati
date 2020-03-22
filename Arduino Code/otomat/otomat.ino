#include <LCD5110_Basic.h>
#include <MFRC522.h>
#include <SPI.h>
#include <SD.h>

int ResetPin = 49;
int SDAPin = 53;
byte id[4]={0,0,0,0};
MFRC522 rfid(SDAPin,ResetPin);
File file;
LCD5110 myGLCD(48,47,46,45,44);
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Okuma Başladı..");
  
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  //pinMode(3,OUTPUT);
   
    /*if(!SD.begin(30)) {
    Serial.println("SD Kart Takılı Değil!");
     myGLCD.print("SD Kart Hata",CENTER,16);
    return;
  }*/
 Serial.println("Cihaz Hazir");
 myGLCD.print("Cihaz Hazir.",CENTER,16);
}

void loop() {
   //CardRead();
 //LedYak(1000);
if(rfid.PICC_IsNewCardPresent()){
 CardRead();//yeni kart gelene kadar okuma yapan metot
 //return;
  }
 /*if(!rfid.PICC_IsNewCardPresent())
  return;
 if(!rfid.PICC_ReadCardSerial())//kart oklutulmama durumunda çalışır
    return;
      myGLCD.clrScr();
      CardRead();*/
      rfid.PICC_HaltA();
     delay(5000);
      //delay();
}
void CardRead(){
  String numara;
  rfid.PICC_ReadCardSerial();
  Serial.print("Id Numarasi: ");
  
  for(int i=0;i<4;i++){
    Serial.print(rfid.uid.uidByte[i]);
    numara +=rfid.uid.uidByte[i];
    
    myGLCD.clrScr();
    Serial.print(" ");  
  }
  myGLCD.print(numara,CENTER,16);
 
  Serial.println(" ");
  Serial.println(numara);
  
}
void LedYak(int deger){
    analogWrite(3, 50);
    delay(deger);
    analogWrite(3, 0);
    delay(deger);
  }
