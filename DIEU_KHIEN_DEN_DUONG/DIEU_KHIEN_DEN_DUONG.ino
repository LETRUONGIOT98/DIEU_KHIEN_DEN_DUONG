#define BLYNK_TEMPLATE_ID "TMPLfVJHowCg"
#define BLYNK_DEVICE_NAME "DU AN 1"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
int ldr = A0;
int dosang = 0, dieukhien = 0, nutnhan = D3, bt = 0, dss = 0, chedo = 0;
int led = D5;
int trangthai;
void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(ldr, INPUT);
  pinMode(nutnhan, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  BlynkEdgent.begin();
  chedo = 1;
  bt = 1;
}
BLYNK_WRITE(V2) {
  dss = param.asInt();
}
BLYNK_WRITE(V1) {
  chedo = param.asInt();
}
BLYNK_WRITE(V0) {
  bt = param.asInt();
}
void loop() {
  BlynkEdgent.run();
  int dsldr = map(analogRead(ldr), 0, 675, 255, 0);
  int ds =  map(dsldr, 0, 255, 0, 100);
  int dslsen =  map(analogRead(ldr), 0, 675, 0, 100);
  int dst =  map(dss, 0, 255, 0, 100);
  Blynk.virtualWrite(V4, dslsen);
  Serial.println(digitalRead(nutnhan));
  if (digitalRead(nutnhan) == 0 && bt == 0) {

    Serial.println("DANG BAT");
    bt = 1;
    Blynk.virtualWrite(V0, 1);
    delay(500);

  }
  if (digitalRead(nutnhan) == 0 && bt == 1) {
    Serial.println("DANG TAT");
    bt = 0;
    Blynk.virtualWrite(V0, 0);
    delay(500);
  }


  if (bt == 1) {
    Serial.println("BAT THIET BI");

    if (chedo == 0) { //Thủ công
      analogWrite(led, dss);
      Blynk.virtualWrite(V3, dst);
    }
    if (chedo == 1) { //Tự động
      analogWrite(led, dsldr);
      Blynk.virtualWrite(V3, ds);

    }
  }
  if ( bt == 0) {
    Serial.println("TAT THIET BI");
    digitalWrite(led, 0);
    Blynk.virtualWrite(V3, 0);

  }
}
