#include <SimpleDHT.h>
#include <LiquidCrystal.h>
#define DHTPIN 7
#define DHTTYPE DHT11
#define LCD_resolution 6
SimpleDHT11 dht11(DHTPIN);
LiquidCrystal lcd (13, 12, 5, 4, 3, 2); byte heart [8] = {
  B00000,
  B01010,
  B10101,
  B10001,
  B10001,
  B01010,
  B00100,
  B00000
};
byte syot[8] = {
  B00000,
  B00100,
  B00100,
  B01010,
  B10001,
  B00000,
  B00000,
  B00000
};
byte ah[8]{
  B10000,
  B10000,
  B11100,
  B10000,
  B10000,
  B10000,
  B00000
};

void setup() {
  lcd.begin(16,2);
  analogWrite(LCD_resolution, 100);
  lcd.clear();
  lcd.createChar(0, heart);
  lcd.createChar(1, syot);
  lcd.createChar(2, ah);
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  lcd.setCursor(4,0);
  lcd.write(byte(1));
  lcd.write(byte(2));
}

void loop() {
  
}
