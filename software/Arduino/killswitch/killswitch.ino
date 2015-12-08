const int ledPin = 10;
const int gatePin = A0;
const int faultPin = 7;
const int sensePin = A1;
const int buttonPin = A5;

bool fault = false;
bool btnState = false;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
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
  int val = analogRead(sensePin);
  //Serial.println(val);
  digitalWrite(ledPin, fault);
  digitalWrite(faultPin, !fault);
  digitalWrite(gatePin, !fault);
  if(val > 600 && !fault) {
    fault = true;
  }
  if(!digitalRead(buttonPin)) {
    if(!btnState) {
      fault = !fault;
      btnState = true;
    }
  } else {
    btnState = false;
  }
}
