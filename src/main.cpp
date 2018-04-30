#include <Arduino.h>

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

// Connect to the WiFi
const char* ssid = "my_wifi_ssid";
const char* password = "my_wifi_password";

// MQTT broker address
const char* mqtt_server = "192.168.222.111";

//mqtt topics
const char * commandTopic = "barn/iot/antSwitchCommand";
const char * statusTopic = "barn/iot/antSwitchStatus";

// Globals
WiFiClient espClient;
PubSubClient client;
char msg[50];
char payStr[5];
unsigned long now;

//Outputs used to control switch relays - first pair is first switch, etc.
int outPins[8] = {D1, D2, D3, D4, D5, D6, D7, D8};

void setupWifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  if (length != 4) {
    Serial.println();
    Serial.println("Error: Message not 4 bytes in length, ignoring");
    return;
  }
  for (int i=0; i<(int)length; i++) {
    char receivedChar = (char)payload[i];
    Serial.print(receivedChar);
    //Parse 4 character string.  Each character is a 1 or 2 representing the switch state
    if ((receivedChar == '1') || (receivedChar == '2')) {
      int pindex = (i * 2) + (receivedChar == '2');
      digitalWrite(outPins[pindex], HIGH);
      delay(1000);
      digitalWrite(outPins[pindex], LOW);
    }
  }
  strncpy(payStr, (char *)payload, 4);
  payStr[4]=0;
  now = millis();
  sprintf(msg, "%lu: %s", now, payStr);
  Serial.println();
  Serial.print("Sending status message: ");
  Serial.println(msg);
  client.publish(statusTopic, msg);
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "antSwitch-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // ... and subscribe to topic
      client.subscribe(commandTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  //Set GPIO pins to output low
  for (int i=0; i<=7; ++i) {
    pinMode(outPins[i], OUTPUT);
    digitalWrite(outPins[i], LOW);
  }

  Serial.begin(9600);
  setupWifi();
  client.setClient(espClient);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
