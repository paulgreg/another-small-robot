#define DEBUG false

#define SAFE_DISTANCE 12
#define TURNING_FOR 8

#define trigger 12
#define echo 11

int turnCounter = 0;

int motorEnablePin[] = {9, 10};
int motorPins[] = {6, 8, 5, 7};

void setup() {
  pinMode(motorEnablePin[0], OUTPUT);
  pinMode(motorEnablePin[1], OUTPUT);
  pinMode(motorPins[0], OUTPUT);
  pinMode(motorPins[1], OUTPUT);
  pinMode(motorPins[2], OUTPUT);
  pinMode(motorPins[3], OUTPUT);

  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  pinMode(echo, INPUT);
  if (DEBUG) Serial.begin(9600);
}

void loop() {
  if (turnCounter > 0) {
    if (DEBUG) Serial.println("turning");
    turnRight();
    turnCounter--;
  } else {
    long distanceInCm = getDistanceInCm();
    if (DEBUG) Serial.println(distanceInCm);
    
    if (distanceInCm > SAFE_DISTANCE) {
      if (DEBUG) Serial.println("forward");
      goForward();
    } else {
      turnCounter = TURNING_FOR;
    }
  }
  delay(250);
}

void stop() {
  setMotor(0, 0, false);
  setMotor(1, 0, false);
}

void turnRight() {
  setMotor(0, 255, false);
  setMotor(1, 255, true);
}

void goForward() {
  setMotor(0, 255, false);
  setMotor(1, 255, false);
}

void setMotor(int idx, int speed, boolean reverse) {
  analogWrite(motorEnablePin[idx], speed);
  digitalWrite(motorPins[idx], ! reverse);
  digitalWrite(motorPins[idx + 2], reverse);
}

long getDistanceInCm() {
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long echoRead = pulseIn(echo, HIGH);
  return echoRead / 58;
}
