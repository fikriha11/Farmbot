#include <EEPROM.h>
#include "RTClib.h"
RTC_DS3231 rtc;

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

/** RTC **/

int tNow = 0; // Tanggal
int bNow = 0; // Bulan
int yNow = 0; // Tahun

int hNow = 0; // Jam
int mNow = 0; // Menit

struct SensorFlow {
  int Count;
} FlowA, FlowB;

struct Tanaman {
  int Usia, JenisTanaman, Tanggal, Bulan, Tahun, Panen;
} Tanaman1, Tanaman2, Tanaman3, Tanaman4, Tanaman5, Tanaman6, Tanaman7, Tanaman8;

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
bool AirBaku = false;
bool AirNutrisi = false;
int Pump = 0;
bool RunningState = false;

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
  Tanaman2.Tahun = 11;
  Tanaman2.Panen = 12;

  Tanaman3.Usia = 13;
  Tanaman3.JenisTanaman = 14;
  Tanaman3.Tanggal = 15;
  Tanaman3.Bulan = 16;
  Tanaman3.Tahun = 17;
  Tanaman3.Panen = 18;

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

const int ON = LOW;
const int OFF = HIGH;

void setup() {

  Serial.begin(115200);
  rtc.begin();
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

  rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

}

void loop() {
  // trialGUI();
  // trialFlow();
  // testRelay();
  // trialSwitch();
  // trialXYZ();
  // Running();
  
  Serial.println(HitungUmur(21, 7, 2021));
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


int HitungUmur(int Tanggal, int Bulan, int Tahun) {
  DateTime now = rtc.now();
  int Tanam = Tanggal + (Bulan * 30 ) + (Tahun * 365);  // Total tanggal Tanam

  tNow = now.day(), DEC; // Tanggal Sekarang
  bNow =  now.month(), DEC; // Bulan Sekarang
  yNow = now.year(), DEC; // Tahun Sekarang

  tNow = 21; // Tanggal Sekarang
  bNow = 4; // Bulan Sekarang
  yNow = 2022; // Tahun Sekarang

  int Now = tNow + (bNow * 30) + (yNow * 365);  // Total

  float cTahun = (Now - Tanam) / 365.0;
  int cBulan = cTahun * 12;
  int cMinggu = cBulan * 4;

  return cMinggu;
}

void siram(int value) {
  FlowA.Count = 0;
  while (true) {
    if (FlowA.Count <= 200 ) {
      digitalWrite(Pump, ON);
    } else {
      delay(500);
      digitalWrite(Pump, OFF);
      break;
    }
    Serial.println(FlowA.Count);
  }
  Count++;  // Pindah Step
}

bool CheckTanaman(int JenisTanaman) {
  if (JenisTanaman != 0) {
    Siram = true;
  } else {
    Siram = false;
  }
  return Siram;
}

void Running(int JenisTanaman, int UmurTanaman, int UmurPanen) {
  if (CheckTanaman(JenisTanaman)) {
    if (UmurTanaman < UmurPanen) {
      int ml = Takaran(JenisTanaman, UmurTanaman);
      siram(ml);
    }
  } else {
    Count++; // Pindah Step
  }
}

bool CheckJam() {
  DateTime now = rtc.now();
  hNow = now.hour(), DEC;
  mNow = now.minute(), DEC;

  if (hNow == 7 and mNow == 0 ) {
    Pump = PumpFert;
    return true;
  } else if (hNow == 15 and mNow == 0 ) {
    Pump = PumpWater;
    return true;
  } else {
    return false;
  }
}


void mainloop() {
  // Check
  if (CheckJam()) {
    RunningState = true;
  } else {
    RunningState = false;
  }

  if (RunningState) {
    excution();
  } else {
    Serial.println("STAND BY");
  }
}

void excution() {
  switch (Count) {
    case 0:
      Serial.println("Preparation");
      homie();
      delay(500);
      break;
    case 1 :
      Serial.println("Tanaman 1A");
      gotoY(50);
      delay(500);
      gotoX(50);
      delay(500);
      Running(EEPROM.read(Tanaman1.JenisTanaman), HitungUmur(EEPROM.read(Tanaman1.Tanggal), EEPROM.read(Tanaman1.Bulan), EEPROM.read(Tanaman1.Tahun)), EEPROM.read(Tanaman1.Panen));
      break;
    case 2 :
      Serial.println("Tanaman 2A");
      gotoX(160);
      delay(500);
      Running(EEPROM.read(Tanaman2.JenisTanaman), HitungUmur(EEPROM.read(Tanaman2.Tanggal), EEPROM.read(Tanaman2.Bulan), EEPROM.read(Tanaman2.Tahun)), EEPROM.read(Tanaman2.Panen));
      break;
    case 3 :
      Serial.println("Tanaman 3A");
      gotoX(160);
      delay(500);
      Running(EEPROM.read(Tanaman3.JenisTanaman), HitungUmur(EEPROM.read(Tanaman3.Tanggal), EEPROM.read(Tanaman3.Bulan), EEPROM.read(Tanaman3.Tahun)), EEPROM.read(Tanaman3.Panen));
      break;
    case 4 :
      Serial.println("Tanaman 4A");
      gotoX(160);
      delay(500);
      Running(EEPROM.read(Tanaman4.JenisTanaman), HitungUmur(EEPROM.read(Tanaman4.Tanggal), EEPROM.read(Tanaman4.Bulan), EEPROM.read(Tanaman4.Tahun)), EEPROM.read(Tanaman4.Panen));
      break;
    case 5 :
      Serial.println("Tanaman 1B");
      gotoY(140);
      delay(500);
      Running(EEPROM.read(Tanaman5.JenisTanaman), HitungUmur(EEPROM.read(Tanaman5.Tanggal), EEPROM.read(Tanaman5.Bulan), EEPROM.read(Tanaman5.Tahun)), EEPROM.read(Tanaman5.Panen));
      break;
    case 6 :
      Serial.println("Tanaman 2B");
      gotoX(-160);
      delay(500);
      Running(EEPROM.read(Tanaman6.JenisTanaman), HitungUmur(EEPROM.read(Tanaman6.Tanggal), EEPROM.read(Tanaman6.Bulan), EEPROM.read(Tanaman6.Tahun)), EEPROM.read(Tanaman6.Panen));
      break;
    case 7 :
      Serial.println("Tanaman 3B");
      gotoX(-160);
      delay(500);
      Running(EEPROM.read(Tanaman7.JenisTanaman), HitungUmur(EEPROM.read(Tanaman7.Tanggal), EEPROM.read(Tanaman7.Bulan), EEPROM.read(Tanaman7.Tahun)), EEPROM.read(Tanaman7.Panen));
      break;
    case 8 :
      Serial.println("Tanaman 4B");
      gotoX(-160);
      delay(500);
      Running(EEPROM.read(Tanaman8.JenisTanaman), HitungUmur(EEPROM.read(Tanaman8.Tanggal), EEPROM.read(Tanaman8.Bulan), EEPROM.read(Tanaman8.Tahun)), EEPROM.read(Tanaman8.Panen));
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
