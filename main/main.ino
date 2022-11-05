#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "ppp";                 // random for now
const char* password = "pailius12345678"; // random for now
const int device_id = 4;

const int relay = 19;

String serverName = "https://power-manager-api.herokuapp.com";
String get_state = "/devices/state/";
String post_data = "/devices/consumption/";
String response;


int state = 0;

void setup()
{
    pinMode(relay, OUTPUT);
    
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("Wifi authenticated");
    
    while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println(WiFi.localIP());

    Serial.println("Setup done");
}

void check_relay_state(int state){
  if (state){
     // if true (1), then appliance can work
    digitalWrite(relay, HIGH);
    }
  else{
    digitalWrite(relay, LOW);
      }
}

void loop()
{
    Serial.println("Smart-power-meter running...");

    check_relay_state(state);
    
    delay(1000);

  
}
