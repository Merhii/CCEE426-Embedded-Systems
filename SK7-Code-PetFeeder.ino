#include <Servo.h>
#include <SimpleDHT.h>
int pinDHT11 = 3;
SimpleDHT11 dht11;
Servo myServo;

unsigned long previousMillis = 0; 
const long interval = 3 * 60 * 60 * 1000;  // 3 hours in milliseconds
int Trg = 8, Echo = 9;
float S = 0.0343;
float d, t;

void setup() {
  myServo.attach(10);  // Attaches the servo on pin 9 to the servo object
  myServo.write(70); // initiale angle 
  pinMode(Trg, OUTPUT);
  pinMode(Echo, INPUT);
  Serial.begin(9600);
  
  delay(1000);
}


void loop() {
  unsigned long currentMillis = millis();  //current Time
  digitalWrite(Trg, HIGH);
  delayMicroseconds(2);
  digitalWrite(Trg, LOW);
  delayMicroseconds(10);
  t = pulseIn(Echo, HIGH);

  // Check if 3 hours have passed
  // if (currentMillis - previousMillis >= interval) {
  //   previousMillis = currentMillis;  // Save the current time

  //   // Perform the servo movement
  //   myServo.write(135);
  //   delay(1000);
  //   myServo.write(70);
  // }

byte temperature = 0;
byte humidity = 0;
if (dht11.read(pinDHT11, &temperature, &humidity, NULL))
{
return;
}
Serial.print((int)temperature);
Serial.print("C");
Serial.print("|");
if((int)humidity > 90 )
{
Serial.print("Not Safe To Consume");
}
else
{
Serial.print("Safe To Consume");
}
Serial.print("|");

  d = (S * t) / 2;
 if (d <= 150) {
  Serial.print("near");
} 
else {
  Serial.print("Far");

  }
Serial.print("|");

delay(5000);

  while (Serial.available()) {
    int servoButton = Serial.read();
    if (servoButton == 1) {
      myServo.write(135);
      delay(1000);
      myServo.write(70);
    }
  }
}