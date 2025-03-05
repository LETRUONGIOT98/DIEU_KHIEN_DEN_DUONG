
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPL7iEBMIZs"
#define BLYNK_DEVICE_NAME "DIEU KHIEN DEN HAM GIU XE"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#include <Arduino.h>
#include <analogWrite.h>
#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
int button = GPIO_NUM_5;     //Nút nhấn reset D5
// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7

#include "BlynkEdgent.h"
int ldrKV1 = GPIO_NUM_34; //D34
int ldrKV2 = GPIO_NUM_35;  //D35
int denKV1 = GPIO_NUM_32;  //D32
int denKV2 = GPIO_NUM_33;  // D33
int sen =  GPIO_NUM_23;
int dosangkv1 = 0, tbkv1 = 0, dskv1 = 0, chedo = 0, dosangkv2 = 0, tbkv2 = 0, dskv2 = 0;
int dckv1 = 0, dckv2 = 0, ddskv1 =0,ddskv2 =0;
const int freq = 10000;
const int resolution = 8;
void setup()
{
  Serial.begin(115200);
  ledcSetup(0, freq, resolution);
  delay(100);
  pinMode(button, INPUT_PULLUP);
  BlynkEdgent.begin();
  pinMode(ldrKV1, INPUT);
  pinMode(ldrKV2, INPUT);
  pinMode(sen, INPUT);
  pinMode(denKV1, OUTPUT);
  pinMode(denKV2, OUTPUT);
  BlynkEdgent.run();
  delay(200);
  chedo = 1;
  tbkv1 = 1;
  tbkv2 = 1;
  Blynk.virtualWrite(V4,1);
  Blynk.virtualWrite(V0,1);
  Blynk.virtualWrite(V5,1);
  ledcAttachPin(denKV1,1);
  ledcAttachPin(denKV2,2);
}

BLYNK_WRITE(V0) {
  tbkv1 = param.asInt();
}

BLYNK_WRITE(V3) {
  dckv1 = param.asInt();
}
BLYNK_WRITE(V4) {
  chedo = param.asInt();
}
BLYNK_WRITE(V5) {
  tbkv2 = param.asInt();
}

BLYNK_WRITE(V8) {
  dckv2 = param.asInt();
}
void loop() {
  BlynkEdgent.run();
  dosangkv1 = map(analogRead(ldrKV1), 0,3000, 100, 0);
  ddskv1 = map(dosangkv1, 0, 100, 255, 0);
  dskv1 = map(ddskv1, 0, 255, 0, 100);
  Blynk.virtualWrite(V1, dosangkv1);
  while(digitalRead(sen)==0){
  analogWrite(denKV1, 255);  
  ledcWrite(2, 8000);
  Blynk.virtualWrite(V2, 100);
  Blynk.virtualWrite(V7 , 100);
  delay(3000);
  }
  //KV2
  dosangkv2 = map(analogRead(ldrKV2), 0, 3000, 100, 0);
  ddskv2 = map(dosangkv2, 0, 100, 8000, 0);
  dskv2 = map(ddskv2, 0, 8000, 0, 100);
  Blynk.virtualWrite(V6, dosangkv2);
  Serial.println(analogRead(ldrKV1));
  if (chedo == 1) {
    if (tbkv1 == 1) {
      analogWrite(denKV1, ddskv1);
      Blynk.virtualWrite(V2, dskv1);
    }
    if (tbkv2 == 1) {
      ledcWrite(2, ddskv2);
      Blynk.virtualWrite(V7, dskv2);
    }
  }

  if (chedo == 0 ) {
    if (tbkv1 == 1) {
      analogWrite(denKV1, dckv1);
      int ds1 = map(dckv1, 0, 255, 0, 100);
      Blynk.virtualWrite(V2, ds1);
    }
    if (tbkv2 == 1) {
      ledcWrite(2, dckv2);
      int ds2 = map(dckv2, 0, 8000, 0, 100);
      Blynk.virtualWrite(V7, ds2);
    }
  }

  if (tbkv1 == 0) {
    analogWrite(denKV1, 0);
    Blynk.virtualWrite(V2, 0);
  }
  if (tbkv2 == 0) {
    ledcWrite(2, 0);
    Blynk.virtualWrite(V7, 0);
  }
}
