
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
      homie();
    } else {
      int x = dataTerima.indexOf("X");
      int y = dataTerima.indexOf("Y");
      int z = dataTerima.indexOf("Z");
      int c = dataTerima.indexOf(";");
      String sLangkah = dataTerima.substring(1, c);
      long langkah = sLangkah.toInt();

      if (x > -1) {
        gotoX(langkah);
      }
      if (y > -1) {
        gotoY(langkah);
      }
      if (z > -1) {
        gotoZ(langkah);
      }
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
