#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUM_LEDS 10

// WingPixel uses the SPI MISO pin for data output
// so must be this pin!
#define DATA_PIN 11
// WingPixel uses the SPI CLK pin for clock output
// so must be this pin!
#define CLOCK_PIN 13

//Typical color order for this LED type
// If wrong, set back to RGB and the observer order on strip.
// That order will be the correct order to place here.
// i.e. if COLOR_ORDER set to RGB and output is B,G,G,R,R,R, set to BGR
#define COLOR_ORDER DOTSTAR_BGR

//decrease for testing over USB power
#define BRIGHTNESS 64 // 25%

//Setup strip object with above defines
Adafruit_DotStar strip = Adafruit_DotStar(
  NUM_LEDS, DATA_PIN, CLOCK_PIN, COLOR_ORDER);

uint32_t color_pattern[4] = {
  0xFF0000,
  0x00FF00,
  0x0000FF,
  0xFFFFFF
};

void setup() {
  strip.begin(); // Initialize pins for output
  strip.setBrightness(BRIGHTNESS);
  strip.show();  // Turn all LEDs off ASAP
}

uint8_t c = 0;
void loop(){
  //Red, Green, Green, Blue, Blue, Blue
  strip.setPixelColor(0, 0xFF0000);
  strip.setPixelColor(1, 0x00FF00);
  strip.setPixelColor(2, 0x00FF00);
  strip.setPixelColor(3, 0x0000FF);
  strip.setPixelColor(4, 0x0000FF);
  strip.setPixelColor(5, 0x0000FF);

  // Blank Separtor
  strip.setPixelColor(6, 0x000000);

  // Cycle through Red, Green, Blue, White
  strip.setPixelColor(7, color_pattern[c]);
  strip.setPixelColor(8, color_pattern[c]);
  strip.setPixelColor(9, color_pattern[c]);

  c++;
  if(c>=4){ c=0; }

  strip.show();
  delay(1000);
}

