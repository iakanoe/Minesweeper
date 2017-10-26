#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <TouchScreen.h>
#include <Adafruit_TFTLCD.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <pin_magic.h>
#include <registers.h>

const int w = 40;
#define height 320
#define width 480
#define cols int(floor(width / w))
#define rows int(floor(height / w))
#define totalBees 10
bool inGame = true;

#define rgb2color(r,g,b) ((map(r,0,255,0,31)<<11)|(map(g,0,255,0,63)<<5)|(map(b,0,255,0,31)))

void drawMode(){
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
}

Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);
TouchScreen ts = TouchScreen(9, A2, A3, 8, 300);
