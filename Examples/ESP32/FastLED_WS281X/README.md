Sadly, WS281X chipsets (NeoPixel, WS2811, WS2812, WS2812B) are not working on the Feather Huzzah32 currently.

See this FastLED issue for more: https://github.com/FastLED/FastLED/issues/491

We highly recommend using APA102 (DotStar) LEDs instead! They are much better!

But, if you have to use WS281X LEDs with the ESP32, check out the [Adafruit NeoPixel ESP32 Example](../Adafruit_NeoPixel/)