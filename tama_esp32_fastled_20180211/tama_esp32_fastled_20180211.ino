/*
 *  This sketch sends random data over UDP on a ESP32 device
 *
 */
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <FastLED.h>

// WiFi network name and password:
const char * networkName = "elecom2g-bf3586";
const char * networkPswd = "1243665439571";

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

int HUE = 0;
int SATURATION = 0;
int BRIGHTNESS = 0;
#define MAX_BRIGHTNESS 200

void setup(){
  // Initilize hardware serial:
  Serial.begin(115200);

  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);
  
  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);
}

void loop(){
  //only send data when connected
  if(connected){
    OSCMessage bundle;
    int size = udp.parsePacket();

    if (size > 0) {
        while (size--) {
        bundle.fill(udp.read());
      }
      if (!bundle.hasError()) {
        bundle.dispatch("/2/push1", led_on);
        bundle.dispatch("/2/push2", led_off);
        bundle.dispatch("/2/push3", led_fadein);
        bundle.dispatch("/2/push4", led_fadeout);
        bundle.dispatch("/2/push12", change_color_random);
        bundle.dispatch("/2/push13", change_color_white);
        bundle.dispatch("/2/push14", change_color_red);
        bundle.dispatch("/2/push15", change_color_green);
        bundle.dispatch("/2/push16", change_color_blue);
        bundle.empty();
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
