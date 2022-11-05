#include <WiFi.h>
#include <HTTPClient.h>



const char* ssid = "ppp";                 // random for now
const char* password = "pailius12345678"; // random for now
const int device_id = 4;

const int relay = 19;
const int led = 26;

unsigned long timer = 5000; // 5 seconds
unsigned long last_time = 0;

String server_name = "https://power-manager-api.herokuapp.com";
String get_state = "/devices/state/4";
String post_data = "https://power-manager-api.herokuapp.com/devices/consumption/";
String payload;

int state = 0;
int int_payload;

int consumption_value = 5;

void setup()
{
    pinMode(relay, OUTPUT);
    pinMode(led, OUTPUT);
    
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

void check_relay_state(String state){
  if (state == "1"){
     // if true (1), then appliance can work
    digitalWrite(relay, HIGH);
    digitalWrite(led, HIGH);
    Serial.println("relay HIGH");
    }
  else{
    digitalWrite(relay, LOW);
    digitalWrite(led, LOW);
    Serial.println("relay LOW");
      }
}

void loop()
{
    Serial.println("Smart-power-meter running...");
    
    if ((millis() - last_time) > timer){
      if (WiFi.status() == WL_CONNECTED){
        HTTPClient http;
        String full_get_state = server_name + get_state;
        http.begin(full_get_state.c_str());
        int httpResponseCode = http.GET();
          if (httpResponseCode == 200){
//            int unit_state = httpGETReques/t(full_get_state);
              String payload = http.getString();
//              check_relay_state(payload);/
              delay(50);
              Serial.println(payload);
              if (payload.equals("\"1\"")){
                Serial.println("Relay HIGH");
                digitalWrite(relay, HIGH);
                digitalWrite(led, HIGH);
              }
              if (payload.equals("\"0\"")){
                Serial.println("Relay LOW");
                digitalWrite(relay, LOW);
                digitalWrite(led, LOW);
              }
              delay(50);
              Serial.println(httpResponseCode);
          }
        
//        int httpResponseCode = http.POST("{\"device_id\":4, \"consumption\":" + consumption_value + "}");
//        Serial.println(httpResponseCode);
        http.end();
        
        http.begin(post_data.c_str());
        String json = "{\"device_id\": 4, \"consumption\": " + String(consumption_value) + "}";
        Serial.println(json);//
        httpResponseCode = http.POST(json);
        Serial.println(httpResponseCode);
        
      }else{
        Serial.println("Wifi disconnected");
      }
      
      last_time = millis();
    }

   
    
    delay(5000);//

  
}
