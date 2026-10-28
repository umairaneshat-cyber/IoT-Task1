#include <Servo.h>

Servo diverter;

int trig = 10, echo = 11;                    // ultrasonic sensor
int ena = 5, in1 = 7, in2 = 8;               // motor driver
int ledShort = 2, ledMed = 3, ledLong = 4;   // indicator LEDs

float beltSpeed = 10.0;    // cm per second (measure this on your real belt)
int detectDist = 100;      // cm: something closer than this is "in front of the sensor"
float shortMax = 10.0;     // cm: below this = short
float medMax = 20.0;       // cm: below this = medium, otherwise long

int shortCount = 0, medCount = 0, longCount = 0;

int getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH, 12000);       // 0 if nothing answers
  return t * 0.034 / 2;
}

bool objectPresent() {
  int d = getDistance();
  return d > 0 && d < detectDist;
}

void beltRun()  { digitalWrite(in1, HIGH); digitalWrite(in2, LOW); analogWrite(ena, 150); }

// measures how long the object stays in front of the sensor
float measureLength() {
  unsigned long start = millis();
  unsigned long lastSeen = start;
  int misses = 0;
  while (misses < 3) {                       // object has passed after 3 empty readings
    if (objectPresent()) { lastSeen = millis(); misses = 0; }
    else misses++;
    delay(20);
  }
  float seconds = (lastSeen - start) / 1000.0;
  return beltSpeed * seconds;                // length = speed x time
}

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ledShort, OUTPUT);
  pinMode(ledMed, OUTPUT);
  pinMode(ledLong, OUTPUT);
  diverter.attach(9);
  diverter.write(90);
  beltRun();
  Serial.println("Length sorter ready");
}

void loop() {
  if (objectPresent()) {                     // an object reaches the sensor
    Serial.println("Object detected, measuring...");
    float length = measureLength();          // belt keeps running
    if (length < 1.0) return;                // too short, treat as noise

    int led;
    if (length < shortMax)    { diverter.write(30);  led = ledShort; shortCount++; }
    else if (length < medMax) { diverter.write(90);  led = ledMed;   medCount++;   }
    else                      { diverter.write(150); led = ledLong;  longCount++;  }

    digitalWrite(led, HIGH);
    Serial.print("Length: ");  Serial.print(length, 1);
    Serial.print(" cm | Short: ");  Serial.print(shortCount);
    Serial.print("  Medium: ");     Serial.print(medCount);
    Serial.print("  Long: ");       Serial.print(longCount);
    Serial.print("  Total: ");      Serial.println(shortCount + medCount + longCount);

    delay(1500);                             // object travels to the bin
    digitalWrite(led, LOW);
    diverter.write(90);
  }
  delay(20);
}
