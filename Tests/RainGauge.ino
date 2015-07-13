/* AWS - Rain Gauge test code

#Logs the rain fall to eeprom when a push button is pressed
#This version works nicely with no interrupts because of the
#function checking the button state for a change and because
#the bucket does not move at lightning speed
 
By Reece May
Blog: https://www.ziggyelectronics.blogspot.com
Written: 3/30/2015
*/
 
#include <EEPROM.h>
 
//Variables
int count = 0;
float mm_const = 0.25;  //calibrated mm of rain for a mm/m^2/tip
float mm_rain = 0.00;
int state = 0;
int button_state = 0;
 
void setup(){
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  //  DDRB |= (1 << 1);
  //  PORTB |= (1 << 1);
 
  Serial.begin(9600);
  Serial.println("Rain Gauge Test Code");
}
int previous = 1;  //no false reading on boot
 
int tip(int to_test){
  int current = to_test;
 
  if(current != previous){
    previous = current;
    return current;
  }
  else return 0;
}
 
void loop(){
 
  //   digitalRead(3);//(PINB & (1 << 0));
 
  button_state = digitalRead(2);
  delay(10);
  if(tip(button_state)){
    count += 1;
    //   Serial.println(count);
  }
  else count = count;
  //Function to see if log button is pushed and stores tip count once
  if(digitalRead(3) == 0 && !state){
    digitalWrite(13, 1);
    delay(50);
    EEPROM.write(0, count);  //writes count as no need for float storage
    delay(50);
    digitalWrite(13, 0);
    state = 1;  //run only once, this is 0 when Serial is called
  }
  if(Serial.available()){
    if(Serial.read() == 'k'){
      byte rea = EEPROM.read(0);
      mm_rain = (rea) * mm_const;
      delay(100);
      Serial.print("count: ");
      Serial.println(rea);
      Serial.print("rain: ");
      Serial.println(mm_rain);
 
      state = 0; 
    }
    else if(Serial.read() == 'c'){
      count = 0;
      mm_rain = 0;
      Serial.println(count);
      Serial.println(mm_rain);
    }
  }
}
