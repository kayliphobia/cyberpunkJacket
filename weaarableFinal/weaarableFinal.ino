
#include <Adafruit_CircuitPlayground.h>

// do NOT include the standard NeoPixel library

#define NEOPIX_PIN    A0
#define NUM_PIXELS    50
float X, Y, Z;
float pose1Zthreshold = 9.5;
float pose2Ythreshold = -9.5;
float pose3Zthreshold = 11;
float pose3Ythreshold = 10;
float pose4Ythreshold = 9;
float pose5Xthreshold = 9.5;
float pose6Xthreshold = -14;
float pose6Ythreshold = 2;



// use Adafruit_CPlay_NeoPixel to create a separate external NeoPixel strip
Adafruit_CPlay_NeoPixel strip = Adafruit_CPlay_NeoPixel(NUM_PIXELS, NEOPIX_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_CPlay_NeoPixel strip2 = Adafruit_CPlay_NeoPixel(55, A2, NEO_GRB + NEO_KHZ800);

void setup() {
  // initialize the Circuit Playground as usual
  CircuitPlayground.begin();
  Serial.begin(9600);
  // initialize external NeoPixel strip separately
  strip.begin();
  strip2.begin();
}

void loop() {
 // for the external NeoPixels, must use the Adafruit_CPlay_NeoPixel functions directly
  detection();
  if (Z > pose1Zthreshold) {
    chargeUp();
    }
  else if(Y < pose2Ythreshold){
    readyUp();
  }
  else if(Y > pose4Ythreshold){
    rest();
  }
  else if(X > pose5Xthreshold){
    healUp();
  }
  else{
    strip.clear();
    strip.show();
    strip2.clear();
    strip2.show();
  }
  
}

void readyUp(){

  for(int x=0; x<54; x++){
      strip.clear();
      strip.setPixelColor(x, 0, x*4, 20);
      strip.setPixelColor(x+1, 0, x*4, 20);
      strip.setPixelColor(x+2, 0, x*4, 20);
      strip2.clear();
      strip2.setPixelColor(x, 0, x*4, 20);
      strip2.setPixelColor(x+1, 0, x*4, 20);
      strip2.setPixelColor(x+2, 0, x*4, 20);
      X = CircuitPlayground.motionX();
      Y = CircuitPlayground.motionY();
      Z = CircuitPlayground.motionZ();
      Serial.print(X);
      Serial.print(",");
      Serial.print(Y);
      Serial.print(",");
      Serial.println(Z);
      if (Z>pose3Zthreshold){
        punch();
        break;
      }
      else if (X < pose6Xthreshold && Y<pose6Ythreshold){
        electric();
        break;
      }
      strip.show();
      strip2.show();
      delay(10);
  }
}

void chargeUp(){
  for(int x=0; x<54; x++){
    strip.setPixelColor(x, 0, x*4, 20);
    strip2.setPixelColor(x, 0, x*4, 20);
    strip.show();
    strip2.show();
    delay(50);
  }
}

void punch(){
  for(int x=0; x<54; x++){
    strip.setPixelColor(x, 255, x*2, 0);
    strip.show();
    strip2.setPixelColor(x, 255, x*2, 0);
    strip2.show();
    delay(7);
  }
  delay(100);
  for(int x=54; x>=0; x--){
      strip.setPixelColor(x, 0, 0, 0);
      strip.show();
      strip2.setPixelColor(x, 0, 0, 0);
      strip2.show();
      delay(7);
  }
  delay(1000);
}

void rest(){
  for (int x=0; x<5;x++){
    strip.setPixelColor(random(NUM_PIXELS),random(0,100),random(0,100), random(0,100));
    strip.show();
    strip2.setPixelColor(random(NUM_PIXELS),random(0,100),random(0,100), random(0,100));
    strip2.show();
    delay(100);
  }
}

void electric(){
  strip.clear();
  strip2.clear();
  for(int x=54; x>0; x--){
      strip.setPixelColor(x, 4*x, 255, 250/x);
      strip.show();
      strip2.setPixelColor(x, 4*x, 255, 250/x);
      strip2.show();
      delay(30);
  }
  for (int y = 5;y>0;y--){
    for(int x=0; x<54; x++){
      strip.setPixelColor(x, 0, 40*y, 255);
      strip2.setPixelColor(x, 0, 40*y, 255);
    }
    strip.show();
    strip2.show();
    delay(random(10,150));
    strip.clear();
    strip.show();
    strip2.clear();
    strip2.show();
    delay(random(10,100));
  }
  delay(1000);
}

void healUp(){
  for (int y = 10;y>0;y--){
      for(int x=0; x<60; x++){
      strip.setPixelColor(x, 100/y, 0, 50/y);
      strip2.setPixelColor(x, 100/y, 0, 50/y);
    }
    strip.show();
    strip2.show();
    delay(40);
  }
    for (int y = 10;y>1;y--){
      for(int x=0; x<54; x++){
      strip.setPixelColor(x, 10*y, 0, 5*y);
      strip2.setPixelColor(x, 10*y, 0, 5*y);
    }
    strip.show();
    strip2.show();
    delay(40);
  }
  strip.clear();
  strip.show();
  strip2.clear();
  strip2.show();
}

void detection(){
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
  Serial.print(X);
  Serial.print(",");
  Serial.print(Y);
  Serial.print(",");
  Serial.println(Z);
  delay(50);  
}