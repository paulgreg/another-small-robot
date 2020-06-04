int motorEnablePin[] = {9, 10};
int motorPins[] = {6, 8, 5, 7};

#define SAFE_DISTANCE_IN_CM 20

#define FORWARD 'F'
#define RIGHT 'R'
#define LEFT 'L'
#define STOP 'S'

#define trigger 12
#define echo 11

char steps[] = {
  STOP,
  FORWARD,
  LEFT,
  FORWARD,
  RIGHT,
  FORWARD
};

int stepIdx = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motorEnablePin[0], OUTPUT);
  pinMode(motorEnablePin[1], OUTPUT);
  pinMode(motorPins[0], OUTPUT);
  pinMode(motorPins[1], OUTPUT);
  pinMode(motorPins[2], OUTPUT);
  pinMode(motorPins[3], OUTPUT);

  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  pinMode(echo, INPUT);
}

void setMotor(int idx, int speed, boolean reverse) {
  analogWrite(motorEnablePin[idx], speed);
  digitalWrite(motorPins[idx], !reverse);
  digitalWrite(motorPins[idx + 2], reverse);
}

void turnLeft() {
  Serial.println("left");
  setMotor(0, 255, true);
  setMotor(1, 255, false);
}

void turnRight() {
  Serial.println("right");
  setMotor(0, 255, false);
  setMotor(1, 255, true);
}

void goForward() {
  Serial.println("forward");
  setMotor(0, 255, false);
  setMotor(1, 255, false);
}

void stop() {
  Serial.println("stop");
  setMotor(0, 0, false);
  setMotor(1, 0, false);
}

void end() {
  stop();
  while(true) {
    Serial.println("end");
    delay(60000);
  }
}

long getDistanceInCm() {
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  long echoRead = pulseIn(echo, HIGH);
  return echoRead / 58;
}

boolean checkIfSafeDistance (long minDistanceInCm) {
  long distanceInCm = getDistanceInCm();
  Serial.print("Distance forward: ");
  Serial.println(distanceInCm);
  return distanceInCm > minDistanceInCm;
}

void loop() {
  if (stepIdx >= sizeof(steps)) end();

  if (!checkIfSafeDistance(SAFE_DISTANCE_IN_CM)) {
    stop();
    delay(5000);
  } else {
    char nextStep = steps[stepIdx]; 
    Serial.print("Next step: ");
    Serial.println(nextStep);
    
    switch (nextStep) {
      case FORWARD:
        goForward();
        delay(3500);
        break;
      case RIGHT:
        turnRight();
        delay(3100);
        break;
      case LEFT:
        turnLeft();
        delay(3100);
        break;
      case STOP:
      default:
        stop();
        delay(1000);
        break;
    }
    stepIdx++;
  }
}
