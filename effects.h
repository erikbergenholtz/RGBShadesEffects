//   Graphical effects to run on the RGB Shades LED array
//   Each function should have the following components:
//    * Must be declared void with no parameters or will break function pointer array
//    * Check effectInit, if false then init any required settings and set effectInit true
//    * Set effectDelay (the time in milliseconds until the next run of this effect)
//    * All animation should be controlled with counters and effectDelay, no delay() or loops
//    * Pixel data should be written using leds[XY(x,y)] to map coordinates to the RGB Shades layout

// Defines
#define BRIGHTER 0  // For the heart and scrollingHeart effects
#define DIMMER 1    // For the heart and scrollingHeart effects
#define INCREASE 0  // For the equalizer effect
#define DECREASE 1  // For the equalizer effect

void clean(){
  for(int x=0 ; x<kMatrixWidth ; x++){
    for(int y=0 ; y<kMatrixHeight ; y++){
      leds[XY(x,y)] = CRGB(0,0,0);
    }
  }
}

// RGB Heart
// Defines of DIMMER and BRIGHTER in the top of the file
int change = DIMMER;
int brightness = 5;
int lux[] = {30,60,100,150,200,255};
void heart(){
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 50;
  }
  clean();
  if(change == BRIGHTER) brightness++;
  else brightness--;
  if(brightness >= 5) change = DIMMER;
  else if(brightness <= 0) change = BRIGHTER;
  int LEDs[] ={27,25,31,32,33,34,35,55,54,53,60,65,48,47,46,38,39,40,41,42,18,16};
  int nrLEDs = 22;
  for(int i=0 ; i<nrLEDs ; i++){
    int led = LEDs[i];
    leds[led] = CHSV(0,255,lux[brightness]);
  }
}

// Equalizer
// Defines of INCREASE and DECREASE in top of file
int YOffset = kMatrixWidth;
int dir = INCREASE;
void equalizer(){
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 40;
    clean();
  }
  if(dir == INCREASE){
    for(int x=0 ; x<kMatrixWidth ; x++){
      int colors[] = {0,30,60,100,150};
      for(int y=kMatrixHeight ; y>=0  ; y--){
        int i = XY(x,y);
        if(
               i==2  || i==11 || i==27 || i==26
            || i==25 || i==16 || i==17 || i==18
            || i==31 || i==32 || i==33 || i==34
            || i==35 || i==42 || i==41 || i==40
            || i==39 || i==38 || y>=3)
        if(y==YOffset) leds[i] = CHSV(colors[y],255,255);
      }
    }
    YOffset--;
  }
  else if(dir == DECREASE){
    for(int x=kMatrixWidth-1 ; x>=0 ; x--){
      for(int y=0 ; y<kMatrixHeight-1  ; y++){
            if(y==YOffset) leds[XY(x,y)] = CRGB(0,0,0);
      }
    }
    YOffset++;
  }
  if(YOffset == kMatrixHeight) dir = INCREASE;
  else if(YOffset == -1) dir = DECREASE;
}

// EqualizerSide
#define INCREASE 0
#define DECREASE 1
#define MID 8
int XOffset = 0;
int dir2 = INCREASE;
void equalizerSide(){
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 40;
  }
  int colors[] = {0,30,60,80,100,120,150,180,180,150,120,100,80,60,30,0};
  if(dir2 == INCREASE){
    for(int x=0 ; x<8 ; x++){
      for(int y=kMatrixHeight ; y>=0  ; y--){
        if(x==XOffset)
          leds[XY(x,y)] = CHSV(colors[x],255,255);
      }
    }
    for(int x=kMatrixWidth ; x>7 ; x--){
      for(int y=kMatrixHeight ; y>=0  ; y--){
          if(x==kMatrixWidth-1-XOffset)
            leds[XY(x,y)] = CHSV(colors[x],255,255);
      }
    }
    XOffset++;
  }
  else if(dir2 == DECREASE){
    for(int x=7 ; x>=0 ; x--){
      for(int y=kMatrixHeight ; y>=0  ; y--){
        if(x==XOffset)
          leds[XY(x,y)] = CRGB(0,0,0);
      }
    }
    for(int x=8 ; x<=kMatrixWidth ; x++){
      for(int y=kMatrixHeight ; y>=0  ; y--){
        if(x==kMatrixWidth-1-XOffset)
          leds[XY(x,y)] = CRGB(0,0,0);
      }
    }
    XOffset--;
  }
  if(XOffset == MID) dir2 = DECREASE;
  else if(XOffset == -1) dir2 = INCREASE;
}

