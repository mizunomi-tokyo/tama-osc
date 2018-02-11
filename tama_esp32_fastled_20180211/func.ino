void led_on(OSCMessage &msg) {
  Serial.println("LED ON");
  for(int i = 1; i < NUM_LEDS; i++) {
    // let's set an led value
    leds[i] = CHSV(0,0,255);
    FastLED.show();
  }
}

void led_off(OSCMessage &msg) {
  Serial.println("LED OFF");
  for(int i = 1; i < NUM_LEDS; i++) {
    // let's set an led value
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

void led_fadein(OSCMessage &msg) {
  Serial.println("LED FADEIN");
  int v = 0;
  while(v < 255){
    for(int i = 1; i < NUM_LEDS; i++) {
      // let's set an led value
      leds[i] = CHSV(0,0,v);
      FastLED.show();
      v = v + 1;
      delay(1);
    }
  }
  for(int i = 1; i < NUM_LEDS; i++) {
    // let's set an led value
    leds[i] = CHSV(0,0,255);
    FastLED.show();
  }
}

void led_fadeout(OSCMessage &msg) {
  Serial.println("LED FADEOUT");
  int v = 255;
  while(v > 0){
    for(int i = 1; i < NUM_LEDS; i++) {
      // let's set an led value
      leds[i] = CHSV(0,0,v);
      v = v - 1;
      FastLED.show();
      delay(1);
    }
  }
  for(int i = 1; i < NUM_LEDS; i++) {
    // let's set an led value
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}
