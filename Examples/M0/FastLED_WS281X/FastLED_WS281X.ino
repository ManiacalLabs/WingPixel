#include<FastLED.h>

#define NUM_LEDS 12

// WingPixel uses the SPI MOSI pin for data output
// so must be this pin!
#define DATA_PIN 23

#define LEDTYPE WS2812

//Typical color order for this LED type
// If wrong, set back to RGB and the observer order on strip.
// That order will be the correct order to place here.
// i.e. if COLOR_ORDER set to RGB and output is B,G,G,R,R,R, set to BGR
#define COLOR_ORDER GRB

//decrease for testing over USB power
#define BRIGHTNESS 64 // 25%

CRGBArray<NUM_LEDS> leds;
CRGBArray<4> color_pattern;

void setup() {
  color_pattern[0] = CRGB(255,0,0);
  color_pattern[1] = CRGB(0,255,0);
  color_pattern[2] = CRGB(0,0,255);
  color_pattern[3] = CRGB(255,255,255);

  FastLED.addLeds<LEDTYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

uint8_t c = 0;
void loop(){
  //Red, Green, Green, Blue, Blue, Blue
  leds[0] = CRGB(255,0,0);
  leds[1] = CRGB(0,255,0);
  leds[2] = CRGB(0,255,0);
  leds[3] = CRGB(0,0,255);
  leds[4] = CRGB(0,0,255);
  leds[5] = CRGB(0,0,255);

  // Blank Separtor
  leds[6] = CRGB(0,0,0);

  // Cycle through Red, Green, Blue, White
  leds[7] = color_pattern[c];
  leds[8] = color_pattern[c];
  leds[9] = color_pattern[c];

  c++;
  if(c>=4){ c=0; }

  FastLED.show();
  delay(1000);
}

