// -------------------- Code Switch --------------------
int getCodeSwitch() {
  float decimal = 0;
  for (int i = 0; i < 6; i++) {
    if (digitalRead(codeSwitch[i]) == LOW) {
      decimal += pow(2, i);
    }
  }
  return round(decimal);
}

// -------------------- Motors --------------------

void setLeftMotorDirF() {
  digitalWrite(leftMotorDir, LOW);
  leftMotorCurrentDir = 1;
}

void setLeftMotorDirB() {
  digitalWrite(leftMotorDir, HIGH);
  leftMotorCurrentDir = -1;
}

void setRightMotorDirF() {
  digitalWrite(rightMotorDir, LOW);
  rightMotorCurrentDir = 1;
}

void setRightMotorDirB() {
  digitalWrite(rightMotorDir, HIGH);
  rightMotorCurrentDir = -1;
}

void setLeftMotorSpeed(int i) {
  analogWrite(pwmLeft, abs(i));
}

void setRightMotorSpeed(int i) {
  analogWrite(pwmRight, abs(i));
}

// -------------------- Infrared Sensors --------------------

boolean getIRLeft() {
  if ((digitalRead(iRLeft) == LOW)) return true;
  else return false;
}

boolean getIRCenter() {
  if ((digitalRead(iRSCenter) == LOW)) return true;
  else return false;
}

boolean getIRRight() {
  if ((digitalRead(iRSRight) == LOW)) return true;
  else return false;
}

// -------------------- Ultrasonic Sensors --------------------

bool uSInSight[] = {0, 0, 0, 0, 0};

bool getUSLeft() {
  return uSInSight[0];
}

bool getUSRight() {
  return uSInSight[1];
}

bool getUSFrontLeft() {
  return uSInSight[2];
}

bool getUSFrontRight() {
  return uSInSight[3];
}

bool getUSFrontCenter() {
  return uSInSight[4];
}

void resetUS() {
  pingTimer[0] = millis() + 75;
  for (uint8_t i = 1; i < sonarNum; i++) pingTimer[i] = pingTimer[i - 1] + pingInterval;
}

void ultrasonicSensors() {
  for (uint8_t i = 0; i < sonarNum; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += pingInterval * sonarNum;
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      sonar[currentSensor].ping_timer(echoCheck);
    }
  }
}

void echoCheck() {
  if (sonar[currentSensor].check_timer()) uSInSight[currentSensor] = true;
  else uSInSight[currentSensor] = false;
}

/*

int uSDist[2] = {0, 0};

int getUSDistL () {
  return uSInSight[0];
}

int getUSDistR () {
  return uSInSight[1];
}

void ultrasonicSensors2() {
  uint8_t i;
  // Side Sensors
  for (i = 0; i < 2 ; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += pingInterval * sonarNum ;
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      sonar[currentSensor].ping_timer(echoCheckS);
    }
  }
  // Front Sensors
  for (i = 2; i < sonarNum ; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += pingInterval * sonarNum ;
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      sonar[currentSensor].ping_timer(echoCheck);
    }
  }
}

void echoCheckS() {
  if (sonar[currentSensor].check_timer()) pingResult(currentSensor, sonar[currentSensor].ping_result / US_ROUNDTRIP_CM);
  else uSDist[currentSensor] = 0;
}

void pingResult(uint8_t sensor, int cm) {
  uSDist[sensor] = cm;
}
*/

// -------------------- IR + US --------------------

boolean getUSIRCenter() {
  return getUSFrontCenter() || getIRCenter();
}

boolean getUSIRRight() {
  return getUSFrontRight() || getIRRight();
}

boolean getUSIRLeft() {
  return getUSFrontLeft() || getIRLeft();
}

// -------------------- Line Sensors --------------------

boolean getLineSFrontRight() {
  if (digitalRead(lineSFrontRight) == LOW) return true;
  else return false;
}
boolean getLineSFrontLeft() {
  if (digitalRead(lineSFrontLeft) == LOW) return true;
  else return false;
}
boolean getLineSBackRight() {
  if (digitalRead(lineSBackRight) == LOW) return true;
  else return false;
}
boolean getLineSBackLeft() {
  if (digitalRead(lineSBackLeft) == LOW) return true;
  else return false;
}
