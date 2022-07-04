/*
   OLD VERSION
*/

#include <EEPROM.h>
#include "RTClib.h"
#include <SimpleTimer.h>
#include <Servo.h>

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

Servo Servo1;
Servo Servo2;
RTC_DS3231 rtc;
SimpleTimer timer;

#define SwitchZ A1
#define SwitchX A2
#define SwitchY A3
#define SwitchL A4

#define SensorFlowA  3
#define button 17
#define Rotary_CHA 18
#define Rotary_CHB 19

/* Relay */
#define PumpWater 32
#define PumpFert 34
#define power 36

/* Stepper */
#define PulseY 12
#define DirY 11
#define PulseZ 10
#define DirZ 9
#define PulseX 8
#define DirX 7
#define PulseL 31
#define DirL 33


struct Tanaman {
  int Usia, JenisTanaman, Tanggal, Bulan, Tahun, Panen;
} Tanaman1, Tanaman2, Tanaman3, Tanaman4, Tanaman5, Tanaman6, Tanaman7, Tanaman8,
Tanaman9, Tanaman10, Tanaman11, Tanaman12, Tanaman13, Tanaman14, Tanaman15, Tanaman16,
Tanaman17, Tanaman18, Tanaman19, Tanaman20;

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
int Count = 5;
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

int CursorPos = 0;
bool Plantstate = false;
bool Flushstate = false;
bool ButtonState = false;

struct ENC
{
  volatile long int pulseCnt;
  long int lastpulse;
} Rotary;


int Takaran(int JenisTanaman, int Umur) {
  int Takar = 0;
  if (JenisTanaman >= 1 && JenisTanaman < 9 ) {
    if (Umur <= 7) {
      Takar = 1000; // 75 ml
    } else if (Umur > 7 && Umur <= 35) {
      Takar = 1300; // 100 ml
    } else {
      Takar = 1800; // 150 ml
    }
  }
  else {
    if (Umur <= 7) {
      Takar = 1000;  // 75 ml
    } else {
      Takar = 1300; // 100 ml
    }
  }
  return Takar;
}


int HitungUmur(int Tanggal, int Bulan, int Tahun) {

  DateTime now = rtc.now();
  int Tanam = Tanggal + (Bulan * 30 ) + (2022 * 365);  // Total tanggal Tanam

  tNow = now.day(), DEC; // Tanggal Sekarang
  bNow =  now.month(), DEC; // Bulan Sekarang
  yNow = now.year(), DEC; // Tahun Sekarang

  int Now = tNow + (bNow * 30) + ((yNow) * 365); // Total

  float cTahun = (Now - Tanam) / 365.0;
  float cBulan = cTahun * 12.0;
  float cMinggu = cBulan * 4.0;

  return int(cMinggu);
}

void siram(int value) {
  FlowA.Count = 0;
  while (true) {
    // Serial2.println(FlowA.Count);
    if (FlowA.Count <= value and value != 0 ) {
      digitalWrite(Pump, ON);
    } else {
      delay(500);
      digitalWrite(Pump, OFF);
      break;
    }
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
  } else if (hNow == 16 and mNow == 0) {
    Pump = PumpWater;
    return true;
  }
  return false;
}



void mainloop() {
  if (CheckJam()) {
    RunningState = true;
  } if (Button()) {
    RunningState = true;
    Pump = PumpFert;
  }

  if (RunningState) {
    digitalWrite(power, ON);
    SiramTanaman();
  }
}

