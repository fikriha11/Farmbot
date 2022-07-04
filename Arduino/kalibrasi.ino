
bool kalibrasi = false;
String Data = "";


void kalibrasiFlow() {
  if (Serial.available()) {
    dataTrial = Serial.readStringUntil('\n');
    if (dataTrial == "100") {
      limit = 1300;
      digitalWrite(PumpFert, ON);
    } else if (dataTrial == "200") {
      limit = 2300;
      digitalWrite(PumpFert, ON);
    } else if (dataTrial == "300") {
      limit = 3300;
      digitalWrite(PumpFert, ON);
    } else if (dataTrial == "400") {
      limit = 4100;
      digitalWrite(PumpFert, ON);
    } else if (dataTrial == "500") {
      limit = 5000;
      digitalWrite(PumpFert, ON);
    }

    else if (dataTrial == "b") {
      digitalWrite(PumpFert, OFF);
    } else {
      FlowA.Count = 0;
    }

  }

  if ( FlowA.Count >= limit) {
    digitalWrite(PumpFert, OFF);
    dataTrial = "b";
  }

  Serial.println(FlowA.Count);
}


void kalibrasiSteper() {
  if (Serial.available()) {
    Data = Serial.readStringUntil('\n');
  }
  if (Data == "start") {
    kalibrasi = true;
  } if (Data == "reset") {
    kalibrasi = true;
    Count = 0;
  }
  if (kalibrasi) {
    switch (Count) {
      case 0:
        Serial.println("Preparation");
        homie();
        delay(500);
        siram(0);
        break;
      case 1 :
        Serial.println("Tanaman 1A");
        gotoY(50);
        delay(500);
        gotoX(50);
        delay(500);
        siram(0);
        break;
      case 2 :
        Serial.println("Tanaman 2A");
        gotoX(160);
        delay(500);
        siram(100);
        break;
      case 3 :
        Serial.println("Tanaman 3A");
        gotoX(160);
        delay(500);
        siram(0);
        break;
      case 4 :
        Serial.println("Tanaman 4A");
        gotoX(190);
        delay(500);
        siram(0);
        break;

      case 5 :
        Serial.println("Tanaman 1B");
        gotoY(190);
        delay(500);
        siram(100);
        break;
      case 6 :
        Serial.println("Tanaman 2B");
        gotoX(-170);
        delay(500);
        siram(100);
        break;
      case 7 :
        Serial.println("Tanaman 3B");
        gotoX(-170);
        delay(500);
        siram(0);
        break;
      case 8 :
        Serial.println("Tanaman 4B");
        gotoX(-160);
        delay(500);
        siram(100);
        break;

      case 9 :
        Serial.println("Tanaman 1C");
        gotoY(190);
        delay(500);
        siram(100);
        break;
      case 10 :
        Serial.println("Tanaman 2C");
        gotoX(160);
        delay(500);
        siram(100);
        break;
      case 11 :
        Serial.println("Tanaman 3C");
        gotoX(160);
        delay(500);
        siram(0);
        break;
      case 12 :
        Serial.println("Tanaman 4C");
        gotoX(180);
        delay(500);
        siram(100);
        break;

      case 13:
        homie();
        Count = 14;
        break;
    }
  }
}
