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
int dosang = 0, dieukhien = 0, nutnhan = D3, bt = 0, bt2 =0, ds2 = 0, chedo = 0;
int led = D5;
int led2 = D6;
int led3 = D7;
int led4 = D8;
int nutnhan2 = D4;
int trangthai;
void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(ldr, INPUT);
  pinMode(nutnhan, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  BlynkEdgent.begin();
  chedo = 1;
  bt = 1;
}
BLYNK_WRITE(V3) {
  ds2 = param.asInt();
}
BLYNK_WRITE(V0) {
  bt = param.asInt();
}
BLYNK_WRITE(V5) {
  bt2 = param.asInt();
}
void loop() {
  BlynkEdgent.run();
  int dsldr = map(analogRead(ldr), 0, 675, 255, 0);
  int ds =  map(dsldr, 0, 255, 0, 100);
  Blynk.virtualWrite(V4, ds);
  //thiết bị 1
  analogWrite(led, ds2);
  //thiết bị 2
  analogWrite(led2, dsldr);
  Serial.println(digitalRead(nutnhan));
  
  //thiết bị 3
  if (digitalRead(nutnhan2) == 0 && bt2 == 0) {

    Serial.println("DANG BAT");
    bt2 = 1;
    Blynk.virtualWrite(V5, 1);
    delay(500);

  }
  if (digitalRead(nutnhan2) == 0 && bt2 == 1) {
    Serial.println("DANG TAT");
    bt2 = 0;
    Blynk.virtualWrite(V5, 0);
    delay(500);
  }
  if ( bt2 == 0) {
    Serial.println("TAT THIET BI");
    digitalWrite(led3, 0);
    Blynk.virtualWrite(V5, 0);

  }
  if ( bt2 == 1) {
    Serial.println("BAT THIET BI");
    digitalWrite(led3, 1);
    Blynk.virtualWrite(V3, 0);

  }
  //Thiết bị 4
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
  if ( bt == 0) {
    Serial.println("TAT THIET BI");
    digitalWrite(led4, 0);
    Blynk.virtualWrite(V0, 0);

  }
  if ( bt == 1) {
    Serial.println("BAT THIET BI");
    digitalWrite(led4, 1);
    Blynk.virtualWrite(V0, 0);

  }
}
