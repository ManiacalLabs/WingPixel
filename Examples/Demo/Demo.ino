#define FASTLED_FORCE_SOFTWARE_SPI
#include<FastLED.h>

#define NUM_LEDS 12

#define DATA_PIN 16
// 18 for Feather ESP32
// 13 for Feather Huzzah ESP8266
// 16 for Feather 32u4

#define CLOCK_PIN 15
// 5 for Feather ESP32
// 14 for Feather Huzzah ESP8266
// 15 for Feather 32u4

CRGBArray<NUM_LEDS> leds;

//void setup() { FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS); }
void setup() {
  FastLED.addLeds<APA102,DATA_PIN,CLOCK_PIN,BRG,DATA_RATE_MHZ(10)>(leds, NUM_LEDS);
  FastLED.setBrightness(32);
}
// void setup() { FastLED.addLeds<LPD8806,DATA_PIN,CLOCK_PIN>(leds, NUM_LEDS); }

void loop(){
  static uint8_t hue;
  for(int i = 0; i < NUM_LEDS; i++) {
    // fade everything out
    leds.fadeToBlackBy(40);

    // let's set an led value
    leds[i] = CHSV(hue++,255,255);

    // now, let's first 20 leds to the top 20 leds,
    //leds(NUM_LEDS/2,NUM_LEDS-1) = leds(NUM_LEDS/2 - 1 ,0);
    FastLED.delay(33);
  }
}

