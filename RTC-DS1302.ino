#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <DS1302.h>
#include <stdio.h>

namespace {
uint8_t CLK = 7;
uint8_t DAT = 6;
uint8_t RST = 8;
DS1302 rtc(RST, DAT, CLK);


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String dayToString(Time::Day day){
  switch(day){
    case 1: return "Sun";
    case 2: return "Monday";
    case 3: return "Tuesday";
    case 4: return "Wednesday";
    case 5: return "Thursday";
    case 6: return "Friday";
    case 7: return "Sat";
  }
  return "uknown";

  
}
void print_time(){

  Time t = rtc.time();
//  Serial.print(t.yr);Serial.print(" ");
//  Serial.print(t.mon);Serial.print(" ");
//  Serial.print(t.date);Serial.print(" ");
//  Serial.print(t.hr);Serial.print(" ");
//  Serial.print(t.min);Serial.print(" ");
//  Serial.print(t.sec);Serial.print(" ");
//  Serial.println();

  String day = dayToString(t.day);
  char buf[50];
    snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d \n %02d:%02d:%02d",
             day.c_str(),
             t.yr, t.mon, t.date,
             t.hr, t.min, t.sec);
  Serial.println(buf);
  lcd.setCursor(0,0);
  lcd.print(day.c_str());
  lcd.print(" ");
  lcd.print(t.yr);
  lcd.print("-");
  lcd.print(t.mon);
  lcd.print("-");
  lcd.print(t.date);
  lcd.setCursor(0,1);
  lcd.print(t.hr);
  lcd.print(":");
  lcd.print(t.min);
  lcd.print(":");
  lcd.print(t.sec);
  lcd.print("   ");
}}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rtc.writeProtect(false);
  rtc.halt(false);

  //Time t (2017, 4, 2, 21, 0, 23, Time::kSunday);
  Time t=rtc.time();
  rtc.time(t);

    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");

 
}

void loop() {
  // put your main code here, to run repeatedly:
  print_time();
  delay(2000);
}
