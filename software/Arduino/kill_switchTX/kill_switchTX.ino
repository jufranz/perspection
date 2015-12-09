#include <Kill_Switch.h>

#define LED 13
#define Mx 10000
char command;


void setup() {
    Serial.begin(9600);

    delay(10);
    Serial.println("Ready, Steady, Go");
    delay(10);

    pinMode(LED, OUTPUT);
    pinMode(A5, INPUT);
    digitalWrite(A5,HIGH);
}

/**
 * @brief Main loop of the program
 * @details In this function, we get messages from serial port and
 * execute them accordingly.
 */
 int val = 0;
void loop() {
    if(digitalRead(A5) == LOW){
      for(int i = 0; i < 100; i++){}
      if(digitalRead(A5) == LOW){
        digitalWrite(LED, HIGH);
        sendPacket('K');
      }
    }
    else{
      sendPacket('G');
      digitalWrite(LED,LOW);
    }
    delay(500);

    /*if(digitalRead(4) == LOW){
      for(int i = 0; i < 100; i++){}
      if(digitalRead(4) == LOW)
        digitalWrite(LED,HIGH);
    }
    else
      digitalWrite(LED,LOW);*/
   
   
}
