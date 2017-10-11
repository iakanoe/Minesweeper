void setup(){
  Serial.begin(9600);
  tft.reset();
  tft.begin(0x9481);
  tft.fillScreen(rgb2color(255,255,255));
  int options[int(cols*rows)][2];
  Serial.print(0);
  for(int i = 0; i < cols; i++) for(int j = 0; j < rows; j++) grid[i][j] = new Cell(i, j, w);
  Serial.print(0);
  for(int n = 0; n < totalBees; n++){
    bool rr = false;
    while(!rr){
      int i = floor(random(cols));
      int j = floor(random(rows));
      if(!grid[i][j]->bee){
        grid[i][j]->bee = true;
        rr = true;
      }
    }
  }
  Serial.print(0);
  for(int i = 0; i < cols; i++) for(int j = 0; j < rows; j++){
    grid[i][j]->countBees();
  }
  Serial.print(0);
}

void loop() {
  TSPoint p = ts.getPoint();
  if(p.z > 10 && p.z < 1000) mousePressed(p.x, p.y);
  for(int i = 0; i < cols; i++) for(int j = 0; j < rows; j++){
    grid[i][j]->show();
  }
}
