//void temp_func(OSCMessage &msg) {
//}

void led_on(OSCMessage &msg) {
  Serial.println("LED ON");
  for(int i = 1; i < NUM_LEDS; i++) {
    // let's set an led value
    BRIGHTNESS = MAX_BRIGHTNESS;
    leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
    FastLED.show();
  }
}

void led_off(OSCMessage &msg) {
  Serial.println("LED OFF");
  for(int i = 1; i < NUM_LEDS; i++) {
    // let's set an led value
    BRIGHTNESS = 0;
    leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
    FastLED.show();
  }
}

void led_fadein(OSCMessage &msg) {
  Serial.println("LED FADEIN");
  while(BRIGHTNESS < MAX_BRIGHTNESS){
    for(int i = 1; i < NUM_LEDS; i++) {
      // let's set an led value
      leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
      FastLED.show();
      BRIGHTNESS = BRIGHTNESS + 1;
      delay(1);
    }
  }
  for(int i = 1; i < NUM_LEDS; i++) {
    // let's set an led value
    BRIGHTNESS = MAX_BRIGHTNESS;
    leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
    FastLED.show();
  }
}

void led_fadeout(OSCMessage &msg) {
  Serial.println("LED FADEOUT");
  while(BRIGHTNESS > 0){
    for(int i = 1; i < NUM_LEDS; i++) {
      // let's set an led value
      leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
      BRIGHTNESS = BRIGHTNESS - 1;
      FastLED.show();
      delay(1);
    }
  }
  for(int i = 1; i < NUM_LEDS; i++) {
    // let's set an led value
    BRIGHTNESS = 0;
    leds[i] = CHSV(HUE, SATURATION, BRIGHTNESS);
    FastLED.show();
  }
}

void change_color_white(OSCMessage &msg) {
  Serial.println("GO WHITE");
  HUE = 0;
  SATURATION = 0;
}
void change_color_red(OSCMessage &msg) {
  Serial.println("GO RED");
  HUE = 0;
  SATURATION = 255;
}
void change_color_green(OSCMessage &msg) {
  Serial.println("GO GREEN");
  HUE = 85;
  SATURATION = 255;
}
void change_color_blue(OSCMessage &msg) {
  Serial.println("GO BLUE");
  HUE = 170;
  SATURATION = 255;
}
void change_color_random(OSCMessage &msg) {
  Serial.println("GO MAD");
  HUE = random(0,255);
  SATURATION = 255;
}
