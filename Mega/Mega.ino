#include <EEPROM.h>
#include "RTClib.h"
#include <SimpleTimer.h>
RTC_DS3231 rtc;
SimpleTimer timer;

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


struct Tanaman {
  int Usia, JenisTanaman, Tanggal, Bulan, Tahun, Panen;
} Tanaman1, Tanaman2, Tanaman3, Tanaman4, Tanaman5, Tanaman6, Tanaman7, Tanaman8;

const char* nTanaman[] = {
  "Kangkung", "Selada", "Pak Coy", "Bayam", "Sawi Pagoda", "kailan", "Sawi", "Daun Bawang", "Daun Mint", "Seledri"
};
const char* nHari[] = {
  "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"
};
const char* nBulan[] = {
  "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"
};


long delay_Micros = 1800; // Set value
long currentMicros = 0; long previousMicros = 0;
String dataTerima;
String dataTrial;
int limit;
int Count = 0;
long nMM = 150;
int speedDelay = 200;

/** RTC **/

int tNow = 0; // Tanggal
int bNow = 0; // Bulan
int yNow = 0; // Tahun

int hNow = 0; // Jam
int mNow = 0; // Menit

struct SensorFlow {
  int Count;
} FlowA, FlowB;


bool Siram = false;
bool AirBaku = false;
bool AirNutrisi = false;
int Pump = 0;
bool RunningState = false;

const int ON = LOW;
const int OFF = HIGH;


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
  float cBulan = cTahun * 12.0;
  float cMinggu = cBulan * 4.0;

  return int(cMinggu);
}

void siram(int value) {
  FlowA.Count = 0;
  while (true) {
    if (FlowA.Count <= 200 and value != 0 ) {
      digitalWrite(PumpWater, ON);
    } else {
      delay(500);
      digitalWrite(PumpWater, OFF);
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
    execution();
  } else {
    Serial.println("STAND BY");
  }
}

void execution() {
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


void Reset() {
  FlowA.Count = 0;
}


void pulseCounterA() {
  FlowA.Count++;
}
