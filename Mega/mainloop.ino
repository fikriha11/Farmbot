void setup() {

  Wire.begin();
  Serial.begin(9600);
  rtc.begin();
  INISIALISASI();

  /*
    if (! rtc.begin()) {
      Serial.println("RTC Not Found");
      Serial.flush();
      abort();
    }
  */

  configTSL();

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

  /* SET RTC */
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  /* SCHEDULE */
  timer.setInterval(3000, updateSensor);

}


void loop() {
  ReceiveData();
  timer.run();
  mainloop();

  // TestEEPROM();
  
  // execution();
  // trialXYZ();
  // trialRelay();
  // trialRTC ();
}
