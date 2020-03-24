
#include <DS1302RTC.h>
#include <Streaming.h>        //http://arduiniana.org/libraries/streaming/
//#include <Time.h>             //http://playground.arduino.cc/Code/Time

#include <TimeLib.h>
DS1302RTC RTC(5, 6, 7);
//            rst,data,clk
//DS1302RTC RTC(9, 10, 11);
// Optional connection for RTC module
//#define DS1302_GND_PIN 33
//#define DS1302_VCC_PIN 35

void setup(void)
{
  Serial.begin(115200);

  // Activate RTC module
  //  digitalWrite(DS1302_GND_PIN, LOW);
  //  pinMode(DS1302_GND_PIN, OUTPUT);
  //
  //  digitalWrite(DS1302_VCC_PIN, HIGH);
  //  pinMode(DS1302_VCC_PIN, OUTPUT);

  Serial << F("RTC module activated");
  Serial << endl;
  delay(500);

  if (RTC.haltRTC()) {
    Serial << F("The DS1302 is stopped.  Please set time");
    Serial << F("to initialize the time and begin running.");
    Serial << endl;
  }
  if (!RTC.writeEN()) {
    Serial << F("The DS1302 is write protected. This normal.");
    Serial << endl;
  }

  delay(5000);

  //setSyncProvider() causes the Time library to synchronize with the
  //external RTC by calling RTC.get() every five minutes by default.
  setSyncProvider(RTC.get);

  Serial << F("RTC Sync");
  if (timeStatus() == timeSet)
    Serial << F(" Ok!");
  else
    Serial << F(" FAIL!");
  Serial << endl;
}

void loop(void)
{
  static time_t tLast;
  time_t t;
  tmElements_t tm;

  //check for input to set the RTC, minimum length is 12, i.e. yy,m,d,h,m,s 17,01,12,11,33,00
  if (Serial.available() >= 12) {
    //note that the tmElements_t Year member is an offset from 1970,
    //but the RTC wants the last two digits of the calendar year.
    //use the convenience macros from Time.h to do the conversions.
    int y = Serial.parseInt();
    if (y >= 100 && y < 1000)
      Serial << F("Error: Year must be two digits or four digits!") << endl;
    else {
      if (y >= 1000)
        tm.Year = CalendarYrToTm(y);
      else    //(y < 100)
        tm.Year = y2kYearToTm(y);
      tm.Month = Serial.parseInt();
      tm.Day = Serial.parseInt();
      tm.Hour = Serial.parseInt();
      tm.Minute = Serial.parseInt();
      tm.Second = Serial.parseInt();
      t = makeTime(tm);
      //use the time_t value to ensure correct weekday is set
      if (RTC.set(t) == 0) { // Success
        setTime(t);
        Serial << F("RTC set to: ");
        printDateTime(t);
        Serial << endl;
      }
      else
        Serial << F("RTC set failed!") << endl;
      //dump any extraneous input
      while (Serial.available() > 0) Serial.read();
    }
  }

  t = now();
  if (t != tLast) {
    tLast = t;
    printDateTime(t);
    Serial << endl;
  }
}

//print date and time to Serial
void printDateTime(time_t t)
{
  printDate(t);
  Serial << ' ';
  printTime(t);
}

//print time to Serial
void printTime(time_t t)
{
  printI00(hour(t), ':');
  printI00(minute(t), ':');
  printI00(second(t), ' ');
}

//print date to Serial
void printDate(time_t t)
{
  printI00(day(t), 0);
  Serial << monthShortStr(month(t)) << _DEC(year(t));
}

//Print an integer in "00" format (with leading zero),
//followed by a delimiter character to Serial.
//Input value assumed to be between 0 and 99.
void printI00(int val, char delim)
{
  if (val < 10) Serial << '0';
  Serial << _DEC(val);
  if (delim > 0) Serial << delim;
  return;
}
