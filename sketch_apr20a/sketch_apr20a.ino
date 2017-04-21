/*
 *  
 */

#include <ESP8266WiFi.h>

const char* ssid     = "Wifi SSID";
const char* password = "WIFI PASSWORD";
const char* host = "api.pushingbox.com"; //http://api.pushingbox.com/pushingbox?devid=vBCC8E7598B28D70
const char* pushingbox = "api.pushingbox.com/pushingbox?devid=vBCC8E7598B28D70";
int status = WL_IDLE_STATUS;                     // the Wifi radio's status

const int LEFTBURNER = 0;                       // the number of the Burner Light Input pin

// variables will change:
int LEFTBURNERstate = 0;                        // a boolean variable for reading the PIRstate status
int value = 0;

void setup() {
// Initialize the BUILTIN_LED pin as an output
  pinMode(BUILTIN_LED, OUTPUT);
// Initialize GPIO 0 pin as an input:
  pinMode(LEFTBURNER,INPUT);
  
  Serial.begin(115200);
  delay(10);

// We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

// print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  // One time 45 second delay to allow PIR to "stabalize"
// Blinks GPIO0 LED slowly then quickly to show progress
Serial.println("Waiting to calibrate PIR");
digitalWrite(BUILTIN_LED, HIGH);
delay(5000);
digitalWrite(BUILTIN_LED, LOW);
}

void loop() {
  
  ++value;

  LEFTBURNERstate = digitalRead(LEFTBURNER);          //read the state of the PIR value
  
// We now create a URI for the request
  String url = "/pushingbox?devid=vBCC8E7598B28D70";

// check if the Left Burner Indicator Light is on
// if it is, the LEFTBURNERstate is HIGH and print "BURNER ON" along with changing LED:
  if (PIRstate == HIGH) {
    Serial.println("Motion Detected");
// turn LED on:
    digitalWrite(BUILTIN_LED, LOW);
    
  WiFiClient client;
  const int httpPort = 80;  
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed.");
    Serial.println("Waiting to resolve connection.");
    return;
  }
  
    Serial.print("connecting to ");
    Serial.println(host);
    Serial.print("Requesting URL: ");
    Serial.println(url);
// This will send the HTTP request to the server
    client.println("GET /pushingbox?devid=vBCC8E7598B28D70 HTTP/1.1");
    client.println("Host: api.pushingbox.com");
    client.println("Connection: close");
    client.println();
    //delay(10);
  //Serial.println("closing connection");
  //Serial.println("");
  //Since LEFTBURNERstate is high wait 10 seconds to avoid repeatedly requesting push
  delay(10000);   
  }
  else{
  digitalWrite(BUILTIN_LED, HIGH);
  }
}
