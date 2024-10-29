const int redPin = 13;
const int irSensor = 12;
const int buzzer = 7;
const int soundSensor = 2;
const int led = 11;

int redBrightness = 0;
int fadeAmount = 5;
boolean is_on = false;
int lastSoundSensorState = LOW;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(irSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(soundSensor, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int currentSoundSensorState = digitalRead(soundSensor);

  if (currentSoundSensorState == HIGH && lastSoundSensorState == LOW) {
    is_on = !is_on;
    digitalWrite(led, is_on ? HIGH : LOW);
    delay(500);
  }
  
  lastSoundSensorState = currentSoundSensorState;

  analogWrite(redPin, redBrightness);
  redBrightness += fadeAmount;
  if (redBrightness <= 0 || redBrightness >= 255) {
    fadeAmount = -fadeAmount;
  }

  int irValue = digitalRead(irSensor);
  Serial.print("Sensor Value = ");
  Serial.println(irValue);

  if (irValue == LOW) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(30);
}

