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
  tft.drawRect(x, y, w, w, 0);
  Serial.print("Cell\t"); Serial.print(i); Serial.print(':'); Serial.println(j);
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

void gameOver() {
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      grid[i][j]->revealed = true;
    }
  }
}

void mousePressed(int xxx, int yyy) {
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      if (grid[i][j]->contains(xxx, yyy)) {
        grid[i][j]->reveal();

        if (grid[i][j]->bee) {
          gameOver();
        }
      }
    }
  }
}
