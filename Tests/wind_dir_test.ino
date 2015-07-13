/* Weather station test
 * This code is just to test the conversion and ways to keep the wind direction data
 */
 
uint8_t gray[] = {
  0b0000,
  0b0001,
  0b0011,
  0b0010,
  0b0110,
  0b0111,
  0b0101,
  0b0100,
  0b1100,
  0b1101,
  0b1111,
  0b1110,
  0b1010,
  0b1011,
  0b1001,
  0b1000
};

String dir[] = {
"N", 
"NNE", 
"NE", 
"ENE", 
"E", 
"ESE", 
"SE", 
"SSE", 
"S", 
"SSW", 
"SW", 
"WSW", 
"W", 
"WNW", 
"NW",
"NNW",
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  for (int i = 0; i < 16; i++) {
    Serial.println(dir[gtob(gray[i])]);
  }
  
}

int ran;  //Don't know why this is here?

void loop() {
  // put your main code here, to run repeatedly:

}

//https://en.wikipedia.org/wiki/Gray_code

unsigned int gtob(unsigned int num) {
  unsigned int mask;
  for (mask = num >> 1; mask != 0; mask = mask >> 1) {
    num = num ^ mask;
  }
  return num;
}
