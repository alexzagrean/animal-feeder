#include <dht11.h>

#include <Adafruit_Sensor.h>

#include <PCD8544.h>


#define trigPin1 1
#define echoPin1 2
#define trigPin2 8
#define echoPin2 9
#define trigPin3 10
#define echoPin3 11

#define DHT11_PIN 7

long duration, distance, RightSensor, BackSensor, FrontSensor, LeftSensor, isClose;

static const byte glyph[] = { B00010000, B00110100, B00110000, B00110100, B00010000 };
static PCD8544 lcd;

dht11 DHT11;

void setup()
{
 
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
   pinMode(12, OUTPUT);

  lcd.begin(84, 48);
  lcd.createChar(0, glyph);
}

void loop() {
   
  SonarSensor(trigPin1, echoPin1);
  RightSensor = distance;
  SonarSensor(trigPin2, echoPin2);
  LeftSensor = distance;
  SonarSensor(trigPin3, echoPin3);
  FrontSensor = distance;
  
  if (isClose == 0 && (LeftSensor < 10 || FrontSensor < 10)) {
    Serial.print("Cainele e aproape \n");
    digitalWrite(12, HIGH); // Turn the LED on
    isClose = 1;
    lcd.setCursor(0, 0);
    lcd.print("Cainele e aproape");
  }
  if (LeftSensor > 10 && FrontSensor > 10) {
    digitalWrite(12, LOW); // Turn the LED on
    isClose = 0;
    lcd.setCursor(0, 0);
    lcd.print("                          ");
  }
  
  int chk = DHT11.read(7);

  
  Serial.print(LeftSensor);
  Serial.print(" - ");
  Serial.print(FrontSensor);
  Serial.print(" - ");
  Serial.println(RightSensor);

}



void SonarSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

}
