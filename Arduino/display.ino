
void menuCheck() {
  CursorPos = map(Rotary.pulseCnt, 0, 255, 0, 10);
  if (Rotary.pulseCnt > 55) {
    if (Button()) {
      ButtonState = true;
    }
    if (ButtonState && !Button()) {
      ButtonState = false;
      Plantstate = true;
    }
    CursorPos = 10;
  }
  else {
    if (Button()) {
      ButtonState = true;
    }
    if (ButtonState && !Button()) {
      ButtonState = false;
      Flushstate = true;
    }
    CursorPos = 0;
  }

  while (Plantstate) {
    displayTanam();
    if (Button()) {
      ButtonState = true;
    }
    if (ButtonState && !Button()) {
      ButtonState = false;
      Plantstate = false;
    }
  }
  while (Flushstate) {
    displaySiram();
    if (Rotary.pulseCnt > 55) {
      CursorPos = 10;
    }
    else {
      CursorPos = 0;
    }
    if (Button()) {
      ButtonState = true;
    }
    if (ButtonState && !Button()) {
      ButtonState = false;
      Flushstate = false;
    }
  }
}

void staticMenu() {
  display.setTextColor(WHITE);
  display.setTextSize(1.7);
  display.setCursor(10, 0);
  display.println("SIRAM");
  display.setCursor(10, 10);
  display.println("TANAM ");
  display.setCursor(2, CursorPos);
  display.println(">");
  display.display();
  display.clearDisplay();
  delay(50);
}

void displayTanam() {
  display.setTextColor(WHITE);
  display.setTextSize(1.7);
  display.setCursor(25, 0);
  display.println("PILIH TANAMAN");

  display.setTextSize(2);
  display.setCursor(50, 13);
  display.println(map(Rotary.pulseCnt, 0, 255, 0, 20));

  display.display();
  display.clearDisplay();
  delay(50);
}

void displaySiram() {
  display.setTextColor(WHITE);
  display.setTextSize(1.7);
  display.setCursor(10, 0);
  display.println("FERT");
  display.setCursor(10, 10);
  display.println("WATER");
  display.setCursor(2, CursorPos);
  display.println(">");
  display.display();
  display.clearDisplay();
  delay(50);
}
