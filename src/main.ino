// FastLed
#include "FastLED.h"

#define DATA_PIN    2
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    50 // Number of leds you are using
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          96
unsigned long lastLEDUpdate = 0;

void setup() 
{

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

//Credit to Tweaking4ALL for original blinky eye code: http://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#halloween_eyes

void loop() {
  // Fixed:
  // HalloweenEyes(0xff, 0x00, 0x00, 1,4, true, 10, 80, 3000);
  // or Random:
  HalloweenEyes(0xff, 0xdf, 0x0d, //Primary Color 1 That Fades
                0xff, 0x00, 0x00, //Primary Color 2 that Does Not fade
                1, random(2,4), 
                true, random(5,50), random(50,150), 
                random(500, 3000));
  HalloweenEyes(0xb7, 0x00, 0xFe, //Secondary Color 1 That Fades
                0xff, 0x00, 0x00, //Secondary Color 2 That Does Not Fade
                1, random(1,4), 
                true, random(15,75), random(100,250), 
                random(500, 3000));
  unsigned long now = millis();
  if ( now - lastLEDUpdate > 10000 ) {
    setAll(0,0,0); // Set all black every 10 seconds
  lastLEDUpdate = now;
  }
  
}

void HalloweenEyes(byte red, byte green, byte blue,
                   byte red2, byte green2, byte blue2,  
                   int EyeWidth, int EyeSpace, 
                   boolean Fade, int Steps, int FadeDelay,
                   int EndPause){
  randomSeed(analogRead(0));
  
  int i;
  int StartPoint  = random( 0, NUM_LEDS - (2*EyeWidth) - EyeSpace );
  int Start2ndEye = StartPoint + EyeWidth + EyeSpace;
  int StartPoint2  = random( 0, NUM_LEDS - (2*EyeWidth) - EyeSpace );
  int Start2ndEye2 = StartPoint2 + EyeWidth + EyeSpace;
  
  for(i = 0; i < EyeWidth; i++) {
    setPixel(StartPoint + i, red, green, blue);
    setPixel(Start2ndEye + i, red, green, blue);
    setPixel(StartPoint2 + i, red2, green2, blue2);
    setPixel(Start2ndEye2 + i, red2, green2, blue2);
  }
  
  showStrip();
  
  if(Fade==true) {
    float r, g, b;
  
    for(int j = Steps; j >= 0; j--) {
      r = j*(red/Steps);
      g = j*(green/Steps);
      b = j*(blue/Steps);
      
      for(i = 0; i < EyeWidth; i++) {
        setPixel(StartPoint + i, r, g, b);
        setPixel(Start2ndEye + i, r, g, b);
      }
      
      showStrip();
      delay(FadeDelay);
    }
  }
  
  //setAll(0,0,0); // Set all black
  
  delay(EndPause);
}


void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}
