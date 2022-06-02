
/*
   DATA YG DI AMBIL
   Plant_id
   Umur
   Umur Panen
*/

String receiveData;
int nA, nB, nC, nD, nE, nF, nG, nH, nI;
String dA, dB, dC, dD, dE, dF, dG, dH, dI;

/* SPLIt */
String SaveData[10];
String SplitData;
int StringData;

/*
   Variable Temporary
*/

int Plant_ID;
int UmurSekarang;
int UmurPanen;

/*
   Variable Temporary
*/

void INISIALISASI() {

  /** Addres EEPRM **/

  Tanaman1.Usia = 1;
  Tanaman1.JenisTanaman = 2;
  Tanaman1.Panen = 3;

  Tanaman2.Usia = 4;
  Tanaman2.JenisTanaman = 5;
  Tanaman2.Panen = 6;

  Tanaman3.Usia = 7;
  Tanaman3.JenisTanaman = 8;
  Tanaman3.Panen = 9;

  Tanaman4.Usia = 10;
  Tanaman4.JenisTanaman = 11;
  Tanaman4.Panen = 12;

  Tanaman5.Usia = 13;
  Tanaman5.JenisTanaman = 14;
  Tanaman5.Panen = 15;

  Tanaman6.Usia = 16;
  Tanaman6.JenisTanaman = 17;
  Tanaman6.Panen = 18;

  Tanaman7.Usia = 19;
  Tanaman7.JenisTanaman = 20;
  Tanaman7.Panen = 21;

  Tanaman8.Usia = 22;
  Tanaman8.JenisTanaman = 23;
  Tanaman8.Panen = 24;
}


void parse(String Data) {
  nA = Data.indexOf("A");
  nB = Data.indexOf("B");
  nC = Data.indexOf("C");
  nD = Data.indexOf("D");
  nE = Data.indexOf("E");
  nF = Data.indexOf("F");
  nG = Data.indexOf("G");
  nH = Data.indexOf("H");
  nI = Data.indexOf("I");

  dA = Data.substring(nA + 1, nB);
  dB = Data.substring(nB + 1, nC);
  dC = Data.substring(nC + 1, nD);
  dD = Data.substring(nD + 1, nE);
  dE = Data.substring(nE + 1, nF);
  dF = Data.substring(nF + 1, nG);
  dG = Data.substring(nG + 1, nH);
  dH = Data.substring(nH + 1, nI);
}

void split(String Data) {
  int i1 = Data.indexOf(',');
  int i2 = Data.indexOf(',', i1 + 1);

  Plant_ID = Data.substring(0, i1).toInt();
  UmurSekarang = Data.substring(i1 + 1, i2).toInt();
  UmurPanen = Data.substring(i2 + 1).toInt();
}

void ReceiveData() {
  while (Serial.available()) {
    receiveData = Serial.readString();
    parse(receiveData);
    SaveEEPROM();
  }
}

void SaveEEPROM() {
  split(dA);
  EEPROM.write(Tanaman1.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman1.Usia, UmurSekarang);
  EEPROM.write(Tanaman1.Panen, UmurPanen);

  split(dB);
  EEPROM.write(Tanaman2.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman2.Usia, UmurSekarang);
  EEPROM.write(Tanaman2.Panen, UmurPanen);

  split(dC);
  EEPROM.write(Tanaman3.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman3.Usia, UmurSekarang);
  EEPROM.write(Tanaman3.Panen, UmurPanen);

  split(dD);
  EEPROM.write(Tanaman4.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman4.Usia, UmurSekarang);
  EEPROM.write(Tanaman4.Panen, UmurPanen);

  split(dE);
  EEPROM.write(Tanaman5.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman5.Usia, UmurSekarang);
  EEPROM.write(Tanaman5.Panen, UmurPanen);

  split(dF);
  EEPROM.write(Tanaman6.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman6.Usia, UmurSekarang);
  EEPROM.write(Tanaman6.Panen, UmurPanen);

  split(dG);
  EEPROM.write(Tanaman7.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman7.Usia, UmurSekarang);
  EEPROM.write(Tanaman7.Panen, UmurPanen);

  split(dH);
  EEPROM.write(Tanaman8.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman8.Usia, UmurSekarang);
  EEPROM.write(Tanaman8.Panen, UmurPanen);
}

void TestEEPROM() {
  Serial.println("\nTanaman 1");
  Serial.println(EEPROM.read(Tanaman1.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman1.Usia));
  Serial.println(EEPROM.read(Tanaman1.Panen));
  Serial.println("\nTanaman 4");
  Serial.println(EEPROM.read(Tanaman4.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman4.Usia));
  Serial.println(EEPROM.read(Tanaman4.Panen));
  Serial.println("\nTanaman 6");
  Serial.println(EEPROM.read(Tanaman6.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman6.Usia));
  Serial.println(EEPROM.read(Tanaman6.Panen));
  Serial.println("\nTanaman 8");
  Serial.println(EEPROM.read(Tanaman8.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman8.Usia));
  Serial.println(EEPROM.read(Tanaman8.Panen));
  delay(1000);
}
