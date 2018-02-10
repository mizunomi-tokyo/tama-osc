/*---------------------------------------------------------------------------------------------
  Open Sound Control (OSC) library for the ESP8266
  Example for receiving open sound control (OSC) bundles on the ESP8266
  Send integers '0' or '1' to the address "/led" to turn on/off the built-in LED of the esp8266.
  This example code is in the public domain.
--------------------------------------------------------------------------------------------- */
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

const char* ssid = "pr500m-99506d-1";
const char* pass = "5ab9378744565";

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
const IPAddress outIp(192,168,1,150);        // remote IP (not needed for receive)
const unsigned int outPort = 9999;          // remote port (not needed for receive)
const unsigned int localPort = 7000;        // local port to listen for UDP packets (here's where we send the packets)


OSCErrorCode error;

unsigned int ledState = HIGH;              // LOW means led is *on*

void setup() {
  pinMode(4, OUTPUT);
  digitalWrite(4, ledState);    // turn *on* led

  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());

}


void led(OSCMessage &msg) {
  
  ledState = msg.getInt(0);
  digitalWrite(4, ledState);
//  Serial.print("/led: ");
//  Serial.println(ledState);
}

void loop() {
  OSCMessage bundle;
  int size = Udp.parsePacket();

  if (size > 0) {
//    Serial.println("unpi");
    while (size--) {
      bundle.fill(Udp.read());
//      Serial.println("pippi-------");
    }
    if (!bundle.hasError()) {
      bundle.dispatch("/led", led, 0);
//      Serial.println("olympas!!!!!");
      bundle.empty();
    } else {
      error = bundle.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}
