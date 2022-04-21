#include "RTClib.h"
RTC_DS3231 rtc;
char dataHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
String hari;
int tanggal, bulan, tahun, jam, menit, detik;
float suhu;

void setup () {
  Serial.begin(9600);
  rtc.begin();

  if (! rtc.begin()) {
    Serial.println("RTC Not Found");
    Serial.flush();
    abort();
  }

  //Atur Waktu
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop () {
  DateTime now = rtc.now();
  hari    = dataHari[now.dayOfTheWeek()];
  tanggal = now.day(), DEC;
  bulan   = now.month(), DEC;
  tahun   = now.year(), DEC;
  jam     = now.hour(), DEC;
  menit   = now.minute(), DEC;
  detik   = now.second(), DEC;
  suhu    = rtc.getTemperature();

  Serial.println(String() + hari + ", " + tanggal + "-" + bulan + "-" + tahun);
  Serial.println(String() + jam + ":" + menit + ":" + detik);
  Serial.println(String() + "Suhu: " + suhu + " C");
  Serial.println();

  delay(1000);
}
