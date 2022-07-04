bool Button() {
  if (digitalRead(button) == LOW) {
    return true;
  } else {
    return false;
  }
}

int LimitRotary() {
  int limit = 60;
  if (Rotary.pulseCnt > limit) {
    Rotary.pulseCnt = limit;
  } if (Rotary.pulseCnt < 0) {
    Rotary.pulseCnt = 0;
  }
  return Rotary.pulseCnt;
}


void Rotary_INTT_A()
{
  if (digitalRead(Rotary_CHA) == HIGH)
  {
    if (digitalRead(Rotary_CHB) == LOW)
    {
      Rotary.pulseCnt++;
    }
    else
    {
      Rotary.pulseCnt--;
    }
  }
  else
  {
    if (digitalRead(Rotary_CHB) == HIGH)
    {
      Rotary.pulseCnt++;
    }
    else
    {
      Rotary.pulseCnt--;
    }
  }

  if (Rotary.pulseCnt > 255) {
    Rotary.pulseCnt = 255;
  } if (Rotary.pulseCnt < 0) {
    Rotary.pulseCnt = 0;
  }
}

void Rotary_INTT_B()
{
  if (digitalRead(Rotary_CHA) == HIGH)
  {
    if (digitalRead(Rotary_CHB) == HIGH)
    {
      Rotary.pulseCnt++;
    }
    else
    {
      Rotary.pulseCnt--;
    }
  }
  else
  {
    if (digitalRead(Rotary_CHB) == LOW)
    {
      Rotary.pulseCnt++;
    }
    else
    {
      Rotary.pulseCnt--;
    }
  }

  if (Rotary.pulseCnt > 255) {
    Rotary.pulseCnt = 255;
  } if (Rotary.pulseCnt < 0) {
    Rotary.pulseCnt = 0;
  }
}
