#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define starts 7
#define stops 6
#define resetB 5
#define clicker 9
int st;
int sp;
int rsb;
int cl;

int counter = 0;
bool startState = false;
int ticker = 0;

void setup() {
    counter = 0;
  startState = false;
  pinMode(starts, INPUT_PULLUP);
  pinMode(stops, INPUT_PULLUP);
  pinMode(resetB, INPUT_PULLUP);
  pinMode(clicker, INPUT);
  display.begin();
  display.clearDisplay();
}
void loop() {

  cl = digitalRead(clicker);
  sp = digitalRead(stops);
  st = digitalRead(starts);
  rsb = digitalRead(resetB);

  if((cl == LOW) && (startState == true) && (ticker == 1))
		{
      counter += 50;
      ticker = 0;
      
  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);
  display.print("ardRODOMETER");
  display.setTextSize(3);
  display.setCursor(4,0);
  display.print(counter/100, "m");
  display.display();
  
		};

  if(cl == HIGH)
  {
    ticker = 1;
  };
  if(rsb == 0)
  {
    counter = 0;
  };

  if(st == LOW)
  {
    startState = true;
  };

  if (sp == LOW)
  {
    startState = false;
    display.setCursor(7,4);
    display.print("Paused");
    display.display();
  };

 
}
