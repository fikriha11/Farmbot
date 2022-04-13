#include <EEPROM.h>

#define PumpWater 32
#define PumpFert 34
#define SwitchZ A1
#define SwitchX A2
#define SwitchY A3
#define SensorFlowA  3

/* Stepper */
#define PulseY 12
#define DirY 11
#define PulseZ 10
#define DirZ 9
#define PulseX 8
#define DirX 7


long delay_Micros = 1800; // Set value
long currentMicros = 0; long previousMicros = 0;
String dataTerima;
String dataTrial;
int limit;
int Count = 0;
long nMM = 150;
int speedDelay = 300;


struct SensorFlow {
  int Count;
} FlowA, FlowB;

struct Tanaman {
  int Usia, JenisTanaman, Tanggal, Bulan, Tahun;
} Tanaman1, Tanaman2, Tanaman3, Tanaman4, Tanaman5, Tanaman6;

const char* nTanaman[] = {
  "Kangkung", "Selada", "Pak Coy", "Bayam", "Sawi Pagoda", "kailan", "Sawi", "Daun Mint", "Daun Bawang", "Seledri"
};
const char* nHari[] = {
  "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"
};
const char* nBulan[] = {
  "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"
};

bool Siram = false;

void INISIALISASI() {

  /** Addres EEPRM **/

  Tanaman1.Usia = 1;
  Tanaman1.JenisTanaman = 2;
  Tanaman1.Tanggal = 3;
  Tanaman1.Bulan = 4;
  Tanaman1.Tahun = 5;

  Tanaman2.Usia = 6;
  Tanaman2.JenisTanaman = 7;
  Tanaman2.Tanggal = 8;
  Tanaman2.Bulan = 9;
  Tanaman2.Tahun = 10;

  Tanaman3.Usia = 11;
  Tanaman3.JenisTanaman = 12;
  Tanaman3.Tanggal = 13;
  Tanaman3.Bulan = 14;
  Tanaman3.Tahun = 15;

  Tanaman4.Usia = 16;
  Tanaman4.JenisTanaman = 17;
  Tanaman4.Tanggal = 18;
  Tanaman4.Bulan = 19;
  Tanaman4.Tahun = 20;

  Tanaman5.Usia = 21;
  Tanaman5.JenisTanaman = 22;
  Tanaman5.Tanggal = 23;
  Tanaman5.Bulan = 24;
  Tanaman5.Tahun = 25;

}

const int ON = LOW;
const int OFF = HIGH;

void setup() {

  Serial.begin(9600);
  INISIALISASI();

  pinMode(PumpWater, OUTPUT);
  pinMode(PumpFert, OUTPUT);
  pinMode(SensorFlowA, INPUT);
  pinMode(SwitchZ, INPUT_PULLUP);
  pinMode(SwitchX, INPUT_PULLUP);
  pinMode(SwitchY, INPUT_PULLUP);

  pinMode(PulseX, OUTPUT);
  pinMode(DirX, OUTPUT);
  pinMode(PulseY, OUTPUT);
  pinMode(DirY, OUTPUT);
  pinMode(PulseZ, OUTPUT);
  pinMode(DirZ, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(SensorFlowA), pulseCounterA, CHANGE);
  digitalWrite(DirX, LOW);
  digitalWrite(DirY, LOW);
  digitalWrite(DirZ, LOW);
  digitalWrite(PumpWater, OFF);
  digitalWrite(PumpFert, OFF);

  Serial.println("STAND BY");
}

void loop() {
  trialGUI();
  // trialFlow();
  // testRelay();
  // trialSwitch();
  // trialXYZ();
  // eksekusiOK2();
  // Running();
}

bool CheckTanaman(int JenisTanaman) {
  if (JenisTanaman != 0) {
    Siram = true;
  } else {
    Siram = false;
  }
  return Siram;
}

int Takaran(int JenisTanaman, int Umur) {
  int Takar = 0;
  if (JenisTanaman >= 1 && JenisTanaman < 9 ) {
    if (Umur < 1) {
      Takar = 75;
    } else if (Umur >= 1 && Umur <= 5) {
      Takar = 100;
    } else {
      Takar = 150;
    }
  }

  else {
    if (Umur < 1) {
      Takar = 75;
    } else {
      Takar = 100;
    }
  }

  return Takar;
}


int HitungUmur(int Tanggal, int Bulan) {
  int Tanam = Tanggal + (Bulan * 30 );  // Total
  int tNow = 7;  // Tanggal Sekarang
  int bNow = 4;  // Bulan Sekarang
  int Now = tNow + (bNow * 30);  // Total
  float cBulan = abs(Now - Tanam) / 30;
  float cMinggu = cBulan * 4;
  return cMinggu;
}


