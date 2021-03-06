void setup(){
  randomSeed(analogRead(A8) + analogRead(A9) + analogRead(A10) + analogRead(A11) + analogRead(A12) + analogRead(A13));
  Serial.begin(9600);
  Serial.print("Iniciando");
  drawMode();
  tft.reset();
  uint16_t identifier = 0x9481;
  tft.begin(identifier);
  tft.setRotation(1);
  tft.fillScreen(rgb2color(255,255,255));
  int options[int(cols*rows)][2];
  Serial.print('.');
  for(int i = 0; i < cols; i++) for(int j = 0; j < rows; j++) grid[i][j] = new Cell(i, j, w);
  Serial.print('.');
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
  Serial.print('.');
  for(int i = 0; i < cols; i++) for(int j = 0; j < rows; j++) grid[i][j]->countBees();
  for(int i = 0; i < cols; i++) for(int j = 0; j < rows; j++) grid[i][j]->show();
  Serial.print("\nIniciado, a jugar!\n");
}

void loop() {
  TSPoint p = ts.getPoint();
  int x = map(p.x, 65, 900, 0, 480);
  int y = map(p.y, 140, 950, 0, 320);
  if(p.z > 10 && p.z < 1000) mousePressed(x, y);
  static int i = 0, j = 0;
  grid[i][j]->show();
  if(j < rows){
    j++;
  } else if(i < cols){
    i++;
    j = 0;
  } else {
    i = 0;
    j = 0;
  }
}