// Cyclops
int R=0;
int G=0;
int B=0;
#define RIGHT 0
#define LEFT 1
int direction;
void cyclops(){
  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    XOffset = 0;
    direction=RIGHT;
    effectDelay = 58;
    R=G=B=0;
  }
  clean();
  if(direction==RIGHT) XOffset++;
  else XOffset--;
  if(XOffset==kMatrixWidth) direction = LEFT;
  else if(XOffset==0) direction = RIGHT;
  for(int x=0 ; x<kMatrixWidth ; x++){
    R=(R+10)%255;
    G=(G+20)%255;
    B=(B+30)%255;
    for(int y=0;y<kMatrixHeight ; y++){
      if(x==XOffset)
        leds[XY(x,y)] = CRGB(R,G,B);
    }
  }
}

//Criss-cross

int cross = true;
int color = 30;
void crissCross(){
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 200;
  }
  clean();
  color = (color + 30)%255;
  if(!cross){
    for(int x=1 ; x<kMatrixWidth-1 ; x++){
      if(x<6 || x>9)
        leds[XY(x,2)] = CHSV(color,255,255);
      if(x==3 || x==12)
        for(int y=0 ; y<kMatrixHeight ; y++){
          leds[XY(x,y)] = CHSV(color,255,255);
        }
    }
    cross=true;
  }else{
    for(int x=1 ; x<kMatrixWidth-1 ; x++){
      for(int y=0 ; y<kMatrixHeight ; y++){
        if(x-1==y || x-10==y)
          leds[XY(x,y)] = CHSV(color,255,255);
      }

    }
    leds[XY(1,4)] = CHSV(color,255,255);
    leds[XY(2,3)] = CHSV(color,255,255);
    leds[XY(4,1)] = CHSV(color,255,255);
    leds[XY(5,0)] = CHSV(color,255,255);
    leds[XY(10,4)] = CHSV(color,255,255);
    leds[XY(11,3)] = CHSV(color,255,255);
    leds[XY(13,1)] = CHSV(color,255,255);
    leds[XY(14,0)] = CHSV(color,255,255);
    cross=false;
  }
}

// Matrix

int xHeight[16];
void matrix(){
  if(effectInit == false){
    effectInit = true;
    effectDelay = 100;
    for(int i=0 ; i<kMatrixWidth ; i++){
      xHeight[i] = rand()%10+4*-1;
    }
  }
  clean();
  int color = 100;
  for(int x=0 ; x<kMatrixWidth ; x++){
    for(int y=0 ; y<kMatrixWidth ; y++){
      if(y==xHeight[x])
        leds[XY(x,y)] = CHSV(color,255, 255);
      else if(y<xHeight[x]){
        int brightness = 255-((xHeight[x]-y)*50);
        if(brightness < 30)
          brightness = 0;
        leds[XY(x,y)] = CHSV(color,255,brightness);
      }
    }
    xHeight[x]++;
    if(xHeight[x] > 9)
      xHeight[x] = rand()%10+4*-1;
  }
}

// EKG
int ekgX;
void ekg(){
  if(effectInit == false){
    effectInit = true;
    effectDelay = 20;
    ekgX=0;
  }
  clean();
  int color = 100;
  for(int x=0 ; x<kMatrixWidth ; x++){
    for(int y=0 ; y<kMatrixHeight ; y++){
      if(x<=ekgX && x>=ekgX-5){
        int brightness = 255-((ekgX-x)*30);
        if(x==2 || x==11){
          if(y==3)
            leds[XY(x,y)] = CHSV(color,255,brightness);
        }else if(x==4 || x==13){
          if(y==1)
            leds[XY(x,y)] = CHSV(color,255,brightness);
        }else{
          if(y==2){
            if(brightness<50) brightness=0;
            leds[XY(x,y)] = CHSV(color,255,brightness);
          }
        }
      }
    }
  }
  ekgX++;
  if(ekgX == 100)
    ekgX = 0;
}

