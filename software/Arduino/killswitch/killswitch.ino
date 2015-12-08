const int ledPin = 10;
const int gatePin = A0;
const int faultPin = 7;
const int sensePin = A1;
const int buttonPin = A5;
const int speakerPin = 6;

bool fault = false;
bool btnState = false;

byte duty = 0;;

void setTimer() {
  //sets timer1 interrupt at 2Hz
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  // set compare match register for 2Hz increments
  OCR1A = 1953; // = (16*10^6) / (8*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);

  setPwmFrequency(speakerPin, 8);
  setTimer();
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

ISR(TIMER1_COMPA_vect){
  if(fault) {
    duty ^= 127;
    analogWrite(speakerPin, duty);
  }
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

  if(!fault) analogWrite(speakerPin, 0);
}
