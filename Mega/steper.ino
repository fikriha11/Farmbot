
void homie() {

  //  Serial.println("home: Z");
  digitalWrite(DirZ, HIGH);
  digitalRead(SwitchZ);

  do {
    digitalWrite(PulseZ, HIGH);
    delayMicroseconds(200); //Set Value
    digitalWrite(PulseZ, LOW);
    delayMicroseconds(200); //Set Value
  } while (digitalRead(SwitchZ) == HIGH);

  // Serial.println("home: X");
  digitalWrite(DirX, HIGH);
  digitalRead(SwitchX);
  do {
    digitalWrite(PulseX, HIGH);
    delayMicroseconds(200); //Set Value
    digitalWrite(PulseX, LOW);
    delayMicroseconds(200); //Set Value
  } while (digitalRead(SwitchX) == HIGH);

  // Serial.println("home: Y");
  digitalWrite(DirY, HIGH);
  digitalRead(SwitchY);
  do {
    digitalWrite(PulseY, HIGH);
    delayMicroseconds(200); //Set Value
    digitalWrite(PulseY, LOW);
    delayMicroseconds(200); //Set Value
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
