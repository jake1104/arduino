#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#define LEDPIN  6   //연결된 핀 번호
#define NUMPIXEL  2 //연결된 LED 개수
#define BT_TX 2
#define BT_RX 3

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXEL, LEDPIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial bt(BT_TX, BT_RX);
byte datalist[4];

void setup() {
  bt.begin(9600);
  Serial.begin(9600);
  pixels.begin();
  delay(1000);
  pixels.setPixelColor(0, 255, 255, 255);
  pixels.setPixelColor(1, 255, 255, 255);
  pixels.show();
}

void loop() {
  if(bt.available() > 0) {
    bt.readBytes(datalist, 4);
    for(byte i=0; i<4; i++) {
      Serial.println(datalist[i]);
    }
    for(byte i=0; i<NUMPIXEL; i++) {
      pixels.setPixelColor(i, datalist[0], datalist[1], datalist[2]);
    }
    pixels.setBrightness(datalist[3]);
    pixels.show();
    delay(100);
  }
}
