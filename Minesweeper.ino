#include <Adafruit_TFTLCD.h>
#include <pin_magic.h>
#include <registers.h>
// https://github.com/CodingTrain/Rainbow-Code/blob/c1c82f2a8b5f79a5f0bdae247aba87e595ccd470/CodingChallenges/CC_71_minesweeper
#define height 320
#define width 240
const int w = 20;
#define cols int(floor(width / w))
#define rows int(floor(height / w))
#define totalBees 1

Adafruit_TFTLCD tft;

class Cell{
  public:
    Cell(int ix, int jx, int wx);
    void show(void);
    void countBees(void);
    bool contains(int xx, int yx);
    void reveal(void);
    void floodFill(void);
    bool bee = false;
  private:
    int i;
    int j;
    int w;
    int x;
    int y;
    int neighborCount = 0;
    bool revealed = false;
};

Cell * grid[int(cols)][int(rows)];

Cell::Cell(int ix, int jx, int wx){
  i = ix;
  j = jx;
  x = (ix * wx);
  y = (jx * wx);
  w = wx;
}

#define rgb2color(r,g,b) (map(b,0,255,0,31)|map(g,0,255,32,2016)|map(r,0,255,2017,65535))

void Cell::show(void){
  tft.drawRect(x, y, w, w, 0);
  if(revealed){
    if(bee){
      tft.fillCircle(x + w * 0.5, y + w * 0.5, w * 0.5, rgb2color(127,127,127));
    } else {
      tft.fillRect(x, y, w, w, rgb2color(200, 200, 200));
      if(neighborCount > 0){
        tft.drawChar(x + w * 0.5, y + w - 6, neighborCount + '0', 0, 1, 1);
      }
    }
  }
}

void Cell::countBees(void){
  if(bee){
    neighborCount = -1;
    return;
  }
  int total = 0;
  for(int xoff = -1; xoff <= 1; xoff++){
    for(int yoff = -1; yoff <= 1; yoff++){
      int ix = i + xoff;
      int jx = j + yoff;
      if (ix > -1 && ix < cols && jx > -1 && jx < rows) {
        Cell neighbor = *(grid[ix][jx]);
        if(neighbor.bee) total++;
      }
    }
  }
  neighborCount = total; 
}

bool Cell::contains(int xx, int yx){
  return (xx > x && xx < x + w && yx > y && yx < y + w);
}

void Cell::reveal(void){
  revealed = true;
  if(neighborCount == 0) floodFill();
}

void Cell::floodFill(void){
  for (int xoff = -1; xoff <= 1; xoff++) {
    for (int yoff = -1; yoff <= 1; yoff++) {
      int ix = i + xoff;
      int jx = j + yoff;
      if (ix > -1 && ix < cols && jx > -1 && jx < rows) {
        Cell neighbor = *(grid[ix][jx]);
        if (!neighbor.bee && !neighbor.revealed) {
          neighbor.reveal();
        }
      }
    }
  }
}

void setup(){
  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(1);
  tft.fillScreen(0);
  for(int i = 0; i < cols; i++) for(int j = 0; j < rows; j++) grid[i][j] = new Cell(i, j, w);
  int options[int(cols*rows)][2];
  for(int i = 0; i < cols; i++) for(int j = 0; j < rows; j++){
    options[i*cols+j][0] = i;
    options[i*cols+j][1] = j;
    options[i*cols+j][2] = 1;
  }
  for(int n = 0; n < totalBees; n++){
    int rr = 0;
    while(!rr){
      int index = floor(random(cols*rows));
      int i = options[index][0];
      int j = options[index][1];
      rr = options[index][2];
      options[index][2] = 0;
    }
  }
  for(int i = 0; i < cols; i++) for(int j = 0; j < rows; j++) grid[i][j]->countBees();
}

void loop{}

/*function gameOver() {
  for (var i = 0; i < cols; i++) {
    for (var j = 0; j < rows; j++) {
      grid[i][j].revealed = true;
    }
  }
}

function mousePressed() {
  for (var i = 0; i < cols; i++) {
    for (var j = 0; j < rows; j++) {
      if (grid[i][j].contains(mouseX, mouseY)) {
        grid[i][j].reveal();

        if (grid[i][j].bee) {
          gameOver();
        }

      }
    }
  }
}

function draw() {
  background(255);
  for (var i = 0; i < cols; i++) {
    for (var j = 0; j < rows; j++) {
      grid[i][j].show();
    }
  }
}*/
