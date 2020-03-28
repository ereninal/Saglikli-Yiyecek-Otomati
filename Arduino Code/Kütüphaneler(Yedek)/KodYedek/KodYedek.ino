#include <MFRC522.h> // for the RFID
#include <SPI.h> // for the RFID and SD card module
#include <SD.h> 
// define pins for RFID
#define CS_RFID 10
#define RST_RFID 9
// define select pin for SD card module
#define CS_SD 4 

// Create a file to store the data
File myFile;

// Instance of the class for RFID
MFRC522 rfid(CS_RFID, RST_RFID); 

// Variable to hold the tag's UID
String uidString;


void setup() {
  
  pinMode(CS_RFID,OUTPUT);
  pinMode(CS_SD,OUTPUT);
  // Init Serial port
  Serial.begin(9600);
  while(!Serial); // for Leonardo/Micro/Zero
  
  // Init SPI bus
  SPI.begin(); 
  rfid.PCD_Init(); 

  // Setup for the SD card
  Serial.print("Initializing SD card...");
  delay(2000);
  
  
  /*if(!SD.begin(CS_SD)) {
    Serial.println("SD Card Modül okunmadı!");
    return;
  }*/
  Serial.println("initialization done.");
}

void loop() {

  
  //look for new cards
  if(rfid.PICC_IsNewCardPresent()) {
    readRFID();
  }
  delay(10);
}

void readRFID() {
  Serial.println("okunuyor");
  digitalWrite(CS_RFID,LOW);
  digitalWrite(CS_SD,HIGH);
  rfid.PICC_ReadCardSerial();
  Serial.print("Tag UID: ");

  uidString = String(rfid.uid.uidByte[0]) + " " + String(rfid.uid.uidByte[1]) + " " + 
    String(rfid.uid.uidByte[2]) + " " + String(rfid.uid.uidByte[3]);
  Serial.println(uidString);


  
  delay(200);
}
