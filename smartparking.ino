#define TRIG1 2
#define ECHO1 3

#define TRIG2 4
#define ECHO2 5

#define TRIG3 6
#define ECHO3 7

#define RED1 8
#define GREEN1 9

#define RED2 10
#define GREEN2 11

#define RED3 12
#define GREEN3 13

#define BUZZER A0

const int threshold = 10;

long getDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if(duration == 0)
    return 999;

  return duration * 0.034 / 2;
}

void setup()
{
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);

  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT);

  pinMode(RED1, OUTPUT);
  pinMode(GREEN1, OUTPUT);

  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);

  pinMode(RED3, OUTPUT);
  pinMode(GREEN3, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  long d1 = getDistance(TRIG1, ECHO1);
  delay(50);

  long d2 = getDistance(TRIG2, ECHO2);
  delay(50);

  long d3 = getDistance(TRIG3, ECHO3);

  bool slot1Occupied = (d1 < threshold);
  bool slot2Occupied = (d2 < threshold);
  bool slot3Occupied = (d3 < threshold);

  // Slot 1 LEDs
  digitalWrite(RED1, slot1Occupied);
  digitalWrite(GREEN1, !slot1Occupied);

  // Slot 2 LEDs
  digitalWrite(RED2, slot2Occupied);
  digitalWrite(GREEN2, !slot2Occupied);

  // Slot 3 LEDs
  digitalWrite(RED3, slot3Occupied);
  digitalWrite(GREEN3, !slot3Occupied);

  // Buzzer only when all slots occupied
  if(slot1Occupied && slot2Occupied && slot3Occupied)
  {
    tone(BUZZER, 2000);
  }
  else
  {
    noTone(BUZZER);
  }

  Serial.print("S1=");
  Serial.print(d1);
  Serial.print("cm  ");

  Serial.print("S2=");
  Serial.print(d2);
  Serial.print("cm  ");

  Serial.print("S3=");
  Serial.print(d3);
  Serial.println("cm");

  delay(200);
}