// LCD Libraries
#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>
#include <Wire.h>

// NFC RFID Libraries
#include <SPI.h>
#include <RFID.h>

#include <Time.h>

#define SS_PIN 10
#define RST_PIN 9
#define I2C_ADDR	 0x3F
#define En_pin		 2
#define Rw_pin		 1
#define Rs_pin		 0
#define D4_pin		 4
#define D5_pin		 5
#define D6_pin		 6
#define D7_pin		 7
#define BACKLIGHT_PIN    3

LiquidCrystal_I2C lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

RFID rfid(SS_PIN, RST_PIN); 

// Setup variables:
int serNum0;
int serNum1;
int serNum2;
int serNum3;
int serNum4;

char* concat(int int1, int int2, int int3, int int4, int int5) {
    char str1[20];
    char str2[5];
    char str3[5];
    char str4[5];
    char str5[5];
    
    sprintf(str1,"%d%d%d%d%d", int1, int2, int3, int4, int5);
    
    return str1;
}

void setup() { 
  Serial.begin(9600);
  
  SPI.begin(); 
  rfid.init();
  lcd.begin (20, 4);
  lcd.clear();
 
  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  
  lcd.clear();
  lcd.home();
  lcd.print("NFCReader ready");
}

void loop() {
    char* current_id;
    int skip_while = 1;
    String name = "";

    if (rfid.isCard()) {
      if (rfid.readCardSerial()) {
          if (rfid.serNum[0] != serNum0 && rfid.serNum[1] != serNum1 && rfid.serNum[2] != serNum2 && rfid.serNum[3] != serNum3 && rfid.serNum[4] != serNum4 ) {
              lcd.clear();
              serNum0 = rfid.serNum[0];
              serNum1 = rfid.serNum[1];
              serNum2 = rfid.serNum[2];
              serNum3 = rfid.serNum[3];
              serNum4 = rfid.serNum[4];
              current_id = concat(serNum0, serNum1, serNum2, serNum3, serNum4);
              
              current_id = "12345";
              
              Serial.println(current_id);
              
              lcd.print("Card ID:");
              delay(1000);
              
              lcd.setCursor(0,1);
              lcd.print(current_id);
              
              while (skip_while) {
                while ( Serial.available() > 0 ) {
                  char received = Serial.read();
                  name += received; 
                  
                  // Process message when new line character is recieved
                  if (received == '\n') {
                    name.replace("\n", "");
                    name = "Bem vindo " + name + "!";
                    
                    lcd.clear();
                    lcd.print(name);
                    
                    skip_while = 0;
                  }
                }
              }
           } else {
             lcd.setCursor(0,3);
             lcd.print(".");
           } 
        }
    }
    rfid.halt();

}



