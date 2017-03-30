#include "FastLED.h"

#define COLOR_ORDER       GRB
#define MAX_BRIGHTNESS    255
#define NUM_LEDS          150

CRGB leds[NUM_LEDS];

#define DATA_PIN          8 //White wire from the http://www.andymark.com/product-p/am-2917.htm power connector


void setup()
{

   
   FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
   FastLED.clear();
   FastLED.show();
   delay(250);
   //clear() turns all LEDs off
   FastLED.clear();
   FastLED.setBrightness(MAX_BRIGHTNESS);
   fill_solid( leds, NUM_LEDS /*number of leds*/, CRGB( 125, 125, 125) );
   FastLED.show();
   // start serial port at 9600 bps:
   Serial.begin(9600);
}

void loop()
{
   
   	FastLED.clear();
   	FastLED.show();
   	color_chase(CRGB::Green, 100);
}

//These are the functions we have defined to do chase patterns. They are actually called inside the loop() above
//They are meant to demonstrate things such as setting LED colors, controlling brightness
void color_chase(uint32_t color, uint8_t wait)
{
   FastLED.clear();
   //The brightness ranges from 0-255
   //Sets brightness for all LEDS at once
   FastLED.setBrightness(MAX_BRIGHTNESS);
   // Move a block of LEDs
   
   for(int i = 0; i < 10; i++)
   {
      for(int l = 0; l < NUM_LEDS; l++)
      {
          if((l+i)/5 % 2 == 0){leds[l] = CRGB::Green;}
          else {leds[l] = CRGB::Black;}
      }
      FastLED.show();
      delay(wait);
   }
}

//Move an "empty" dot down the strip
void missing_dot_chase(uint32_t color, uint8_t wait)
{
   //Step thru some brightness levels from max to 10. led_brightness/=2 is a cryptic shorthand way of saying led_brightness = led_brightness/2
   //	for (int led_brightness = MAX_BRIGHTNESS; led_brightness > 10; led_brightness/=2)
   {
      //FastLED.setBrightness(led_brightness);
      //CSK 4/22/2016 Turn brightness down to save batteries since almost all leds are on
      FastLED.setBrightness(25);

      // Start by turning all pixels on:
      //for(int led_number = 0; led_number < NUM_LEDS; led_number++) leds[led_number] = color;
      //https://github.com/FastLED/FastLED/wiki/Controlling-leds
      fill_solid(leds, NUM_LEDS, color);

      // Then display one pixel at a time:
      for(int led_number = 0; led_number < NUM_LEDS - 5; led_number++)
      {
         leds[led_number] = CRGB::Black; // Set new pixel 'off'
         //CSK 4/22/2016
         leds[led_number + 1] = CRGB::Black; // Set new pixel 'off'
         leds[led_number + 2] = CRGB::Black; // Set new pixel 'off'
         leds[led_number + 3] = CRGB::Black; // Set new pixel 'off'
         leds[led_number + 4] = CRGB::Black; // Set new pixel 'off'
         leds[led_number + 5] = CRGB::Black; // Set new pixel 'off'
         if( led_number > 0 && led_number < NUM_LEDS)
         {
            leds[led_number-1] = color; // Set previous pixel 'on'
         }
         FastLED.show();
         delay(wait);
      }
   }
   return;
}

//Cylon - LED sweeps back and forth, with the color, delay and number of cycles of your choice
void cylon(CRGB color, uint16_t wait, uint8_t number_of_cycles)
{
   FastLED.setBrightness(MAX_BRIGHTNESS);
   for (uint8_t times = 0; times<=number_of_cycles; times++)
   {
      // Make it look like one LED is moving in one direction
      for(int led_number = 0; led_number < NUM_LEDS; led_number++)
      {
         //Apply the color that was passed into the function
         leds[led_number] = color;
         //Actually turn on the LED we just set
         FastLED.show();
         // Turn it back off
         leds[led_number] = CRGB::Black;
         // Pause before "going" to next LED
         delay(wait);
      }

      // Now "move" the LED the other direction
      for(int led_number = NUM_LEDS-1; led_number >= 0; led_number--)
      {
         //Apply the color that was passed into the function
         leds[led_number] = color;
         //Actually turn on the LED we just set
         FastLED.show();
         // Turn it back off
         leds[led_number] = CRGB::Black;
         // Pause before "going" to next LED
         delay(wait);
      }
   }
   return;
}

void rainbow(uint8_t wait)
{

   uint16_t hue;
   FastLED.clear();

   for(hue=10; hue<255*3; hue++)
   {

      fill_rainbow( &(leds[0]), NUM_LEDS /*led count*/, hue /*starting hue*/);
      FastLED.show();
      delay(wait);
   }
   return;
}

