#define Button 2
bool st =true;
int LED1 = 13;
int LED2 = 12;
int LED3 = 14;
volatile int state1 = LOW;
volatile int state2 = LOW;
volatile int state3 = LOW;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(Button,INPUT);
  attachInterrupt(digitalPinToInterrupt(Button), blink, LOW);
}

void loop() {
  unsigned long currentMillis = millis();
   if (currentMillis % 500 == 0) {
    if (state1 == LOW) {
      state1 = HIGH;
    } else {
      state1 = LOW;
    }
    digitalWrite(LED1, state1);
    delay(50); 
    } 
  if (currentMillis % 600 == 0) {
    if (state2 == LOW) {
      state2 = HIGH;
    } else {
      state2 = LOW;
    }
    digitalWrite(LED2, state2);
    delay(50);
  }
  if (currentMillis % 700 == 0) {
    if (state3 == LOW) {
      state3 = HIGH;
    } else {
      state3 = LOW;
    }
    digitalWrite(LED3, state3);
    delay(50);
  }
}


void blink() {
    ;;
  }
