#include <Wire.h>

boolean DeviceFound = false;
byte error, address;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    Serial.println("\nI2C Araniyor...");
  
    for(address = 0; address <= 127; address++ )
    {
       Wire.beginTransmission(address);
       error = Wire.endTransmission();

       if (error == 0)
       {
         Serial.print("I2C cihaz bulundu. Adresi: 0x");
         if (address<16)   Serial.print("0");
         Serial.println(address,HEX);
  
         DeviceFound = true;
         break;
       }
       else if (error==4)
       {
         Serial.print("Bilinmeyen hata olustu. Adres: 0x");
         if (address<16)  Serial.print("0");
         Serial.println(address,HEX);
       }
    }
    if (DeviceFound == false)
       Serial.println("Herhangi bir bagli I2C bulunamadi\n");
    else
       Serial.println("Tamamlandi. Kolay gelsin.\n");          
}
 
void loop()
{
}
