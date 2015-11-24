//Test code for Scissor Arm Demo using Arduino for now
//12V DC motor driven by pin 9

int motorPin = 9;
void setup() {
 pinMode(motorPin, OUTPUT);
}

void loop() {
 digitalWrite(motorPin, HIGH);
 delay(1000); 
 digitalWrite(motorPin, LOW);
 delay(1000);
 
}
