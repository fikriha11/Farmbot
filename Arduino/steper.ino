
void homie() {

  // Serial.println("home: L");
  digitalWrite(DirL, LOW);
  digitalRead(SwitchL);
  do {
    digitalWrite(PulseL, HIGH);
    delayMicroseconds(2000); //Set Value
    digitalWrite(PulseL, LOW);
    delayMicroseconds(2000); //Set Value
  } while (digitalRead(SwitchL) == HIGH);

  //  Serial.println("home: Z");
  digitalWrite(DirZ, HIGH);
  digitalRead(SwitchZ);

  do {
    digitalWrite(PulseZ, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseZ, LOW);
    delayMicroseconds(speedDelay); //Set Value
  } while (digitalRead(SwitchZ) == HIGH);

  //  servotutup();
  //  delay(1000);

  // Serial.println("home: X");
  digitalWrite(DirX, HIGH);
  digitalRead(SwitchX);
  do {
    digitalWrite(PulseX, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseX, LOW);
    delayMicroseconds(speedDelay); //Set Value
  } while (digitalRead(SwitchX) == HIGH);

  // Serial.println("home: Y");
  digitalWrite(DirY, HIGH);
  digitalRead(SwitchY);
  do {
    digitalWrite(PulseY, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseY, LOW);
    delayMicroseconds(speedDelay); //Set Value
  } while (digitalRead(SwitchY) == HIGH);

}


void gotoX(long eX) {
  //  Serial.print("Xe--> "); Serial.println(eX);
  eX *= nMM;

  if (eX < 0) {
    digitalWrite(DirX, HIGH);
    eX *= -1;
  } else
  {
    digitalWrite(DirX, LOW);
  }
  for (long i = 0; i <= eX; i++) {
    digitalWrite(PulseX, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseX, LOW);
    delayMicroseconds(speedDelay); //Set Value
  }
}

void gotoY(long Ye) {
  // Serial.print("Y --> "); Serial.println(Ye);
  Ye *= nMM;

  if (Ye < 0) {
    digitalWrite(DirY, HIGH);
    Ye *= -1;
  } else
  {
    digitalWrite(DirY, LOW);
  }
  for (long i = 0; i <= Ye; i++) {
    digitalWrite(PulseY, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseY, LOW);
    delayMicroseconds(speedDelay); //Set Value
  }
}

void gotoZ(long Ze) {
  // Serial.print("Z --> "); Serial.println(Ze);
  Ze *= nMM;

  if (Ze < 0) {
    digitalWrite(DirZ, HIGH);
    Ze *= -1;
  } else
  {
    digitalWrite(DirZ, LOW);
  }
  for (long i = 0; i <= Ze; i++) {
    //previousMicros = currentMicros;
    digitalWrite(PulseZ, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseZ, LOW);
    delayMicroseconds(speedDelay); //Set Value
  }
}

void gotoL(long Le) {
  // Serial.print("Z --> "); Serial.println(Ze);
  Le *= nMM;

  if (Le < 0) {
    digitalWrite(DirL, LOW);
    Le *= -1;
  } else
  {
    digitalWrite(DirL, HIGH);
  }
  for (long i = 0; i <= Le; i++) {
    //previousMicros = currentMicros;
    digitalWrite(PulseL, HIGH);
    delayMicroseconds(2000); //Set Value
    digitalWrite(PulseL, LOW);
    delayMicroseconds(2000); //Set Value
  }
}

void tanam() {
  homie();
  delay(1000);
  gotoY(100); delay(500);
  gotoX(100); delay(500);
  servobuka();
  gotoZ(350); delay(500);
  gotoL(12); delay(4000);
  homie();

}

void ambilpipa() {
  gotoY(20); delay(500);
  gotoX(107); delay(1000);
  //gotoZ(35); delay(1000);
  servobukatitik(); delay(3000);
  gotoY(-20); delay(1000);
  gotoZ(27); delay(1000);
  servotutup(); delay(2000);
  gotoY(100); delay(500);
  gotoZ(370); delay(500);
  gotoL(14); delay(4000);

  // Serial.println("home: L");
  digitalWrite(DirL, LOW);
  digitalRead(SwitchL);
  do {
    digitalWrite(PulseL, HIGH);
    delayMicroseconds(2000); //Set Value
    digitalWrite(PulseL, LOW);
    delayMicroseconds(2000); //Set Value
  } while (digitalRead(SwitchL) == HIGH);

  //  Serial.println("home: Z");
  digitalWrite(DirZ, HIGH);
  digitalRead(SwitchZ);

  do {
    digitalWrite(PulseZ, HIGH);
    delayMicroseconds(speedDelay); //Set Value
    digitalWrite(PulseZ, LOW);
    delayMicroseconds(speedDelay); //Set Value
  } while (digitalRead(SwitchZ) == HIGH);

  gotoY(-100); delay(2000);
  servobukatitik(); delay(1000);
  gotoY(20); delay(500);
  homie();
}


void servobuka() {
  //  digitalWrite(power, 1); delay(500);
  Servo1.write(45);
  //delay(1000);
  Servo2.write(40);
  delay(1000);
  //delay(1000);
  //  digitalWrite(power, 0); delay(500);
}
void servotutup() {
  //  digitalWrite(power, 1); delay(500);
  Servo1.write(95);
  //delay(1000);
  Servo2.write(0);
  delay(1000);
  //  digitalWrite(power, 0); delay(500);
}
void servobukatitik() {
  // digitalWrite(power, 1); delay(500);
  Servo1.write(70);
  //delay(1000);
  Servo2.write(20);
  delay(1000);
  // digitalWrite(power, 0); delay(500);
}
