#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip0
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip0)
Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(10, 2, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(10, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(10, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(10, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(10, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(10, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(10, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip7 = Adafruit_NeoPixel(10, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip8 = Adafruit_NeoPixel(10, 10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip9 = Adafruit_NeoPixel(10, 11, NEO_GRB + NEO_KHZ800);

//Added comment to test GitHub

struct snakeType
{
    int xCo;
    int yCo;
};
  
snakeType snake [30];
const int magenta = strip0.Color(255, 0, 255);
const int black = strip9.Color(0,0,0);
const int other = strip0.Color(0,255,0);
int difficulty = 400;
String incoming = "dir_right";

void setup() {
  
  //Strip setup
  strip0.begin();
  strip1.begin();
  strip2.begin();
  strip3.begin();
  strip4.begin();
  strip5.begin();
  strip6.begin();
  strip7.begin();
  strip8.begin();
  strip9.begin();
  
  snake[0].xCo = 8;
  snake[0].yCo = 0;
  setBox(snake[0].xCo,snake[0].yCo, magenta);

  //UART setup
  Serial.begin(9600);
  Serial.setTimeout(20);
  
  strip0.show(); // Initialize all pixels to 'off'
  //strip1.show();
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  
  while (Serial.available() > 0) {
    incoming = Serial.readString();
    Serial.println(incoming);
    }
    //delay between snake moving
    delay(difficulty);
clearAll();
  if (incoming == "dir_up") {
       Serial.println("Go up");
       if (snake[0].yCo < 9){
         snake[0].yCo++;
       }
       else {
         snake[0].yCo = 0;
       }
       setBox(snake[0].xCo,snake[0].yCo, magenta);
     }
    if (incoming == "dir_down") {
       Serial.println("Go down");
       if (snake[0].yCo >0){
         snake[0].yCo--;
       }
       else {
         snake[0].yCo = 9;
       }
       setBox(snake[0].xCo,snake[0].yCo, magenta);
     }
    
    
  if (incoming == "dir_right") {
       Serial.println("Go right");
       if (snake[0].xCo < 9){
         snake[0].xCo++;
       }
       else {
         snake[0].xCo = 0;
       }
       setBox(snake[0].xCo,snake[0].yCo, magenta);
     }
     
   if (incoming == "dir_left") {
   Serial.println("Go left");
   if (snake[0].xCo > 0){
     snake[0].xCo--;
   }
   else {
     snake[0].xCo = 9;
   }
   setBox(snake[0].xCo,snake[0].yCo, magenta);
 }
  }

void clearAll(){

  for (int i=0;i<10;i++){
    for (int j=0;j<10;j++){
      setBox(i,j,0);
    };
  };
}

void setBox(int strip, int pixel, int colour) {
  switch (strip)
  {
    case 0:
      strip0.setPixelColor(pixel, colour);
      strip0.show();
      break;
    case 1:
      strip1.setPixelColor(pixel,colour);
      strip1.show();
      break;
    case 2:
      strip2.setPixelColor(pixel,colour);
      strip2.show();
      break;
    case 3:
      strip3.setPixelColor(pixel,colour);
      strip3.show();
      break;
    case 4:
      strip4.setPixelColor(pixel,colour);
      strip4.show();
      break;
    case 5:
      strip5.setPixelColor(pixel,colour);
      strip5.show();
      break;
    case 6:
      strip6.setPixelColor(pixel,colour);
      strip6.show();
      break;
    case 7:
      strip7.setPixelColor(pixel,colour);
      strip7.show();
      break;
    case 8:
      strip8.setPixelColor(pixel,colour);
      strip8.show();
      break;
    case 9:
      strip9.setPixelColor(pixel,colour);
      strip9.show();
      break;
    
  }
  
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip0.numPixels(); i++) {
      strip0.setPixelColor(i, c);
      strip0.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip0.numPixels(); i++) {
      strip0.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip0.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip0.numPixels(); i++) {
      strip0.setPixelColor(i, Wheel(((i * 256 / strip0.numPixels()) + j) & 255));
    }
    strip0.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip0.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip0.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip0.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}