void siram(int value) {
  FlowA.Count = 0;
  while (true) {
    if (FlowA.Count <= 200 ) {
      digitalWrite(PumpWater, ON);
    } else {
      delay(500);
      digitalWrite(PumpWater, OFF);
      break;
    }
    Serial.println(FlowA.Count);
  }
  Count++;
}

void Running(int JenisTanaman, int UmurTanaman, int UmurPanen) {
  if (CheckTanaman(JenisTanaman)) {
    if (UmurTanaman < UmurPanen) {
      int ml = Takaran(JenisTanaman, UmurTanaman);
      siram(ml);
    }
  }
}


void MainLoop() {
  switch (Count) {
    case 0:
      Serial.println("Preparation");
      homie();
      delay(500);
      siram(100);
      break;
    case 1 :
      Serial.println("Tanaman 1A");
      gotoY(50);
      delay(500);
      gotoX(50);
      delay(500);
      siram(100);
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
      siram(100);
      break;
    case 4 :
      Serial.println("Tanaman 4A");
      gotoX(160);
      delay(500);
      siram(100);
      break;
    case 5 :
      Serial.println("Tanaman 1B");
      gotoY(140);
      delay(500);
      siram(100);
      break;
    case 6 :
      Serial.println("Tanaman 2B");
      gotoX(-160);
      delay(500);
      siram(100);
      break;
    case 7 :
      Serial.println("Tanaman 3B");
      gotoX(-160);
      delay(500);
      siram(100);
      break;
    case 8 :
      Serial.println("Tanaman 4B");
      gotoX(-160);
      delay(500);
      siram(100);
      break;
    case 9:
      homie();
      Count = 10;
      break;
  }
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

void Reset() {
  FlowA.Count = 0;
}




void eksekusiOK2() {

  // Preparation
  Serial.println("Preparation");
  homie();
  delay(500);
  siram(100);

  // Tanaman 1A
  Serial.println("Tanaman 1A");
  gotoY(50);
  delay(500);
  gotoX(50);
  delay(500);
  siram(100);

  // Tanaman 2A
  Serial.println("Tanaman 2A");
  gotoX(160);
  delay(500);
  siram(100);

  // Tanaman 3A
  Serial.println("Tanaman 3A");

  gotoX(160);
  delay(500);
  siram(100);

  // Tanaman 4A
  Serial.println("Tanaman 4A");
  gotoX(160);
  delay(500);
  siram(100);

  // Tanaman 1B
  Serial.println("Tanaman 1B");
  gotoY(140);
  delay(500);
  siram(100);

  // Tanaman 2B
  Serial.println("Tanaman 2B");
  gotoX(-160);
  delay(500);
  siram(100);


  // Tanaman 3B
  Serial.println("Tanaman 3B");
  gotoX(-160);
  delay(500);
  siram(100);

  // Tanaman 4B
  Serial.println("Tanaman 4B");
  gotoX(-160);
  delay(500);
  siram(100);

  Serial.println("HOME");
  homie();
}


void homie() {
  Serial.println("home: X");
  digitalWrite(DirX, HIGH);
  digitalRead(SwitchX);
  do {
    digitalWrite(PulseX, HIGH);
    delayMicroseconds(200); //Set Value
    digitalWrite(PulseX, LOW);
    delayMicroseconds(200); //Set Value
  } while (digitalRead(SwitchX) == HIGH);

  Serial.println("home: Y");
  digitalWrite(DirY, HIGH);
  digitalRead(SwitchY);
  do {
    digitalWrite(PulseY, HIGH);
    delayMicroseconds(200); //Set Value
    digitalWrite(PulseY, LOW);
    delayMicroseconds(200); //Set Value
  } while (digitalRead(SwitchY) == HIGH);

  //  Serial.println("home: Z");
  //  digitalWrite(DirZ, HIGH);
  //  digitalRead(SwitchZ);

  //  do {
  //    digitalWrite(PulseZ, HIGH);
  //    delayMicroseconds(200); //Set Value
  //    digitalWrite(PulseZ, LOW);
  //    delayMicroseconds(200); //Set Value
  //  } while (digitalRead(SwitchZ) == HIGH);
}


void gotoX(long eX) {
  Serial.print("Xe--> "); Serial.println(eX);
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
  Serial.print("Y --> "); Serial.println(Ye);
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
  Serial.print("Z --> "); Serial.println(Ze);
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

void trialFlow() {
  Serial.println(FlowA.Count);
}

void trialGUI() {
  for (int i = 1; i <= 10; i++) {
    Serial.println("A" + String(i) + "B32C80D5832E70F");
    delay(2000);
  }
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

void testRelay() {
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
    Serial.println("OFF");
    digitalWrite(PumpWater, OFF);
    digitalWrite(PumpFert, OFF);
  }

  Serial.println(FlowA.Count);
}

void pulseCounterA() {
  FlowA.Count++;
}
