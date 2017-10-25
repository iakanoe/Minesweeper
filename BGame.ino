class Cell{
  public:
    Cell(int ix, int jx, int wx);
    void show(void);
    void countBees(void);
    bool contains(int xx, int yx);
    void reveal(void);
    void floodFill(void);
    bool bee = false;
    bool revealed = false;
  private:
    int i;
    int j;
    int w;
    int x;
    int y;
    int neighborCount = 0;
};

Cell * grid[int(cols)][int(rows)];

Cell::Cell(int ix, int jx, int wx){
  i = ix;
  j = jx;
  x = (ix * wx);
  y = (jx * wx);
  w = wx;
}

void Cell::show(void){
  drawMode();
  //Serial.print("Cell\t"); Serial.print(i); Serial.print(':'); Serial.println(j);
  if(revealed){
    tft.fillRect(x, y, w, w, rgb2color(127, 127, 127));
    if(bee) tft.fillCircle(x + w * 0.5, y + w * 0.5, w * 0.5 - 5, rgb2color(0,255,0));
    else {
      if(neighborCount > 0){
        tft.setTextColor(rgb2color(255,0,0));
        tft.setTextSize(5);
        tft.setCursor(x - 1 + w / 4, y + 1);
        tft.println(neighborCount);
        //tft.drawChar(x + w * 0.5, y + w - 6, '0' + char(neighborCount), 0, 1, 1);
      }
    }
  }
  tft.drawRect(x, y, w, w, 0);
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
  show();
  if(neighborCount == 0 && inGame) floodFill();
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

void gameOver() {
  inGame = false;
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      grid[i][j]->revealed = true;
    }
  }
}

void mousePressed(int xxx, int yyy) {
  Serial.print("Click! "); Serial.print(xxx); Serial.print(','); Serial.println(yyy);
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      if (grid[i][j]->contains(xxx, yyy)) {
         Serial.print("\tContained in cell "); Serial.print(i); Serial.print(','); Serial.println(j);
        if (grid[i][j]->bee){
          gameOver();
          return;
        }
        grid[i][j]->reveal();
        return;
      }
    }
  }
}
