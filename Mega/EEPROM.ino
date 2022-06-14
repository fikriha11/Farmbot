
/*
   DATA YG DI AMBIL
   Plant_id
   Umur
   Umur Panen
*/

String receiveData;
int nA, nB, nC, nD, nE, nF, nG, nH, nI, nJ, nK, nL, nM, nN, nO, nP, nQ, nR, nS, nT, nU;
String dA, dB, dC, dD, dE, dF, dG, dH, dI, dJ, dK, dL, dM, dN, dO, dP, dQ, dR, dS, dT;

/* SPLIt */
String SaveData[10];
String SplitData;
int StringData;

String DATAA = "A3,9,25B0,0,0C3,4,25D2,4,40E2,6,40F2,1,40G3,4,25H3,0,25I3,1,25J2,1,40K0,0,0L3,1,25M0,0,0N2,1,40O3,1,25P0,0,0Q2,1,40R2,1,40S1,1,20T3,1,25";


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

  Tanaman9.Usia = 25;
  Tanaman9.JenisTanaman = 26;
  Tanaman9.Panen = 27;

  Tanaman10.Usia = 28;
  Tanaman10.JenisTanaman = 29;
  Tanaman10.Panen = 30;

  Tanaman11.Usia = 31;
  Tanaman11.JenisTanaman = 32;
  Tanaman11.Panen = 33;

  Tanaman12.Usia = 34;
  Tanaman12.JenisTanaman = 35;
  Tanaman12.Panen = 36;

  Tanaman13.Usia = 37;
  Tanaman13.JenisTanaman = 38;
  Tanaman13.Panen = 39;

  Tanaman14.Usia = 40;
  Tanaman14.JenisTanaman = 41;
  Tanaman14.Panen = 41;

  Tanaman15.Usia = 43;
  Tanaman15.JenisTanaman = 44;
  Tanaman15.Panen = 45;

  Tanaman16.Usia = 46;
  Tanaman16.JenisTanaman = 47;
  Tanaman16.Panen = 48;

  Tanaman17.Usia = 49;
  Tanaman17.JenisTanaman = 50;
  Tanaman17.Panen = 51;

  Tanaman18.Usia = 52;
  Tanaman18.JenisTanaman = 53;
  Tanaman18.Panen = 54;

  Tanaman19.Usia = 55;
  Tanaman19.JenisTanaman = 56;
  Tanaman19.Panen = 57;

  Tanaman20.Usia = 58;
  Tanaman20.JenisTanaman = 59;
  Tanaman20.Panen = 60;

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
  nJ = Data.indexOf("J");
  nK = Data.indexOf("K");
  nL = Data.indexOf("L");

  nM = Data.indexOf("M");
  nN = Data.indexOf("N");
  nO = Data.indexOf("O");
  nP = Data.indexOf("P");

  nQ = Data.indexOf("Q");
  nR = Data.indexOf("R");
  nS = Data.indexOf("S");
  nT = Data.indexOf("T");

  dA = Data.substring(nA + 1, nB);
  dB = Data.substring(nB + 1, nC);
  dC = Data.substring(nC + 1, nD);
  dD = Data.substring(nD + 1, nE);

  dE = Data.substring(nE + 1, nF);
  dF = Data.substring(nF + 1, nG);
  dG = Data.substring(nG + 1, nH);
  dH = Data.substring(nH + 1, nI);

  dI = Data.substring(nI + 1, nJ);
  dJ = Data.substring(nJ + 1, nK);
  dK = Data.substring(nK + 1, nL);
  dL = Data.substring(nL + 1, nM);

  dM = Data.substring(nM + 1, nN);
  dN = Data.substring(nN + 1, nO);
  dO = Data.substring(nO + 1, nP);
  dP = Data.substring(nP + 1, nQ);

  dQ = Data.substring(nQ + 1, nR);
  dR = Data.substring(nR + 1, nS);
  dS = Data.substring(nS + 1, nT);
  dT = Data.substring(nT + 1, nU);

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

