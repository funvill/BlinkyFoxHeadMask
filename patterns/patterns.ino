#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN D4

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(245, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
int pattern ; 

void setup() {
  int brightness = 32 ; 

  // I don't have a switch but I can restart the system easily. 
  // If i want it bright, i restart it until it shows brightly 
  int r = random(5) ; 
  if( r == 2 ) {
    brightness = 255 ; 
  }
  strip.setBrightness(brightness);

  pattern = random(0,3);


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  switch( pattern) 
  {
    case 0: 
      for( int count = 20 ; count > 0 ; count-- ) {
        theaterChase(strip.Color(127, 127, 127), 50); // White
      }
    break ; 

    case 1: 
      // Set everything black. 
      for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
    
      for( int count = 500 ; count > 0 ; count-- ) {
        randomFlashSticky() ;
      }   
    break ; 

    case 2: 
      for( int speed = 5 ; speed > 0 ; speed-- ) {
        rainbowCycle(speed);
      }    
    break ; 
    
    default: {
      pattern = 0 ; 
      return; 
      break; 
    }
  }
  
  pattern++; 



/*
  // Flash whilte 
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
  }
  strip.show();
  delay(50); 
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
  delay(50); 
*/
  // smile(); 


  
  // theaterChaseRainbow(50);
}
/*
void smile() {
    // Set everything black. 
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.setPixelColor(98, strip.Color(255, 0, 0));
  strip.setPixelColor(99, strip.Color(255, 0, 0));
  strip.setPixelColor(100, strip.Color(255, 0, 0));
  strip.setPixelColor(101, strip.Color(255, 0, 0));
  strip.setPixelColor(102, strip.Color(255, 0, 0));
  strip.setPixelColor(103, strip.Color(255, 0, 0));

  strip.setPixelColor(153, strip.Color(255, 0, 0));
  strip.setPixelColor(154, strip.Color(255, 0, 0));
  strip.setPixelColor(155, strip.Color(255, 0, 0));
  strip.setPixelColor(156, strip.Color(255, 0, 0));
  strip.setPixelColor(157, strip.Color(255, 0, 0));
  strip.setPixelColor(158, strip.Color(255, 0, 0));

  strip.setPixelColor(105, strip.Color(0, 0, 255));
  strip.setPixelColor(106, strip.Color(0, 0, 255));
  strip.setPixelColor(143, strip.Color(0, 0, 255));
  strip.setPixelColor(144, strip.Color(0, 0, 255));
  strip.show();
  delay(50); 
}
*/

void randomFlashSticky() {
  for( int count = 0 ; count < 10 ; count++ ) { 
    int offset = random( 5, strip.numPixels() - 3 ) ; 
  
    // uint32_t c = strip.Color(random(255), random(255), random(255)) ; 
    uint32_t c = strip.Color(random(127, 255), 0, 0) ; 
    strip.setPixelColor(offset-3, strip.Color(0, 0, 0));
    strip.setPixelColor(offset-2, strip.Color(0, 0, 0));
    strip.setPixelColor(offset-1, c);
    strip.setPixelColor(offset, c);
    strip.setPixelColor(offset+1, c);
    strip.setPixelColor(offset+2, strip.Color(0, 0, 0));
    strip.setPixelColor(offset+3, strip.Color(0, 0, 0));
  }
  strip.show();
  delay(50); 
  
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*1; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
