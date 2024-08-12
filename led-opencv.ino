#include<SoftwareSerial.h>

// Define LED pins
#define LED_PINKY 2
#define LED_RING 3
#define LED_MIDDLE 4
#define LED_INDEX 5
#define LED_THUMB 6

char number[50];
char c;
int state = 0;
String myStringRec;
int stringCounter = 0;
bool stringCounterStart = false;
String myRevivedString;
int stringLength = 6;

int ledPinky, ledMiddle, ledIndex, ledThumb, ledRing;

void setup() {
  Serial.begin(9600);
  
  // Initialize LED pins as outputs
  pinMode(LED_PINKY, OUTPUT);
  pinMode(LED_RING, OUTPUT);
  pinMode(LED_MIDDLE, OUTPUT);
  pinMode(LED_INDEX, OUTPUT);
  pinMode(LED_THUMB, OUTPUT);

  // Turn off all LEDs at startup
  digitalWrite(LED_PINKY, LOW);
  digitalWrite(LED_RING, LOW);
  digitalWrite(LED_MIDDLE, LOW);
  digitalWrite(LED_INDEX, LOW);
  digitalWrite(LED_THUMB, LOW);
}

void loop() {
  receiveData();
  
  // Control LEDs based on the received data
  digitalWrite(LED_PINKY, ledPinky);
  digitalWrite(LED_RING, ledRing);
  digitalWrite(LED_MIDDLE, ledMiddle);
  digitalWrite(LED_INDEX, ledIndex);
  digitalWrite(LED_THUMB, ledThumb);
}

void receiveData() {
  int i = 0;
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '$') {
      stringCounterStart = true;
    }
    if (stringCounterStart == true) {
      if (stringCounter < stringLength) {
        myRevivedString = String(myRevivedString + c);
        stringCounter++;
      }
      if (stringCounter >= stringLength) {
        stringCounter = 0;
        stringCounterStart = false;
        ledPinky = myRevivedString.substring(1, 2).toInt();
        ledRing = myRevivedString.substring(2, 3).toInt();
        ledMiddle = myRevivedString.substring(3, 4).toInt();
        ledIndex = myRevivedString.substring(4, 5).toInt();
        ledThumb = myRevivedString.substring(5, 6).toInt();
        myRevivedString = "";
      }
    }
  }
}