// Scrolling square
int offsetX;
int offsetY;
void scrollingSquare(){
  if(effectInit == false){
    effectInit = true;
    effectDelay = 500;
    offsetX = 0;
    offsetY = 0;
  }
  clean();
  for(int x=offsetX ; x<2+offsetX ; x++){
    for(int y=offsetY ; y<2+offsetY ; y++){
      leds[XY(x,y)] = CHSV(200,255,255);
    }
  }
  offsetX = (offsetX + 1)%16;
  offsetY = (offsetY + 1)%5;
}


// Srolling an advanced shape
void scroller(int xOff,int yOff, int * xLED, int * yLED, int arrLen,int width, int height){
  for(int i=0 ; i<arrLen ; i++){
    xLED[i] = (xLED[i]+xOff)%width;
    if(xLED[i]<0) xLED[i] = width+xLED[i];
    yLED[i] = (yLED[i]+yOff)%height;
    if(yLED[i]<0) yLED[i] = height+yLED[i];
  }
}

// Defines of DIMMER and BRIGHTER in the top of the file

/*
 * I had to change some variable names to make this work. Sorry about
 * that guys. Such is life with global variables.
 */
 
int scrollChange = DIMMER;
int scrollBrightness = 5;
int xLED[] = {2,4,1,2,3,4,5,2,3,4,3,12,11,12,13,10,11,12,13,14,11,13};
int yLED[] = {1,1,2,2,2,2,2,3,3,3,4,4, 3, 3, 3, 2, 2, 2, 2, 2, 1, 1};
void scrollingHeart(){
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 500;
  }
  int scrollLux[] = {30,60,100,150,200,255};
  int nrLEDs = 22;
  clean();
  if(scrollChange == BRIGHTER) scrollBrightness++;
  else scrollBrightness--;
  if(scrollBrightness >= 5) scrollChange = DIMMER;
  else if(scrollBrightness <= 0) scrollChange = BRIGHTER;
  for(int i=0 ; i<nrLEDs ; i++){
    int led = XY(xLED[i],yLED[i]);
    leds[led] = CHSV(0,255,scrollLux[scrollBrightness]);
  }
  scroller(1,1,xLED,yLED,nrLEDs);
}

//Class to store colors in the RGB format
class color{
  public:
    byte r=0;
    byte g=0;
    byte b=0;
    color(byte _r,byte _g,byte _b){
      this->r = _r;
      this->g = _g;
      this->b = _b;
    }
};

int xCoords[] = {0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,6,6,6,6,6,6,9,9,9,9,9,9,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,15,15,15,15,15,15};
int yCoords[] = {1,2,3,7,12,17,0,4,6,8,12,16,18,0,1,2,3,4,6,7,8,12,16,17,18,0,1,2,3,4,6,7,8,12,16,17,18,0,1,2,3,4,6,7,8,12,16,17,18,0,4,6,8,12,16,18,1,2,3,7,12,17,1,2,3,7,12,17,0,4,6,8,12,16,18,0,1,2,3,4,6,7,8,12,16,17,18,0,1,2,3,4,6,7,8,12,16,17,18,0,1,2,3,4,6,7,8,12,16,17,18,0,4,6,8,12,16,18,1,2,3,7,12,17};
void eyes(){
        if(!effectInit){
                effectInit = true;
                effectDelay = 350;
        }
        clean();
        color c[] = {color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(255, 0, 110),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(0, 19, 127),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(255, 0, 110),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(255, 0, 110),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(0, 19, 127),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(255, 0, 110),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(255, 0, 110),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127),color(0, 19, 127)};
        int nrOfLEDs = 124;
        int aniWidth = 16;
        int aniHeight = 20;
        for(int i=0 ; i<nrOfLEDs ; i++){
                leds[XY(xCoords[i],yCoords[i])] = CRGB(c[i].r,c[i].g,c[i].b);
        }
        scroller(0,-5,xCoords,yCoords,nrOfLEDs,aniWidth,aniHeight);
}