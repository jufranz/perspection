#include <Kill_Switch.h>

#define LED 13
#define MAX 10000 // is the timeout time

void setup() {
    Serial.begin(9600);

    delay(10);
    Serial.println("Ready, Steady, Go");
    delay(10);

    pinMode(LED, OUTPUT);
}

/*
 * VAL = 0 Means we got a good command
 * VAL = 1 Means we got a kill command
 * VAL = 2 Means we got garbage data
 * VAL = 3 Means we got a timeout and we're gonna kill it anyway
 */
 int val = 0;
void loop() {
    /// 1. get legal message
    val = parsePacket(MAX);

    //if we timed out or got a kill command
    if(val == 3 || val == 1){
      digitalWrite(LED,HIGH);
      while(1){}
    }
    else
      digitalWrite(LED,LOW);


      /*digitalWrite(LED,HIGH);
      delay(500);
      digitalWrite(LED,LOW);
      delay(500);*/
}
