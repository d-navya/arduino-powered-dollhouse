#include <Servo.h>
#include <Adafruit_Keypad.h>
#include <Adafruit_Keypad_Ringbuffer.h>
#include <Keypad.h>
#include <Servo.h>

const int ldr_pin = 12;
const int led_pin = 13;
Servo ServoMotor;
char* password = "888";
int position = 0;
bool locked = true;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = { 8, 7, 6, 9 };
byte colPins[COLS] = { 5, 4, 3, 2 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int RedpinLock = 12;
int GreenpinUnlock = 13;

void setup() {
  ServoMotor.attach(11);
  pinMode(RedpinLock, OUTPUT);
  pinMode(GreenpinUnlock, OUTPUT);
  LockedPosition(locked);
  pinMode(ldr_pin,INPUT);
  pinMode(led_pin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(ldr_pin) == 1) {
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }
   
  Serial.println(digitalRead(ldr_pin));

  char key = keypad.getKey();
  if(key == '*' || key == '#') {
    position = 0;
  } else if(key == password[position]) {
    position++;
    if(position == 3) {
      locked = !locked;
      LockedPosition(locked);
      position = 0;
    }
  }
}

void LockedPosition(bool isLocked) {
  if(isLocked) {
    digitalWrite(RedpinLock, HIGH);
    digitalWrite(GreenpinUnlock, LOW);
    ServoMotor.write(0);
  } else {
    digitalWrite(RedpinLock, LOW);
    digitalWrite(GreenpinUnlock, HIGH);
    ServoMotor.write(90);
  }
}

