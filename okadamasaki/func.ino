//void temp_func(OSCMessage &msg) {
//}

void led_on(OSCMessage &msg) {
  TRIGGER = msg.getInt(0);
  BRIGHTNESS = msg.getInt(2);
  HUE = msg.getInt(3);
  SATURATION = msg.getInt(4);
  if(TRIGGER == 1){
    Serial.println("LED ON");
    for(int i = 1; i < NUM_LEDS; i++) {
//       let's set an led value
      leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
      FastLED.show();
    }
  }
}

void led_off(OSCMessage &msg) {
  TRIGGER = msg.getInt(0);
  if(TRIGGER == 1){
    Serial.println("LED OFF");
    for(int i = 1; i < NUM_LEDS; i++) {
      // let's set an led value
      BRIGHTNESS = 0;
      leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
      FastLED.show();
    }
  }
}

void led_fadein(OSCMessage &msg) {
  TRIGGER = msg.getInt(0);
  SECOND = msg.getFloat(1);
  int MAX_BRIGHTNESS = msg.getInt(2);
  HUE = msg.getInt(3);
  SATURATION = msg.getInt(4);
  if(TRIGGER == 1){
    Serial.println("LED FADEIN");
    while(BRIGHTNESS < MAX_BRIGHTNESS){
      for(int i = 1; i < NUM_LEDS; i++) {
        // let's set an led value
        leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
        FastLED.show();
        BRIGHTNESS = BRIGHTNESS + 1;
        FastLED.delay(SECOND * 1000 / MAX_BRIGHTNESS);
      }
    }
    for(int i = 1; i < NUM_LEDS; i++) {
      // let's set an led value
      BRIGHTNESS = MAX_BRIGHTNESS;
      leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
      FastLED.show();
    }
  }
}

void led_fadeout(OSCMessage &msg) {
  TRIGGER = msg.getInt(0);
  SECOND = msg.getFloat(1);
  int MAX_BRIGHTNESS = BRIGHTNESS;
  if(TRIGGER == 1){
    Serial.println("LED FADEOUT");
    while(BRIGHTNESS > 0){
      for(int i = 1; i < NUM_LEDS; i++) {
        // let's set an led value
        leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
        BRIGHTNESS = BRIGHTNESS - 1;
        FastLED.show();
        FastLED.delay(SECOND * 1000 / MAX_BRIGHTNESS);
      }
    }
    for(int i = 1; i < NUM_LEDS; i++) {
      // let's set an led value
      BRIGHTNESS = 0;
      leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
      FastLED.show();
    }
  }
}

void flash(OSCMessage &msg) {
  int BPM = msg.getInt(0);
  int COUNT = msg.getInt(1);
  BRIGHTNESS = msg.getInt(2);
  HUE = msg.getInt(3);
  SATURATION = msg.getInt(4);
  Serial.println("FLASH");
  for(int j = 0; j < COUNT; j++){
    Serial.println("LED ON");
    for(int i = 1; i < NUM_LEDS; i++) {
      // let's set an led value
      leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
      FastLED.show();
    }
    FastLED.delay(30000/BPM);
    Serial.println("LED OFF");
    for(int i = 1; i < NUM_LEDS; i++) {
      // let's set an led value
      leds[i] = CHSV(HUE, SATURATION, 0);
      FastLED.show();
    }
    FastLED.delay(30000/BPM);
  }
}
