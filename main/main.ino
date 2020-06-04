int motorEnablePin[] = {9, 10};
int motorPins[] = {6, 8, 5, 7};

#define FORWARD 'F'
#define RIGHT 'R'
#define LEFT 'L'
#define STOP 'S'

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

void loop() {
  if (stepIdx >= sizeof(steps)) end();

  char nextStep = steps[stepIdx]; 
  Serial.print("Next step: ");
  Serial.println(nextStep);
  
  switch (nextStep) {
    case FORWARD:
      goForward();
      delay(3400);
      break;
    case RIGHT:
      turnRight();
      delay(3000);
      break;
    case LEFT:
      turnRight();
      delay(3000);
      break;
    case STOP:
    default:
      stop();
      delay(1000);
      break;
  }
  stepIdx++;
  Serial.print("stepIdx: ");
  Serial.println(stepIdx);

}
