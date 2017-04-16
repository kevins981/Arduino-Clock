#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include "RTClib.h"
#include <stdio.h>

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat"};
uint8_t menu_button = 9;
uint8_t increase_button = 8;
uint8_t next_button=7;
uint8_t buzzer_pin=6;
int cSec,cMin,cHour;
RTC_DS3231 rtc;

DateTime now;

int menu = 0; // menu selector. 0 = display time, 1 = alarm menu

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void print_time(){
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

void print_alarm(){
  lcd.setCursor(0,0);
  lcd.print("ALARM MENU");
  lcd.setCursor(0,1);
  

  int currentPos=0;
  lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ALARM MENU");
      lcd.setCursor(0,1);
      lcd.print(cHour);
      lcd.print(":");
      lcd.print(cMin);
      lcd.print(":");
      lcd.print(cSec);
  while(true){
    if(button_press(increase_button)){
      switch(currentPos){
        case 0:
          cSec=(cSec+1)%60;
          break;
        case 1:
          cMin=(cMin+1)%60;
          break;
        case 2:
          cHour=(cHour+1)%24;
          break;
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ALARM MENU");
      lcd.setCursor(0,1);
      lcd.print(cHour);
      lcd.print(":");
      lcd.print(cMin);
      lcd.print(":");
      lcd.print(cSec);
      delay(300);
    }
    if(button_press(next_button)){
      currentPos=(currentPos+1)%3;
      delay(300);
    }
    if(button_press(menu_button)){
      menu=0;
      delay(300);
      return;
      
    }
    
    
  }
}
bool button_press(uint8_t currentButton){
  if(digitalRead(currentButton) == HIGH)
    return false;
  delay(300);
  return true;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  cSec=0;
  cMin=10;
  cHour=22;
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
  pinMode(increase_button, INPUT);
  pinMode(next_button, INPUT);
  pinMode(buzzer_pin, OUTPUT);
}



void loop() {
  now = rtc.now();
  noTone(buzzer_pin);
  if(now.hour()==cHour&&now.minute()==cMin){
    tone(buzzer_pin,3830);
    delay(300);
  }
  if (button_press(menu_button)){
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