void updateSensor() {
  if (!RunningState) {
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
}

void Lubangi(int x, int y, int l) {
  int sleep = 500;
  gotoY(y);
  delay(sleep);
  gotoX(x);
  delay(sleep);
  gotoZ(350);
  delay(sleep);
  gotoL(l);
}

void homeZL() {
  digitalWrite(DirL, LOW);
  digitalRead(SwitchL);
  do {
    digitalWrite(PulseL, HIGH);
    delayMicroseconds(2000);
    digitalWrite(PulseL, LOW);
    delayMicroseconds(2000);
  } while (digitalRead(SwitchL) == HIGH);

  digitalWrite(DirZ, HIGH);
  digitalRead(SwitchZ);

  do {
    digitalWrite(PulseZ, HIGH);
    delayMicroseconds(speedDelay);
    digitalWrite(PulseZ, LOW);
    delayMicroseconds(speedDelay);
  } while (digitalRead(SwitchZ) == HIGH);
}

void taruhPipa(int x, int y) {
  homeZL(); delay(500);
  gotoX(x); delay(500);
  gotoY(y); delay(500);
  servobuka(); delay(3000);
  servotutup(); delay(2000);
  gotoY(30);
  delay(500);
}

void ambilTanaman(int x) {
  int sleep = 500;
  gotoY(20);
  delay(sleep);
  gotoX(x);
  servobukatitik(); delay(1000);
  gotoY(-20); delay(1000);
  gotoZ(27); delay(1000);
  servotutup(); delay(2000);
}

void DiTanam(int x, int y, int l, int pos) {
  Lubangi(x, y, l);
  delay(500);
  homie();
  delay(500);
  ambilTanaman(pos);
  delay(500);
  Lubangi(x - pos, y, l);  // Put Tanaman
  taruhPipa(-(x - pos), -(y));
  delay(500);
  homie();
}

void Tanam() {
  switch (Count) {
    case 1 :
      DiTanam(47,  140, 13, 2);
      Count = 0;
      break;
    case 2 :
      DiTanam(125, 140, 13, 19);
      Count = 0;
      break;
    case 3 :
      DiTanam(203, 140, 13, 38);
      Count = 0;
      break;
    case 4 :
      DiTanam(281, 140, 13, 55);
      Count = 0;
      break;

    case 5 :
      DiTanam(47,  235, 13, 73);
      Count = 0;
      break;
    case 6 :
      DiTanam(125, 235, 13, 92);
      Count = 0;
      break;
    case 7 :
      DiTanam(203,  235, 13, 111);
      Count = 0;
      break;
    case 8 :
      DiTanam(281, 235, 13, 130);
      Count = 0;
      break;

    case 9 :
      DiTanam(47,  330, 13, 149);
      Count = 0;
      break;
    case 10 :
      DiTanam(125, 330, 13, 168);
      Count = 0;
      break;
    case 11 :
      DiTanam(203,  330, 13, 187);
      Count = 0;
      break;
    case 12 :
      DiTanam(281, 330, 13, 206);
      Count = 0;
      break;

    case 13 :
      DiTanam(47,  430, 13, 225);
      Count = 0;
      break;
    case 14 :
      DiTanam(125, 430, 13, 244);
      Count = 0;
      break;
    case 15 :
      DiTanam(203,  430, 13, 263);
      Count = 0;
      break;
    case 16 :
      DiTanam(281, 430, 13, 282);
      Count = 0;
      break;

    case 17 :
      DiTanam(47,  525, 13, 301);
      Count = 0;
      break;
    case 18 :
      DiTanam(125, 525, 13, 320);
      Count = 0;
      break;
    case 19 :
      DiTanam(203,  525, 13, 339);
      Count = 0;
      break;
    case 20 :
      DiTanam(281, 525, 13, 358);
      Count = 0;
      break;

    default :
      break;
  }
}

void SiramTanaman() {
  switch (Count) {
    case 0:
      homie();
      delay(500);
      siram(0);
      break;
    case 1 :
      gotoY(50);
      delay(500);
      gotoX(50);
      delay(500);
      Running(EEPROM.read(Tanaman1.JenisTanaman), EEPROM.read(Tanaman1.Usia), EEPROM.read(Tanaman1.Panen));
      break;
    case 2 :
      gotoX(160);
      delay(500);
      Running(EEPROM.read(Tanaman2.JenisTanaman), EEPROM.read(Tanaman2.Usia), EEPROM.read(Tanaman2.Panen));
      break;
    case 3 :
      gotoX(160);
      delay(500);
      Running(EEPROM.read(Tanaman3.JenisTanaman), EEPROM.read(Tanaman3.Usia), EEPROM.read(Tanaman3.Panen));
      break;
    case 4 :
      gotoX(190);
      delay(500);
      Running(EEPROM.read(Tanaman4.JenisTanaman), EEPROM.read(Tanaman4.Usia), EEPROM.read(Tanaman4.Panen));
      break;

    case 5 :
      gotoY(190);
      delay(500);
      Running(EEPROM.read(Tanaman5.JenisTanaman), EEPROM.read(Tanaman5.Usia), EEPROM.read(Tanaman5.Panen));
      break;
    case 6 :
      gotoX(-170);
      delay(500);
      Running(EEPROM.read(Tanaman6.JenisTanaman), EEPROM.read(Tanaman6.Usia), EEPROM.read(Tanaman6.Panen));
      break;
    case 7 :
      gotoX(-170);
      delay(500);
      Running(EEPROM.read(Tanaman7.JenisTanaman), EEPROM.read(Tanaman7.Usia), EEPROM.read(Tanaman7.Panen));
      break;
    case 8 :
      gotoX(-170);
      delay(500);
      Running(EEPROM.read(Tanaman8.JenisTanaman), EEPROM.read(Tanaman8.Usia), EEPROM.read(Tanaman8.Panen));
      break;


    case 9 :
      gotoY(190);
      delay(500);
      Running(EEPROM.read(Tanaman9.JenisTanaman), EEPROM.read(Tanaman9.Usia), EEPROM.read(Tanaman9.Panen));
      break;
    case 10 :
      gotoX(170);
      delay(500);
      Running(EEPROM.read(Tanaman10.JenisTanaman), EEPROM.read(Tanaman10.Usia), EEPROM.read(Tanaman10.Panen));
      break;
    case 11 :
      gotoX(170);
      delay(500);
      Running(EEPROM.read(Tanaman11.JenisTanaman), EEPROM.read(Tanaman11.Usia), EEPROM.read(Tanaman11.Panen));
      break;
    case 12 :
      gotoX(170);
      delay(500);
      Running(EEPROM.read(Tanaman12.JenisTanaman), EEPROM.read(Tanaman12.Usia), EEPROM.read(Tanaman12.Panen));
      break;

    case 13 :
      gotoY(190);
      delay(500);
      Running(EEPROM.read(Tanaman13.JenisTanaman), EEPROM.read(Tanaman13.Usia), EEPROM.read(Tanaman13.Panen));
      break;
    case 14 :
      gotoX(-170);
      delay(500);
      Running(EEPROM.read(Tanaman14.JenisTanaman), EEPROM.read(Tanaman14.Usia), EEPROM.read(Tanaman14.Panen));
      break;
    case 15 :
      gotoX(-170);
      delay(500);
      Running(EEPROM.read(Tanaman15.JenisTanaman), EEPROM.read(Tanaman15.Usia), EEPROM.read(Tanaman15.Panen));
      break;
    case 16 :
      gotoX(-170);
      delay(500);
      Running(EEPROM.read(Tanaman16.JenisTanaman), EEPROM.read(Tanaman16.Usia), EEPROM.read(Tanaman16.Panen));
      break;

    case 17 :
      gotoY(190);
      delay(500);
      Running(EEPROM.read(Tanaman17.JenisTanaman), EEPROM.read(Tanaman17.Usia), EEPROM.read(Tanaman17.Panen));
      break;
    case 18 :
      gotoX(170);
      delay(500);
      Running(EEPROM.read(Tanaman18.JenisTanaman), EEPROM.read(Tanaman18.Usia), EEPROM.read(Tanaman18.Panen));
      break;
    case 19 :
      gotoX(170);
      delay(500);
      Running(EEPROM.read(Tanaman19.JenisTanaman), EEPROM.read(Tanaman19.Usia), EEPROM.read(Tanaman19.Panen));
      break;
    case 20 :
      gotoX(170);
      delay(500);
      Running(EEPROM.read(Tanaman20.JenisTanaman), EEPROM.read(Tanaman20.Usia), EEPROM.read(Tanaman20.Panen));
      break;

    case 21:
      homie();
      Count = 0;
      digitalWrite  (power, OFF);
      RunningState = false;
      break;
  }
}


void Reset() {
  FlowA.Count = 0;
}


void pulseCounterA() {
  FlowA.Count++;
}
