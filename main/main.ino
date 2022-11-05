#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ppp";                 // random for now
const char* password = "pailius12345678"; // random for now

String serverName = "";

void setup()
{

    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.println("Authenticated");
    
    while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println(WiFi.localIP());

    Serial.println("Setup done");
}

void loop()
{
    Serial.println("Scan start");

  
}