void coba() {
  parse(DATAA);
  SaveEEPROM();
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

  split(dI);
  EEPROM.write(Tanaman9.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman9.Usia, UmurSekarang);
  EEPROM.write(Tanaman9.Panen, UmurPanen);

  split(dJ);
  EEPROM.write(Tanaman10.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman10.Usia, UmurSekarang);
  EEPROM.write(Tanaman10.Panen, UmurPanen);

  split(dK);
  EEPROM.write(Tanaman11.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman11.Usia, UmurSekarang);
  EEPROM.write(Tanaman11.Panen, UmurPanen);

  split(dL);
  EEPROM.write(Tanaman12.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman12.Usia, UmurSekarang);
  EEPROM.write(Tanaman12.Panen, UmurPanen);

  split(dM);
  EEPROM.write(Tanaman13.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman13.Usia, UmurSekarang);
  EEPROM.write(Tanaman13.Panen, UmurPanen);

  split(dN);
  EEPROM.write(Tanaman14.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman14.Usia, UmurSekarang);
  EEPROM.write(Tanaman14.Panen, UmurPanen);

  split(dO);
  EEPROM.write(Tanaman15.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman15.Usia, UmurSekarang);
  EEPROM.write(Tanaman15.Panen, UmurPanen);

  split(dP);
  EEPROM.write(Tanaman16.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman16.Usia, UmurSekarang);
  EEPROM.write(Tanaman16.Panen, UmurPanen);

  split(dQ);
  EEPROM.write(Tanaman17.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman17.Usia, UmurSekarang);
  EEPROM.write(Tanaman17.Panen, UmurPanen);

  split(dR);
  EEPROM.write(Tanaman18.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman18.Usia, UmurSekarang);
  EEPROM.write(Tanaman18.Panen, UmurPanen);

  split(dS);
  EEPROM.write(Tanaman19.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman19.Usia, UmurSekarang);
  EEPROM.write(Tanaman19.Panen, UmurPanen);

  split(dT);
  EEPROM.write(Tanaman20.JenisTanaman, Plant_ID);
  EEPROM.write(Tanaman20.Usia, UmurSekarang);
  EEPROM.write(Tanaman20.Panen, UmurPanen);

}

void TestEEPROM() {
  Serial.println("\nTanaman 1");
  Serial.println(EEPROM.read(Tanaman1.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman1.Usia));
  Serial.println(EEPROM.read(Tanaman1.Panen));
  Serial.println("\nTanaman 2");
  Serial.println(EEPROM.read(Tanaman2.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman2.Usia));
  Serial.println(EEPROM.read(Tanaman2.Panen));
  Serial.println("\nTanaman 3");
  Serial.println(EEPROM.read(Tanaman3.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman3.Usia));
  Serial.println(EEPROM.read(Tanaman3.Panen));
  Serial.println("\nTanaman 4");
  Serial.println(EEPROM.read(Tanaman4.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman4.Usia));
  Serial.println(EEPROM.read(Tanaman4.Panen));

  Serial.println("\nTanaman 5");
  Serial.println(EEPROM.read(Tanaman5.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman5.Usia));
  Serial.println(EEPROM.read(Tanaman5.Panen));
  Serial.println("\nTanaman 6");
  Serial.println(EEPROM.read(Tanaman6.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman6.Usia));
  Serial.println(EEPROM.read(Tanaman6.Panen));
  Serial.println("\nTanaman 7");
  Serial.println(EEPROM.read(Tanaman7.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman7.Usia));
  Serial.println(EEPROM.read(Tanaman7.Panen));
  Serial.println("\nTanaman 8");
  Serial.println(EEPROM.read(Tanaman8.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman8.Usia));
  Serial.println(EEPROM.read(Tanaman8.Panen));

  Serial.println("\nTanaman 9");
  Serial.println(EEPROM.read(Tanaman9.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman9.Usia));
  Serial.println(EEPROM.read(Tanaman9.Panen));
  Serial.println("\nTanaman 10");
  Serial.println(EEPROM.read(Tanaman10.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman10.Usia));
  Serial.println(EEPROM.read(Tanaman10.Panen));
  Serial.println("\nTanaman 11");
  Serial.println(EEPROM.read(Tanaman11.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman11.Usia));
  Serial.println(EEPROM.read(Tanaman11.Panen));
  Serial.println("\nTanaman 12");
  Serial.println(EEPROM.read(Tanaman12.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman12.Usia));
  Serial.println(EEPROM.read(Tanaman12.Panen));

  Serial.println("\nTanaman 13");
  Serial.println(EEPROM.read(Tanaman13.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman13.Usia));
  Serial.println(EEPROM.read(Tanaman13.Panen));
  Serial.println("\nTanaman 14");
  Serial.println(EEPROM.read(Tanaman14.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman14.Usia));
  Serial.println(EEPROM.read(Tanaman14.Panen));
  Serial.println("\nTanaman 15");
  Serial.println(EEPROM.read(Tanaman15.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman15.Usia));
  Serial.println(EEPROM.read(Tanaman15.Panen));
  Serial.println("\nTanaman 16");
  Serial.println(EEPROM.read(Tanaman16.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman16.Usia));
  Serial.println(EEPROM.read(Tanaman16.Panen));

  Serial.println("\nTanaman 17");
  Serial.println(EEPROM.read(Tanaman17.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman17.Usia));
  Serial.println(EEPROM.read(Tanaman17.Panen));
  Serial.println("\nTanaman 18");
  Serial.println(EEPROM.read(Tanaman18.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman18.Usia));
  Serial.println(EEPROM.read(Tanaman18.Panen));
  Serial.println("\nTanaman 19");
  Serial.println(EEPROM.read(Tanaman19.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman19.Usia));
  Serial.println(EEPROM.read(Tanaman19.Panen));
  Serial.println("\nTanaman 20");
  Serial.println(EEPROM.read(Tanaman20.JenisTanaman));
  Serial.println(EEPROM.read(Tanaman20.Usia));
  Serial.println(EEPROM.read(Tanaman20.Panen));
  delay(1000);
}
