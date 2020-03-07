#include <LCD5110_Basic.h>
#include <MFRC522.h>
#include <SPI.h>
int brightness = 0;
int fadeAmount = 5;
int resetPin = 9;
int ssPin = 10;
byte id[4]={0,0,0,0};
MFRC522 rfid(ssPin,resetPin);

LCD5110 myGLCD(8,7,6,5,4);
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
  pinMode(3,OUTPUT);
}

void loop() {

  
   
 LedYak(1000);
if(!rfid.PICC_IsNewCardPresent())//yeni kart gelene kadar okuma yapan metot
 return;
 if(!rfid.PICC_ReadCardSerial())//kart oklutulmama durumunda çalışır
    return;
      myGLCD.clrScr();
      ekranaYaz();
      rfid.PICC_HaltA();
     delay(5000);
      //delay()
}
void ekranaYaz(){
  String numara;
  Serial.print("Id Numarasi: ");
  
  for(int i=0;i<4;i++){
    Serial.print(rfid.uid.uidByte[i]);
    numara +=rfid.uid.uidByte[i];
    
    myGLCD.clrScr();
    Serial.print(" ");  
  }
  myGLCD.print(numara,CENTER,16);
 
  Serial.println(" ");
  Serial.print(numara);  
}
void LedYak(int deger){
    analogWrite(3, 50);
    delay(deger);
    analogWrite(3, 0);
    delay(deger);
  }
