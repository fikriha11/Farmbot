
/*
   DATA YG DI AMBIL
   Plant_id
   Umur
   Umur Panen
*/


String Data1 = "A2,12B3,1C4,2D";
String Data2 = "A21,22,23,15B20,19,18C";

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
  Tanaman1.Tanggal = 3;
  Tanaman1.Bulan = 4;
  Tanaman1.Tahun = 5;
  Tanaman1.Panen = 6;

  Tanaman2.Usia = 7;
  Tanaman2.JenisTanaman = 8;
  Tanaman2.Tanggal = 9;
  Tanaman2.Bulan = 10;
  Tanaman2.Tahun = 10;
  Tanaman2.Panen = 12;

  Tanaman3.Usia = 13;
  Tanaman3.JenisTanaman = 14;
  Tanaman3.Tanggal = 15;
  Tanaman3.Bulan = 16;
  Tanaman3.Tahun = 17;
  Tanaman3.Panen = 10;

  Tanaman4.Usia = 19;
  Tanaman4.JenisTanaman = 20;
  Tanaman4.Tanggal = 21;
  Tanaman4.Bulan = 22;
  Tanaman4.Tahun = 23;
  Tanaman4.Panen = 24;

  Tanaman5.Usia = 25;
  Tanaman5.JenisTanaman = 26;
  Tanaman5.Tanggal = 27;
  Tanaman5.Bulan = 28;
  Tanaman5.Tahun = 29;
  Tanaman5.Panen = 30;

  Tanaman6.Usia = 31;
  Tanaman6.JenisTanaman = 32;
  Tanaman6.Tanggal = 33;
  Tanaman6.Bulan = 34;
  Tanaman6.Tahun = 35;
  Tanaman6.Panen = 36;

  Tanaman7.Usia = 37;
  Tanaman7.JenisTanaman = 38;
  Tanaman7.Tanggal = 39;
  Tanaman7.Bulan = 40;
  Tanaman7.Tahun = 41;
  Tanaman7.Panen = 42;

  Tanaman8.Usia = 43;
  Tanaman8.JenisTanaman = 44;
  Tanaman8.Tanggal = 45;
  Tanaman8.Bulan = 46;
  Tanaman8.Tahun = 47;
  Tanaman8.Panen = 48;
}

void Setting_EEPROM() {

  /* TANAMAN 1 */
  EEPROM.write(Tanaman1.Usia, 1);
  EEPROM.write(Tanaman1.JenisTanaman, 1);
  EEPROM.write(Tanaman1.Tanggal, 10);
  EEPROM.write(Tanaman1.Bulan, 5);
  EEPROM.write(Tanaman1.Tahun, 22);
  EEPROM.write(Tanaman1.Panen, 5);

  /* TANAMAN 2 */
  EEPROM.write(Tanaman2.Usia, 1);
  EEPROM.write(Tanaman2.JenisTanaman, 1);
  EEPROM.write(Tanaman2.Tanggal, 10);
  EEPROM.write(Tanaman2.Bulan, 5);
  EEPROM.write(Tanaman2.Tahun, 22);
  EEPROM.write(Tanaman2.Panen, 5);

  /* TANAMAN 3 */
  EEPROM.write(Tanaman3.Usia, 1);
  EEPROM.write(Tanaman3.JenisTanaman, 1);
  EEPROM.write(Tanaman3.Tanggal, 10);
  EEPROM.write(Tanaman3.Bulan, 5);
  EEPROM.write(Tanaman3.Tahun, 22);
  EEPROM.write(Tanaman3.Panen, 5);

  /* TANAMAN 4 */
  EEPROM.write(Tanaman4.Usia, 1);
  EEPROM.write(Tanaman4.JenisTanaman, 1);
  EEPROM.write(Tanaman4.Tanggal, 10);
  EEPROM.write(Tanaman4.Bulan, 5);
  EEPROM.write(Tanaman4.Tahun, 22);
  EEPROM.write(Tanaman4.Panen, 5);

  /* TANAMAN 5 */
  EEPROM.write(Tanaman5.Usia, 1);
  EEPROM.write(Tanaman5.JenisTanaman, 1);
  EEPROM.write(Tanaman5.Tanggal, 10);
  EEPROM.write(Tanaman5.Bulan, 5);
  EEPROM.write(Tanaman5.Tahun, 22);
  EEPROM.write(Tanaman5.Panen, 5);

  /* TANAMAN 6 */
  EEPROM.write(Tanaman6.Usia, 1);
  EEPROM.write(Tanaman6.JenisTanaman, 1);
  EEPROM.write(Tanaman6.Tanggal, 10);
  EEPROM.write(Tanaman6.Bulan, 5);
  EEPROM.write(Tanaman6.Tahun, 22);
  EEPROM.write(Tanaman6.Panen, 5);

  /* TANAMAN 7 */
  EEPROM.write(Tanaman7.Usia, 1);
  EEPROM.write(Tanaman7.JenisTanaman, 1);
  EEPROM.write(Tanaman7.Tanggal, 10);
  EEPROM.write(Tanaman7.Bulan, 5);
  EEPROM.write(Tanaman7.Tahun, 22);
  EEPROM.write(Tanaman7.Panen, 5);

  /* TANAMAN 8 */
  EEPROM.write(Tanaman8.Usia, 1);
  EEPROM.write(Tanaman8.JenisTanaman, 1);
  EEPROM.write(Tanaman8.Tanggal, 10);
  EEPROM.write(Tanaman8.Bulan, 5);
  EEPROM.write(Tanaman8.Tahun, 22);
  EEPROM.write(Tanaman8.Panen, 5);

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

void ReceiveData(){
  while(Serial.available()){
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

  split(dI);
  EEPROM.write(Tanaman8.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman8.Usia, UmurSekarang);
  EEPROM.write(Tanaman8.Panen, UmurPanen);
}

void TestEEPROM(){
  Serial.println(EEPROM.read(Tanaman8.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman8.Usia));
  Serial.println(EEPROM.read(Tanaman8.Panen));
  delay(1000);
}
