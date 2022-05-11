#include <Wire.h>
#include "TSL2561.h"

#define soilMoisture A8

const int AirValue = 620;
const int WaterValue = 310;

int soilMoistureValue =  0;
int soilmoisturepercent = 0;

int Moisture() {
  soilMoistureValue = analogRead(soilMoisture);
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  if (soilmoisturepercent > 100) {
    return 100;
  }
  else if (soilmoisturepercent < 0) {
    return 0;
  }
  else {
    return soilmoisturepercent;
  }
}


TSL2561 tsl(TSL2561_ADDR_FLOAT);

void configTSL() {

  if (tsl.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No sensor?");
    while (1);
  }
  tsl.setGain(TSL2561_GAIN_16X);
  tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS);
}

int Lumen() {
  uint16_t x = tsl.getLuminosity(TSL2561_VISIBLE);
  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir, full;
  ir = lum >> 16;
  full = lum & 0xFFFF;
  return tsl.calculateLux(full, ir);
}


int Temp() {
  return 45;
}

int Humid() {
  return 65;
}
