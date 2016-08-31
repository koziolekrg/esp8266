#include <ESP8266WiFi.h>

const char* ssid = "ESP8266";
const char* password = "test8266";

const int ledPin = 2;
WiFiServer server(1337);

void printWiFiStatus();

void setup(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(ledPin, OUTPUT);

  server.begin();
}

void loop(void) {


  if (WiFi.status() != WL_CONNECTED) {
    while (WiFi.status() != WL_CONNECTED) {
      Serial.println("Try to connect");
      delay(500);
    }
    printWiFiStatus();
  }

  WiFiClient client = server.available();

 if (client) {
    
    Serial.println("Client connected.");
    
    while (client.connected()) {  
      
      if (client.available()) {
        
        String command = client.readStringUntil('\r');
        Serial.println(command);

        if (command.indexOf("on")!= -1) {
          digitalWrite(ledPin, HIGH);
          Serial.println("LED ON");
        }
        else if (command.indexOf("off")!= -1) { 
          digitalWrite(ledPin, LOW);
          Serial.println("LED OFF");
        }
        else {
          Serial.println("Invalid request");
        }
        client.flush();     
      }
    }
  }

void printWiFiStatus() {
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
