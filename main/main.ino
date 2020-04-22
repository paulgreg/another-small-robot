#define SWITCH_PIN 13

int motorEnablePin[] = {9, 10};
int motorPins[] = {6, 8, 5, 7};

char F = 'F';
char R = 'R';
char L = 'L';
char S = 'S';

int stepIdx = 0;
int delayUntilEndStep = 0;

char steps[] = {
  S,
  F,
  F,
  F,
  F,
  F,
  F,
  F,
  R,
  F,
  F,
  F,
  F,
  R,
  F,
  F
};

int stepNb = 5;


void setup() {
  pinMode(motorEnablePin[0], OUTPUT);
  pinMode(motorEnablePin[1], OUTPUT);
  pinMode(motorPins[0], OUTPUT);
  pinMode(motorPins[1], OUTPUT);
  pinMode(motorPins[2], OUTPUT);
  pinMode(motorPins[3], OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  Serial.begin(9600);
}

void setMotor(int idx, int speed, boolean reverse) {
  analogWrite(motorEnablePin[idx], speed);
  digitalWrite(motorPins[idx], ! reverse);
  digitalWrite(motorPins[idx + 2], reverse);
}

void turnLeft() {
  Serial.println("left");
  setMotor(0, 255, true);
  setMotor(1, 255, false);
  delayUntilEndStep = 3400;
}

void turnRight() {
  Serial.println("right");
  setMotor(0, 255, false);
  setMotor(1, 255, true);
  delayUntilEndStep = 3400;
}

void goForward() {
  Serial.println("forward");
  setMotor(0, 255, false);
  setMotor(1, 255, false);
  delayUntilEndStep = 3000;
}

void stop() {
  Serial.println("stop");
  setMotor(0, 0, false);
  setMotor(1, 0, false);
  delayUntilEndStep = 1000;
}

void end() {
  while(true) {
    Serial.println("end");
    delay(1000);
  }
}

void loop() {
  if (digitalRead(SWITCH_PIN) == LOW) {
    if (delayUntilEndStep > 0) delayUntilEndStep -= 100;
    if (delayUntilEndStep == 0) {
      stepIdx++;
      if (stepIdx > stepNb) end();
      Serial.print("Next step: ");
      Serial.println(steps[stepIdx]);
      switch (steps[stepIdx]) {
        case 'F':
          goForward();
          break;
        case 'R':
          turnRight();
          break;
        case 'L':
          turnRight();
          break;
        default:
          stop();
      }
    }
  } else {
    stop();
  }
  delay(100);
}
