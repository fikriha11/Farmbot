/*
   DATA YG DI AMBIL
   Plant_id
   Umur
*/


String Data = "A2,12B3,1C4,2D";
String Data1 = "A21,22,23,15B20,19,18C";


int nA, nB, nC, nD, nE, nF, nG, nH, nI;
String dA, dB, dC, dD, dE, dF, dG, dH, dI;

/* SPLIt */
String SaveData[10];
String SplitData;
int StringData;

/*
   Variable Temporary
*/

String Plant_ID;
String Umur;

/*
   Variable Temporary
*/


void setup() {
  Serial.begin(9600);
}

void loop() {
  SaveEEPROM();
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

  Plant_ID = Data.substring(0, i1);
  Umur = Data.substring(i1 + 1, i2);
}

void SaveEEPROM() {
  parse(Data);
  split(dA);
  Serial.println(Plant_ID + '\t' + Umur);
  split(dB);
  Serial.println(Plant_ID + '\t' + Umur);
  split(dC);
  Serial.println(Plant_ID + '\t' + Umur);
  delay(1000);
}
