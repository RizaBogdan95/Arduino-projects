#include <LEDEffects.h>
short arrLED[] = { 2, 3, 4, 5, 6, 7, 8};
const int nNumLEDs = sizeof(arrLED)/sizeof(short);
int i = 0;
int x;
LEDEffects LED(nNumLEDs, arrLED);
void setup() {
  LED.InitLEDPins();
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    x = Serial.read();
  }
  if (x==49)  ef1();
  if (x==50)  ef2();
  if (x==51)  ef3();
  if (x==52)  ef4();
  if (x==53)  ef5();
  if (x==54)  ef6();
  if (x==55)  ef7();
  if (x==56)  ef8();

}


void ef1() {
  LED.OneByOne(MOVE_RIGHT, 50, HIGH);
  LED.OneByOne(MOVE_RIGHT, 50, LOW);
}
void ef2() {
  LED.OneByOne(MOVE_LEFT, 50, HIGH);
  LED.OneByOne(MOVE_LEFT, 50, LOW);
}
void ef3() {
  for(i = 0; i < 2; i++) {
    LED.SingleLED(MOVE_RIGHT, 50, (i > 0));
    LED.SingleLED(MOVE_LEFT , 50, true);
  }
}
void ef4() {
  for(i = 0; i < 4; i++) {
    LED.DoSegments(3, MOVE_RIGHT, 100, (i > 0));
    LED.DoSegments(3, MOVE_LEFT , 100, true);
    }
}
void ef5() {
  for(i = 0; i < 4; i++) {
    LED.ToCenter(60);
  }
}
void ef6() {
  for(i = 0; i < 3; i++) {
    LED.FromCenter(HIGH, RETURN_TO_DARKNESS, 100);
    delay(100);
  }
  for(i = 0; i < 3; i++) {
    LED.FromCenter(HIGH, STAY_HIGH, 100);
    delay(100);
  }
}
void ef7() {
  for( i = 0; i < 3; i++) {
    LED.BlinkAllLEDs(250);
    delay(250);
  }
}
void ef8() {
  LED.RandomTrigger(HIGH, 100);
  delay(1000);
  LED.RandomTrigger(LOW, 100);
  LED.SingleLED(MOVE_LEFT, 40, false);
  LED.SingleLED(MOVE_LEFT, 30, false);
  LED.SingleLED(MOVE_LEFT, 20, false);
  LED.SingleLED(MOVE_LEFT, 10, false);
}

