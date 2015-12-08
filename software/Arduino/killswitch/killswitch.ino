const int ledPin = 10;
const int gatePin = A0;
const int faultPin = 7;
const int sensePin = A1;
const int buttonPin = A5;
const int speakerPin = 6;

bool fault = false;
bool enabled = true;
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
  digitalWrite(ledPin, !enabled);
  digitalWrite(faultPin, !fault);
  digitalWrite(gatePin, enabled);
  if(val > 600 && !fault) {
    enabled = false;
    fault = true;
  }
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
