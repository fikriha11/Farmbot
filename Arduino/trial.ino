
void trialGUI() {
  String temp = String(SHT("Temp"));
  String humid = String(SHT("Hum"));
  String lumen = String(Lumen());
  String moisture = String(Moisture());
  //  for (int i = 1; i <= 10; i++) {
  //    Serial.println("A" + String(i) + "B" + temp + "C" + humid + "D" + lumen + "E" + moisture + "F");
  //    delay(2000);
  //  }
  Serial.println("A" + String(1) + "B" + temp + "C" + humid + "D" + lumen + "E" + moisture + "F");
}

void trialXYZ() {
  if (Serial.available() > 0) {
    dataTerima = Serial.readStringUntil('\n');
    if (dataTerima == "home") {
      Serial.println("HOME");
      digitalWrite(power, 0);
      delay(300);
      homie();
      digitalWrite(power, 1);
    } else  if (dataTerima == "tanam") {
      digitalWrite(power, 0);
      delay(300);
      tanam();
      digitalWrite(power, 1);
    } else  if (dataTerima == "pipa") {
      digitalWrite(power, 0);
      delay(300);
      ambilpipa();
      digitalWrite(power, 1);
    }
    else
    {
      //digitalWrite(power,0);
      //delay(300);
      int a = dataTerima.indexOf("A");
      int b = dataTerima.indexOf("B");
      int x = dataTerima.indexOf("X");
      int y = dataTerima.indexOf("Y");
      int z = dataTerima.indexOf("Z");
      int l = dataTerima.indexOf("L");
      int c = dataTerima.indexOf(";");
      String sLangkah = dataTerima.substring(1, c);
      long langkah = sLangkah.toInt();

      if (x > -1) {
        digitalWrite(power, 0);
        delay(300);
        gotoX(langkah);
      }
      if (y > -1) {
        digitalWrite(power, 0);
        delay(300);
        gotoY(langkah);
      }
      if (z > -1) {
        digitalWrite(power, 0);
        delay(300);
        gotoZ(langkah);
      }
      if (l > -1) {
        digitalWrite(power, 0);
        delay(300);
        gotoL(langkah);
      }
      if (a > -1) {
        servobukatitik();;

      }
      if (b > -1) {
        servotutup();
      }

      digitalWrite(power, 1);
    }
  }
}

void Trial() {
  int Tanaman = 9;
  int TanggalTanam = 13;
  int BulanTanam = 4;
  int TahunTanam = 2022;

  Serial.print(nTanaman[Tanaman]);
  Serial.print('\t');
  Serial.print(HitungUmur(TanggalTanam, BulanTanam, TahunTanam));
  Serial.print('\t');
  Serial.println(Takaran(Tanaman, HitungUmur(TanggalTanam, BulanTanam, TahunTanam)));
}

void trialRTC () {
  int tanggal, bulan, tahun, jam, menit, detik;
  float suhu;
  DateTime now = rtc.now();
  tanggal = now.day(), DEC;
  bulan   = now.month(), DEC;
  tahun   = now.year(), DEC;
  jam     = now.hour(), DEC;
  menit   = now.minute(), DEC;
  detik   = now.second(), DEC;
  suhu    = rtc.getTemperature();

  Serial.println(String() + tanggal + "-" + bulan + "-" + tahun);
  Serial.println(String() + jam + ":" + menit + ":" + detik);
  Serial.println(String() + "Suhu: " + suhu + " C");
  Serial.println();
  delay(1000);
}


void trialFlow() {
  Serial.println(FlowA.Count);
}

void trialSwitch() {
  Serial.print("Z: ");
  Serial.print(digitalRead(SwitchZ));
  Serial.print('\t');
  Serial.print("X: ");
  Serial.print(digitalRead(SwitchX));
  Serial.print('\t');
  Serial.print("Y: ");
  Serial.print(digitalRead(SwitchY));
  Serial.println('\t');
}

void trialRelay() {
  String data = "";

  if (Serial.available()) {
    data = Serial.readStringUntil('\n');
  }

  if (data == "a") {
    Serial.println("PumpWater");
    digitalWrite(PumpWater, ON);
  } if (data == "b") {
    Serial.println("PumpFert");
    digitalWrite(PumpFert, ON);
  } if (data == "c") {
    Serial.println("Power");
    digitalWrite(power, ON);
  } if (data == "d") {
    Serial.println("OFF");
    digitalWrite(PumpWater, OFF);
    digitalWrite(PumpFert, OFF);
    digitalWrite(power, OFF);
  }
}

void trialServo() {
  Servo1.write(90);   // Tutup
  Servo2.write(0);
  delay(2000);
  Servo1.write(0);  // Buka
  Servo2.write(90);
  delay(2000);
}

void trialTanam() {
  if (Serial.available()) {
    dataTerima = Serial.readStringUntil('\n');
  }

  if (dataTerima == "start") {
    Tanam();
  }
}

void trialSensor() {
  Serial.print("Temp: ");
  Serial.print(SHT("Temp"));
  Serial.print("\t");

  Serial.print("Humidity: ");
  Serial.print(SHT("Hum"));
  Serial.print("\t");

  Serial.print("Lux: ");
  Serial.print(Lumen());
  Serial.print("\t");

  Serial.print("Soil: ");
  Serial.println(Moisture());

}
