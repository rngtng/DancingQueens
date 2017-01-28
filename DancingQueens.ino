
//// ------------------ Defaults -----------------------
#define RANDOM_LOOPS_MIN  1
#define RANDOM_LOOPS_MAX 10

#define RANDOM_SLEEP_MIN     10  // in milliseconds
#define RANDOM_SLEEP_MAX   1000  // in milliseconds
#define RANDOM_SLEEP_STEPS  100  // in milliseconds

#define CHANNELS 8

//// ------------------ Patterns -----------------------
// any number below zero get replaced by random value within given range
// { <loops>, <sleep>, <data length>, < ... data ... > }
int p1[] = {
  10,   -1, 2, 0x00, 0x01};
int p2[] = {
  1,  100, 16, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
int p3[] = {
  2,  500,  8, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
int p4[] = {
  20,  500,  6, B00011000, B00100100, B01000010, B10000001, B01000010, B00100100};

int *patterns[] = {
  p1, p2, p3, p4 };

//// ------------------ nothing to edit below here -----------------------
int number_of_patterns = sizeof(patterns)/sizeof(int);
int current_pos;
int current_pattern;
int current_loop;
int current_size;

//// ------------------ main -----------------------
void setup() {
  randomSeed(analogRead(0));

  // set the digital pin as output:
  DDRD = DDRD | B11111100;
  DDRH = DDRH | B01111000;
  DDRB = DDRB | B1111111;

  // turn all off
  set(0);

  // turn all off
  load_pattern(3);
}

void loop()
{
  int value = positive_value_or_random(patterns[current_pattern][current_pos + 3]);
  int sleep = positive_sleep_or_random(patterns[current_pattern][1]);
  setM(value);
  delay(sleep);
  current_pos++;
  if(current_pos > current_size) restart_loop();
}

//// -----------------------------------------
void set(byte v) {
  PORTD = (((255 - v) << 6) & B11000000); //  | (PORTD & B0000011);
  PORTB = (((255 - v) >> 2) & B00111111);
}

void setM(byte v) {
  PORTH = ((( v) << 3) & B01111000); //  | (PORTD & B0000011);
  PORTB = ((( v)) & B11111111);
}


void restart_loop() {
  current_pos = 0;
  current_loop--;
  if(current_loop < 0) load_random_pattern();
}

// -------------------------------------------------------------------
void load_random_pattern() {
  load_pattern(random(number_of_patterns));
}

void load_pattern(int pattern_nr) {
  current_pattern = pattern_nr;
  current_loop    = positive_loop_or_random(patterns[current_pattern][0]);
  current_size    = patterns[current_pattern][2];
  restart_loop();
}

// -------------------------------------------------------------------
int positive_value_or_random(int i) {
  return (i >= 0) ? i : random(0, 1 << CHANNELS);
}

int positive_loop_or_random(int i) {
  return (i > 0) ?  i : random(RANDOM_LOOPS_MIN, RANDOM_LOOPS_MAX + 1);
}

int positive_sleep_or_random(int i) {
  return (i > 0) ? i : random_sleep();
}

int random_sleep() {
  return RANDOM_SLEEP_MIN + random((RANDOM_SLEEP_MAX - RANDOM_SLEEP_MIN) / RANDOM_SLEEP_STEPS) * RANDOM_SLEEP_STEPS;
}


