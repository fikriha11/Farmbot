bool Button() {
  if (digitalRead(button) == LOW) {
    return true;
  } else {
    return false;
  }
}
