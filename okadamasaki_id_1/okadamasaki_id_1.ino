/*
 *  mizunomi.tokyo <843@mizunomi.tokyo>
 *  Copyright (C) 2018 Kazumi Egawa <arnerican.f0otboy@gmail.com>
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <FastLED.h>

// WiFi network name and password:
const char * networkName = "elecom2g-egapyon-1";
const char * networkPswd = "egaegapyonpyon";

//IP address to send UDP data to:
// either use the ip address of the server or 
// a network broadcast address
const char * udpAddress = "192.168.1.255";  //not need for reciever
const int udpPort = 7000;

//Are we currently connected?
boolean connected = false;

//The udp library class
WiFiUDP udp;

// How many leds in your strip?
#define NUM_LEDS 5
#define DATA_PIN 13
CRGBArray<NUM_LEDS> leds;
int TRIGGER = 0;
int SECOND = 0;
int BRIGHTNESS = 100;
int HUE = 0;
int SATURATION = 255;

//color shows ball's ID
//
// THIS BALL'S ID IS 0
//
const int ID = 1;
int ONOLE = ID * 25;

void setup(){
  // Initilize hardware serial:
  Serial.begin(115200);

  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);
  
  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);
}

void loop(){
  if(!connected){
    leds[3] = CHSV(ONOLE, 255, 50);
    FastLED.show();
    FastLED.delay(2000);
    leds[3] = CHSV(0,0,0);
    FastLED.show();
  }
  else{
    OSCMessage message;
    int size = udp.parsePacket();

    if (size > 0) {
        while (size--) {
        message.fill(udp.read());
      }
      if (!message.hasError()) {
        message.dispatch("/1/on", led_on);
        message.dispatch("/1/off", led_off);
        message.dispatch("/1/fadein", led_fadein);
        message.dispatch("/1/fadeout", led_fadeout);
        message.dispatch("/1/flash", flash);
        message.dispatch("/all/on", led_on);
        message.dispatch("/all/off", led_off);
        message.dispatch("/all/fadein", led_fadein);
        message.dispatch("/all/fadeout", led_fadeout);
        message.dispatch("/all/flash", flash);
        message.empty();
      }
    }
  }
}

void connectToWiFi(const char * ssid, const char * pwd){
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);
  
  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          //When connected set
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());
          //initializes the UDP state
          //This initializes the transfer buffer
          udp.begin(WiFi.localIP(),udpPort);
          connected = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;
    }
}
