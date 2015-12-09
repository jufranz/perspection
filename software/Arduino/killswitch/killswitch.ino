#include <Kill_Switch.h>

#define MAX 10000 // is the timeout time
const int ledPin = 13;
const int gatePin = A0;
const int faultPin = 7;
const int sensePin = A1;
const int buttonPin = A5;
const int speakerPin = 6;

bool fault = false;
bool enabled = true;
bool btnState = false;

int boobs = 0;
int val = 0;
bool ok = true;

void setup() {
  // put your setup code here, to run once:
  //code for recieving from kill switch
  Serial.begin(9600);
  delay(10);
  Serial.println("Ready, Steady, Go");
  delay(10);
    
  pinMode(ledPin, OUTPUT);
  pinMode(gatePin, OUTPUT);
  pinMode(faultPin, OUTPUT);
  pinMode(sensePin, INPUT);
  digitalWrite(buttonPin, HIGH);
  digitalWrite(gatePin, HIGH);
  digitalWrite(ledPin, LOW);
  digitalWrite(faultPin, LOW);
  delay(10);
}


void loop() {
  //val = analogRead(sensePin);
  boobs = parsePacket(MAX);
  
  //Serial.println(val);
  if(val > 600 && !fault) {
    enabled = false;
    fault = true;
  }
  //xbee manual kill portion
  //will kill if we haven't recieved a message for
  //MAX miliseconds, max at the top of the file
  if(boobs == 3 || boobs == 1){
      ok = false;
      fault = true;
    }
  else
    ok = true;

  enabled = enabled && ok;
  
  digitalWrite(ledPin, !enabled); //LED will be off when enabled
  digitalWrite(faultPin, !fault); 
  digitalWrite(gatePin, enabled);

  /*
   * If the button is pressed (signal reads low)
   *  if the button state is false
   *    if fault is true, set fault to false, set button state to true
   *    if we've disabled power, set enable it, set enable to true, set button state to true
   *  otherwise set enable to false, set button state to tru
   *  
   *Else set button state to false
   */
  if(!digitalRead(buttonPin)) {
    if(!btnState) {
      if(fault) {
        fault = false;
      } else if(!enabled) {
        enabled = true;
        digitalWrite(gatePin, HIGH);
        delay(10);
      } else {
        enabled = false;
      }
      btnState = true;
    }
  } else {
    btnState = false;
  }

  if(fault) {
    int m = millis();
    if(m % 1000 < 250) {
      tone(speakerPin, 5000);
    } else if(m % 1000 < 500) {
      tone(speakerPin, 4000);
    } else {
      noTone(speakerPin);
    }
    
  } else {
    noTone(speakerPin);
  }

  //if(!fault) noTone(speakerPin);
}
