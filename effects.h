//   Graphical effects to run on the RGB Shades LED array
//   Each function should have the following components:
//    * Must be declared void with no parameters or will break function pointer array
//    * Check effectInit, if false then init any required settings and set effectInit true
//    * Set effectDelay (the time in milliseconds until the next run of this effect)
//    * All animation should be controlled with counters and effectDelay, no delay() or loops
//    * Pixel data should be written using leds[XY(x,y)] to map coordinates to the RGB Shades layout


void clean(){
  for(int x=0 ; x<kMatrixWidth ; x++){
    for(int y=0 ; y<kMatrixHeight ; y++){
      leds[XY(x,y)] = CRGB(0,0,0);
    }
  }
}

// RGB Heart
#define BRIGHTER 0
#define DIMMER 1
int change = DIMMER;
int brightness = 5;
int lux[] = {30,60,100,150,200,255};
void heart(){
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 50;
    clean();
  }
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
#define INCREASE 0
#define DECREASE 1
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
      else
        leds[XY(x,y)] = CRGB(0,0,0);
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

// Triple Sine Waves
byte sineOffset = 0; // counter for current position of sine waves
void threeSine() {
  
  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 20;
  }

  // Draw one frame of the animation into the LED array
  for (byte x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {

      // Calculate "sine" waves with varying periods
      // sin8 is used for speed; cos8, quadwave8, or triwave8 would also work here
      byte sinDistanceR = qmul8(abs(y*(255/kMatrixHeight) - sin8(sineOffset*9+x*16)),2);
      byte sinDistanceG = qmul8(abs(y*(255/kMatrixHeight) - sin8(sineOffset*10+x*16)),2);
      byte sinDistanceB = qmul8(abs(y*(255/kMatrixHeight) - sin8(sineOffset*11+x*16)),2);

      leds[XY(x,y)] = CRGB(255-sinDistanceR, 255-sinDistanceG, 255-sinDistanceB); 
    }
  }
  
  sineOffset++; // byte will wrap from 255 to 0, matching sin8 0-255 cycle

}

// RGB Plasma
byte offset  = 0; // counter for radial color wave motion
int plasVector = 0; // counter for orbiting plasma center
void plasma() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
  }

  // Calculate current center of plasma pattern (can be offscreen)
  int xOffset = cos8(plasVector/256);
  int yOffset = sin8(plasVector/256);

  // Draw one frame of the animation into the LED array
  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y < kMatrixHeight; y++) {
      byte color = sin8(sqrt(sq(((float)x-7.5)*10+xOffset-127)+sq(((float)y-2)*10+yOffset-127))+offset);
      leds[XY(x,y)] = CHSV(color, 255, 255);
    }    
  }

  offset++; // wraps at 255 for sin8
  plasVector += 16; // using an int for slower orbit (wraps at 65536)

}


// Scanning pattern left/right, uses global hue cycle
byte riderPos = 0;
void rider() {
  
  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 5;
    riderPos = 0;
  }

  // Draw one frame of the animation into the LED array
  for (byte x = 0; x < kMatrixWidth; x++) {
    int brightness = abs(x*(256/kMatrixWidth) - triwave8(riderPos)*2 + 127)*3;
    if (brightness > 255) brightness = 255;
    brightness = 255 - brightness;
    CRGB riderColor = CHSV(cycleHue, 255, brightness);
    for (byte y = 0; y < kMatrixHeight; y++) {
      leds[XY(x,y)] = riderColor;
    }
  }

  riderPos++; // byte wraps to 0 at 255, triwave8 is also 0-255 periodic

}



// Shimmering noise, uses global hue cycle
void glitter() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 15;
  }

  // Draw one frame of the animation into the LED array
  for (int x = 0; x < kMatrixWidth; x++) {
    for (int y = 0; y <kMatrixHeight; y++) {
      leds[XY(x,y)] = CHSV(cycleHue,255,random8(5)*63);
    }
  }

}


// Fills saturated colors into the array from alternating directions
byte currentColor = 0;
byte currentRow = 0;
byte currentDirection = 0;
void colorFill() {
  
  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 45;
    currentColor = 0;
    currentRow = 0;
    currentDirection = 0;
    currentPalette = RainbowColors_p;
  }

  // test a bitmask to fill up or down when currentDirection is 0 or 2 (0b00 or 0b10)
  if (!(currentDirection & 1)) {
    effectDelay = 45; // slower since vertical has fewer pixels
    for (byte x = 0; x < kMatrixWidth; x++) {
      byte y = currentRow;
      if (currentDirection == 2) y = kMatrixHeight - 1 - currentRow;
      leds[XY(x,y)] = currentPalette[currentColor];
    }
  } 

  // test a bitmask to fill left or right when currentDirection is 1 or 3 (0b01 or 0b11)
  if (currentDirection & 1) {
    effectDelay = 20; // faster since horizontal has more pixels
    for (byte y = 0; y < kMatrixHeight; y++) {
      byte x = currentRow;
      if (currentDirection == 3) x = kMatrixWidth - 1 - currentRow;
      leds[XY(x,y)] = currentPalette[currentColor];
    }
  }

  currentRow++;
  
  // detect when a fill is complete, change color and direction
  if ((!(currentDirection & 1) && currentRow >= kMatrixHeight) || ((currentDirection & 1) && currentRow >= kMatrixWidth)) {
    currentRow = 0;
    currentColor += random8(3,6);
    if (currentColor > 15) currentColor -= 16;
    currentDirection++;
    if (currentDirection > 3) currentDirection = 0;
    effectDelay = 300; // wait a little bit longer after completing a fill
  }


}

// Emulate 3D anaglyph glasses
void threeDee() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 50;
  }
  
   for (byte x = 0; x < kMatrixWidth; x++) {
     for (byte y = 0; y < kMatrixHeight; y++) {
       if (x < 7) {
         leds[XY(x,y)] = CRGB::Blue;
       } else if (x > 8) {
         leds[XY(x,y)] = CRGB::Red;
       } else {
         leds[XY(x,y)] = CRGB::Black;
       }
     }
   }
   
   leds[XY(6,0)] = CRGB::Black;
   leds[XY(9,0)] = CRGB::Black;

}

// Random pixels scroll sideways, uses current hue
#define rainDir 0
void sideRain() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 30;
  }
  
  scrollArray(rainDir);
  byte randPixel = random8(kMatrixHeight);
  for (byte y = 0; y < kMatrixHeight; y++) leds[XY((kMatrixWidth-1) * rainDir,y)] = CRGB::Black;
  leds[XY((kMatrixWidth-1)*rainDir, randPixel)] = CHSV(cycleHue, 255, 255); 

}

// Pixels with random locations and random colors selected from a palette
// Use with the fadeAll function to allow old pixels to decay
void confetti() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 10;
    selectRandomPalette();
  }

  // scatter random colored pixels at several random coordinates
  for (byte i = 0; i < 4; i++) {
    leds[XY(random16(kMatrixWidth),random16(kMatrixHeight))] = ColorFromPalette(currentPalette, random16(255), 255);//CHSV(random16(255), 255, 255);
    random16_add_entropy(1);
  }
   
}


// Draw slanting bars scrolling across the array, uses current hue
byte slantPos = 0;
void slantBars() {

  // startup tasks
  if (effectInit == false) {
    effectInit = true;
    effectDelay = 5;
  }

  for (byte x = 0; x < kMatrixWidth; x++) {
    for (byte y = 0; y < kMatrixHeight; y++) {
      leds[XY(x,y)] = CHSV(cycleHue, 255, quadwave8(x*32+y*32+slantPos));
    }
  }

  slantPos-=4;

}

