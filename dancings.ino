
#define MIN_TIME 10    // in milliseconds
#define MAX_TIME 1000  // in milliseconds

// any number below zero get replaced by random from from 0 ... 255
// <loops>, <delay>
int p1[] = { 10, -1, 2, 0x00, 0x01};
int p1[] = { 10, -1, 2, 0x00, 0x01};
// int patternb[] = {0, 1, 0, 1, 0, 1};
// int *patterns[] = { patterna, patternb }; 



//int patterns[1][] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 12, 13, 14, 15, 16, 100};
int patterns[3][17] = {
  {
    0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  -1    }
  ,  
  
  ,
  {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, -1    }
};

int current_pattern;
int current_pos;
int current_size;

void setup() {
  // set the digital pin as output:
  DDRD = DDRD | B11111100;
  DDRB = DDRB | B00111111;
  set(0);
  reset();
}

void loop()
{ 
  int v = value(patterns[current_pattern][current_pos]);
  int s = value(patterns[current_pattern][16]) * 10;
  set(v);
  delay(s);
  current_pos++;
  if(current_pos > 15) reset();
}

void set(byte v) {
  PORTD = (((255 - v) << 6) & B11000000); //  | (PORTD & B0000011);
  PORTB = (((255 - v) >> 2) & B00111111);
}

void reset() {
  current_pos = 0;
  current_pattern = 2;
  current_size = sizeof(patterns[current_pattern])/sizeof(int);
}

int value(int i) {
  if(i < 0) {
    return random(255);
  }
  return i;
}



