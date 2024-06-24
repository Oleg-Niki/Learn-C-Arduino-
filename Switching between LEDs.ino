#include <Arduino.h>

enum STATE_CLR
{
  STATE_CLR_0,
  STATE_CLR_1,
  STATE_CLR_2
};

volatile byte state = LOW;
const byte interruptPin = 3;
volatile STATE_CLR stateClr = STATE_CLR_0;

const byte RED_LIGHT_PIN = 10;    
const byte GREEN_LIGHT_PIN = 11;  
const byte YELLOW_LIGHT_PIN = 12;  
const byte ADDITIONAL_BLUE_LIGHT_PIN = 9;
const byte ADDITIONAL_WHITE_LIGHT_PIN = 8;

const byte RED_LIGHT_SWITCH_PIN = 2;  
const byte GREEN_LIGHT_SWITCH_PIN = 6;
const byte YELLOW_LIGHT_SWITCH_PIN = 4;
const byte ADDITIONAL_BLUE_LIGHT_SWITCH_PIN = 5;

volatile unsigned long count = 0;
volatile unsigned long prevCount = 0;

void setup() {

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), buttonClickISR, FALLING);

  // Configure our LED control pins as OUTPUT pins
  pinMode(RED_LIGHT_PIN, OUTPUT);    
  pinMode(GREEN_LIGHT_PIN, OUTPUT);
  pinMode(YELLOW_LIGHT_PIN, OUTPUT);  
  pinMode(ADDITIONAL_BLUE_LIGHT_PIN, OUTPUT);

  // Configure the switch pins as INPUT pins
  pinMode(RED_LIGHT_SWITCH_PIN, INPUT);
  pinMode(GREEN_LIGHT_SWITCH_PIN, INPUT);
  pinMode(YELLOW_LIGHT_SWITCH_PIN, INPUT);  
  pinMode(ADDITIONAL_BLUE_LIGHT_SWITCH_PIN, INPUT);

  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial);  
}

void loop() {
/*
  if (digitalRead(RED_LIGHT_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
    digitalWrite(RED_LIGHT_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(RED_LIGHT_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }

  if (digitalRead(GREEN_LIGHT_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
    digitalWrite(GREEN_LIGHT_PIN, HIGH);              // turn on LED by providing HIGH voltage (5v)
  } else {
    digitalWrite(GREEN_LIGHT_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }

  if (digitalRead(YELLOW_LIGHT_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
    digitalWrite(YELLOW_LIGHT_PIN, HIGH);              // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(YELLOW_LIGHT_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  }
*/
  switch (stateClr)
  {
    case STATE_CLR_0:
      digitalWrite(YELLOW_LIGHT_PIN, LOW);
      digitalWrite(GREEN_LIGHT_PIN, LOW);
      digitalWrite(RED_LIGHT_PIN, HIGH);
      break;
    case STATE_CLR_1:
      digitalWrite(YELLOW_LIGHT_PIN, HIGH);
      digitalWrite(GREEN_LIGHT_PIN, LOW);
      digitalWrite(RED_LIGHT_PIN, LOW);
      break;
    case STATE_CLR_2:
      digitalWrite(YELLOW_LIGHT_PIN, LOW);
      digitalWrite(GREEN_LIGHT_PIN, HIGH);
      digitalWrite(RED_LIGHT_PIN, LOW);
      break;
    default:
      digitalWrite(YELLOW_LIGHT_PIN, LOW);
      digitalWrite(GREEN_LIGHT_PIN, LOW);
      digitalWrite(RED_LIGHT_PIN, LOW);
  }

  digitalWrite(ADDITIONAL_BLUE_LIGHT_PIN, state);

  count++;

  //if (digitalRead(ADDITIONAL_BLUE_LIGHT_SWITCH_PIN) == HIGH) {  // if switch is on (HIGH voltage)
  //  digitalWrite(ADDITIONAL_BLUE_LIGHT_PIN, HIGH);              // turn the LED on (HIGH is the voltage level)
  //} else {
  //  digitalWrite(ADDITIONAL_BLUE_LIGHT_PIN, LOW);  // turn off LED by setting output to LOW (zero volts)
  //}
}

void buttonClickISR() {
 
  bool skip = (count - prevCount < 500);
  prevCount = count;

  if(skip)
      return;

  state = !state;
    Serial.print(F("buttonClickISR: "));
    Serial.println(state);
    Serial.print(F("State COLOR: "));
    Serial.println(stateClr);
    Serial.print(F("Count: "));
    Serial.println(count);


  switch (stateClr)
  {
    case STATE_CLR_0:
      stateClr = STATE_CLR_1;
      break;
    case STATE_CLR_1:
      stateClr = STATE_CLR_2;
      break;
    case STATE_CLR_2:
      stateClr = STATE_CLR_0;
      break;
  }
}
