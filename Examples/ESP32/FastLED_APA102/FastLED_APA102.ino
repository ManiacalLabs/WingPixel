#include<FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define NUM_LEDS 12

// WingPixel uses the SPI MOSI pin for data output
// so must be this pin!
#define DATA_PIN 18
// WingPixel uses the SPI CLK pin for clock output
// so must be this pin!
#define CLOCK_PIN 5

#define LEDTYPE APA102

//Typical color order for this LED type
// If wrong, set back to RGB and the observer order on strip.
// That order will be the correct order to place here.
// i.e. if COLOR_ORDER set to RGB and output is B,G,G,R,R,R, set to BGR
#define COLOR_ORDER BGR

//decrease for testing over USB power
#define BRIGHTNESS 64 // 25%


CRGBArray<NUM_LEDS> leds;
CRGBArray<4> color_pattern;

// -- The core to run FastLED.show()
#define FASTLED_SHOW_CORE 0

// -- Task handles for use in the notifications
static TaskHandle_t FastLEDshowTaskHandle = 0;
static TaskHandle_t userTaskHandle = 0;

/** show() for ESP32
 *  Call this function instead of FastLED.show(). It signals core 0 to issue a show,
 *  then waits for a notification that it is done.
 */
void FastLEDshowESP32()
{
    if (userTaskHandle == 0) {
        // -- Store the handle of the current task, so that the show task can
        //    notify it when it's done
        userTaskHandle = xTaskGetCurrentTaskHandle();

        // -- Trigger the show task
        xTaskNotifyGive(FastLEDshowTaskHandle);

        // -- Wait to be notified that it's done
        const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 200 );
        ulTaskNotifyTake(pdTRUE, xMaxBlockTime);
        userTaskHandle = 0;
    }
}

/** show Task
 *  This function runs on core 0 and just waits for requests to call FastLED.show()
 */
void FastLEDshowTask(void *pvParameters)
{
    // -- Run forever...
    for(;;) {
        // -- Wait for the trigger
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // -- Do the show (synchronously)
        FastLED.show();

        // -- Notify the calling task
        xTaskNotifyGive(userTaskHandle);
    }
}

void setup() {
  delay(3000); // 3 second delay for recovery
  color_pattern[0] = CRGB(255,0,0);
  color_pattern[1] = CRGB(0,255,0);
  color_pattern[2] = CRGB(0,0,255);
  color_pattern[3] = CRGB(255,255,255);

  FastLED.addLeds<LEDTYPE,DATA_PIN,CLOCK_PIN,COLOR_ORDER,DATA_RATE_MHZ(10)>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // -- Create the FastLED show task
  xTaskCreatePinnedToCore(FastLEDshowTask, "FastLEDshowTask", 2048, NULL, 2, &FastLEDshowTaskHandle, FASTLED_SHOW_CORE);
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

  FastLEDshowESP32();
  delay(1000);
}

