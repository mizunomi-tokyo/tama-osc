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


int TRIGGER = 0;
int SECOND = 0;
int BRIGHTNESS = 0;
int HUE = 0;
int SATURATION = 0;

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
    OSCMessage message;
    int size = udp.parsePacket();

    if (size > 0) {
        while (size--) {
        message.fill(udp.read());
      }
      if (!message.hasError()) {
        message.dispatch("/on", led_on);
        message.dispatch("/off", led_off);
        message.dispatch("/fadein", led_fadein);
        message.dispatch("/fadeout", led_fadeout);
        message.dispatch("/flash", flash);
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
