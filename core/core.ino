#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip0
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip0)
Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(10, 2, NEO_GRB + NEO_KHZ800);
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
  
const uint32_t red = strip0.Color(255, 0,0);
const uint32_t turq = strip0.Color(0,255,255);
const uint32_t pink = strip0.Color(255, 51, 153);
const uint32_t blue = strip0.Color(0, 0, 255);
const uint32_t orange = strip0.Color(255, 128, 0);
const uint32_t green = strip0.Color(0, 255,0);
const uint32_t white = strip0.Color(255, 255, 255);
const uint32_t yellow = strip0.Color(255, 255, 0);
const uint32_t purple = strip0.Color(153, 0, 153);

//max length of snake
snakeType snake [30];
int snakeLength = 2;
uint32_t gblColour = turq;
uint32_t foodColour = red;
int randX;
int randY;

int score=0;

//higher is easier
int difficulty = 300;

//set the default starting direction
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
  
  snake[0].xCo = 2;
  snake[0].yCo = 0;
  snake[1].xCo = 1;
  snake[1].yCo = 0;
  setBox(snake[0].xCo,snake[0].yCo, gblColour);
  randomSeed(analogRead(0));

  //UART setup
  Serial.begin(9600);
  Serial.setTimeout(20);
  genFood();
}

void loop() {  
  while (Serial.available() > 0) {
      incoming = Serial.readString();
      Serial.println(incoming);
      }
  //delay between snake moving
  delay(difficulty);
  clearAll();
  
  //snake[0] is the snake head
  
  if (incoming.startsWith("dir_up")) {
       Serial.println("Go up");
       if (snake[0].yCo < 9){
           snake[0].yCo++;
         }
       else {
           snake[0].yCo = 0;
         }
     }
   if (incoming.startsWith("dir_down")) {
         Serial.println("Go down");
         if (snake[0].yCo >0){
             snake[0].yCo--;
           }
         else {
             snake[0].yCo = 9;
           }
       }
  if (incoming.startsWith("dir_right")) {
         Serial.println("Go right");
         if (snake[0].xCo < 9){
             snake[0].xCo++;
           }
         else {
             snake[0].xCo = 0;
           }
       }
   if (incoming.startsWith("dir_left")) {
     Serial.println("Go left");
     if (snake[0].xCo > 0){
         snake[0].xCo--;
       }
     else {
         snake[0].xCo = 9;
       }
   }
   
   //colour changers
   if (incoming.endsWith("clr_blue")) {
     Serial.println("Change to blue");
     gblColour = blue;
   }
   if (incoming.endsWith("clr_green")) {
     Serial.println("Change to green");
     gblColour = green;
   }
   if (incoming.endsWith("clr_red")) {
     Serial.println("Change to red");
     gblColour = red;
   }
   if (incoming.endsWith("clr_turq")) {
     Serial.println("Change to turq");
     gblColour = turq;
   }
   if (incoming.endsWith("clr_pink")) {
     Serial.println("Change to pink");
     gblColour = pink;
   }
   if (incoming.endsWith("clr_orange")) {
     Serial.println("Change to orange");
     gblColour = orange;
   }
   if (incoming.endsWith("clr_white")) {
     Serial.println("Change to white");
     gblColour = white;
   }
   if (incoming.endsWith("clr_yellow")) {
     Serial.println("Change to yellow");
     gblColour = yellow;
   }
   if (incoming.endsWith("clr_purple")) {
     Serial.println("Change to purple");
     gblColour = purple;
   }
   
   
   checkImpact();
   setBox(snake[0].xCo,snake[0].yCo, gblColour);
   setBox(randX,randY,foodColour);
   snakeShift();
   
   if ((snake[0].xCo == randX) && (snake[0].yCo == randY)){
     //snake has eaten food
     score=score+1;
     snakeLength++;
     genFood();
   }
  }
  
void checkImpact(){
  for (int i=1;i<snakeLength;i++){
      if ((snake[0].xCo == snake[i].xCo) && (snake[0].yCo == snake[i].yCo)){
        Serial.println("You deeaadd");
        died();
    };
  }
}
  
void died(){
  delay(2000);
  score=0;
  snakeLength=2;
  snake[0].xCo = 2;
  snake[0].yCo = 0;
  snake[1].xCo = 1;
  snake[1].yCo = 0;
}  
  

void clearAll(){
  for (int i=0;i<10;i++){
    for (int j=0;j<10;j++){
      setBox(i,j,0);
    };
  };
}

void snakeShift(){
  for (int i=snakeLength; i>0; i--){
    snake[i] = snake[i-1];
    setBox(snake[i].xCo,snake[i].yCo, gblColour);
  };
}

void genFood(){
  randX = random(10);
  randY = random(10);
 }


void setBox(int strip, int pixel, uint32_t colour) {
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

