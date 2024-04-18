#define BLYNK_TEMPLATE_ID "TMPLkjEVVox_"
#define BLYNK_DEVICE_NAME "diemdom"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG
#define USE_NODE_MCU_BOARD

#include "BlynkEdgent.h"

#define led1 14 //D5
#define led2 12 //D6
#define led3 13 //D7
#define led4 15 //D8 
#define button1 5 //D1
#define button2 4 //D2
#define button3 0 //D3
#define button4 2 //D4
unsigned long times=millis();
unsigned long timesDelay=millis();
WidgetLED led_connect(V0);
boolean updateState1=0;
boolean updateState2=0;
boolean updateState3=0;
boolean updateState4=0;

void setup()
{
  Serial.begin(115200);
  delay(100);
  BlynkEdgent.begin();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(button3,INPUT_PULLUP);
  pinMode(button4,INPUT_PULLUP);
  attachInterrupt(button1,handleInterrup1,FALLING);
  attachInterrupt(button2,handleInterrup2,FALLING);
  attachInterrupt(button3,handleInterrup3,FALLING);
  attachInterrupt(button4,handleInterrup4,FALLING);
  Serial.println("---------------------Int--------------------");
}

void loop() {
  BlynkEdgent.run();

  if(millis()-times>1000){
    Blynk.virtualWrite(V5, millis()/1000);
    if (led_connect.getValue()){
      led_connect.off();
    }else {
      led_connect.on();
    }
    times=millis();
  }
  if(updateState1==1){
    Blynk.virtualWrite(V1,digitalRead(led1));
    updateState1=0;
  }
  if(updateState2==1){
    Blynk.virtualWrite(V2,digitalRead(led2));
    updateState2=0;
  }
  if(updateState3==1){
    Blynk.virtualWrite(V3,digitalRead(led3));
    updateState3=0;
  }
  if(updateState4==1){
    Blynk.virtualWrite(V4,digitalRead(led4));
    updateState4=0;
  }
}
BLYNK_CONNECTED() {
  // Request Blynk server to re-send latest values for all pins
  Blynk.syncAll();
}
BLYNK_WRITE(V1){
  int p = param.asInt();
  digitalWrite(led1, p); 
}
BLYNK_WRITE(V2){
  int p = param.asInt();
  digitalWrite(led2, p); 
}
BLYNK_WRITE(V3){
  int p = param.asInt();
  digitalWrite(led3, p); 
}
BLYNK_WRITE(V4){
  int p = param.asInt();
  digitalWrite(led4, p); 
}
ICACHE_RAM_ATTR void handleInterrup1(){
  if(millis()-timesDelay>200){
    digitalWrite(led1,!digitalRead(led1));
    updateState1=1;
    timesDelay=millis();
  }
}
ICACHE_RAM_ATTR void handleInterrup2(){
  if(millis()-timesDelay>200){
    digitalWrite(led2,!digitalRead(led2));
    updateState2=1;
    timesDelay=millis();
  }
}
ICACHE_RAM_ATTR void handleInterrup3(){
  if(millis()-timesDelay>200){
    digitalWrite(led3,!digitalRead(led3));
    updateState3=1;
    timesDelay=millis();
  }
}
ICACHE_RAM_ATTR void handleInterrup4(){
  if(millis()-timesDelay>200){
    digitalWrite(led4,!digitalRead(led4));
    updateState4=1;
    timesDelay=millis();
  }
}
