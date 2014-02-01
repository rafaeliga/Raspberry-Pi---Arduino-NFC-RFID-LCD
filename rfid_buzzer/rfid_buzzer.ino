#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>
#include <Wire.h>

/**
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS: Pin 10
* RST: Pin 9
*
* Script is based on the script of Miguel Balboa. 
* New cardnumber is printed when card has changed. Only a dot is printed
* if card is the same.
*
* @version 0.1
* @author Henri de Jong
* @since 06-01-2013
*/

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
//    gordo = 942321812526
//    guizao = 2069496193
//    rafa = 211191118134156
//    julio = 243210116134211

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
              Serial.println(current_id);
              lcd.print("Card ID:");
              lcd.setCursor(0,1);
              lcd.print(current_id);
              while (skip_while) {
                if ( Serial.available() ) {
                  if (Serial.read()) {
                    lcd.clear();
//                    switch (Serial.read()) {
//                      case 1:
//                        lcd.print("Usuario 1 logado!");
//                      case 2:
//                        lcd.print("Usuario 2 logado!");
//                      case 3:
//                        lcd.print("Usuario 3 logado!");
//                      case 4:
//                        lcd.print("Usuario 4 logado!");
//                      default:
//                        lcd.print("Nenhum usuario");
//                    }
                    skip_while = 0;
                  } else {
                    lcd.print("Nothing");
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



