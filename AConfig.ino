#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <TouchScreen.h>
#include <Adafruit_TFTLCD.h>
#include <pin_magic.h>
#include <registers.h>
// https://github.com/CodingTrain/Rainbow-Code/blob/c1c82f2a8b5f79a5f0bdae247aba87e595ccd470/CodingChallenges/CC_71_minesweeper

const int w = 40;
#define height 320
#define width 240
#define cols int(floor(width / w))
#define rows int(floor(height / w))
#define totalBees 10

#define rgb2color(r,g,b) (map(b,0,255,0,31)|map(g,0,255,32,2016)|map(r,0,255,2017,65535))

Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);
TouchScreen ts(9, A2, A3, 8, 300);
