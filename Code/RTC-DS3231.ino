#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include "RTClib.h"
#include <stdio.h>

//namespace {
  
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat"};
uint8_t menu_button = 9;

RTC_DS3231 rtc;

DateTime now;

int menu = 0; // menu selector. 0 = display time, 1 = alarm menu

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//String dayToString(Time::Day day){
//  switch(day){
//    case 1: return "Sun";
//    case 2: return "Monday";
//    case 3: return "Tuesday";
//    case 4: return "Wednesday";
//    case 5: return "Thursday";
//    case 6: return "Friday";
//    case 7: return "Sat";
//  }
//  return "uknown";
//
//  
//}
void print_time(){

//  Time t = rtc.time();
//  Serial.print(t.yr);Serial.print(" ");
//  Serial.print(t.mon);Serial.print(" ");
//  Serial.print(t.date);Serial.print(" ");
//  Serial.print(t.hr);Serial.print(" ");
//  Serial.print(t.min);Serial.print(" ");
//  Serial.print(t.sec);Serial.print(" ");
//  Serial.println();

//  String day = dayToString(t.day);
//  char buf[50];
//  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d \n %02d:%02d:%02d",
//             day.c_str(),
//             t.yr, t.mon, t.date,
//             t.hr, t.min, t.sec);
//  Serial.println(buf);
  lcd.setCursor(0,0);
  lcd.print(now.year(), DEC);
  lcd.print("-");
  lcd.print(now.month(), DEC);
  lcd.print("-");
  lcd.print(now.day(), DEC);
  lcd.print(" ");
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.setCursor(0,1);
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  lcd.print(now.minute(), DEC);
  lcd.print(":");
  lcd.print(now.second(), DEC);
  lcd.print("   ");

  }
//}

void print_alarm(){
  lcd.setCursor(0,0);
  lcd.print("ALARM MENU");
}

bool menu_button_press(){
  if (digitalRead(menu_button) == HIGH){
    return false;
  }
  else{
    delay(300); //wait for user to relasee button
    return true;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  rtc.writeProtect(false);
//  rtc.halt(false);
  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
//  
//  Time t (2017, 4, 14, 22, 1, 23, Time::kFriday);
//  Time t=rtc.time();
//  rtc.time(t);

    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode(menu_button, INPUT);
  
 
}



void loop() {
  now = rtc.now();
  if (menu_button_press()){
    

    switch(menu){
       case 0:
          lcd.clear();
          menu = 1;
          break;
       
       case 1:
          lcd.clear();
          menu = 0;
          break;

       default:
          lcd.clear();
          menu = 1;       
    }
    
  }
  
  switch(menu){
    
    case 0:
      print_time();
      delay(200);
      break;
      
    case 1:
      print_alarm();
      delay(200);
      break;

    default:
      print_time();
      delay(200);  
  }
  

}
