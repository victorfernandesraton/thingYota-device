
#include <vector>

#include "HttpRequest.hpp"

#include "httpHandles/auth.hpp"

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ArduinoJson.h>


ESP8266WiFiMulti WiFiMulti;
StaticJsonDocument<200> doc;

const String host = "https://ic-iot-unifacs-api-2.herokuapp.com/";
const char host_socket[] = "123.23.23.20";
const int port =  80;
const char path_socket[] = "/arduino?transport=websocket";
// const String macAddres = WiFi.macAddress;
// bool connect = false;

void setup()
{
    Serial.begin(9600);

    Serial.println();
    Serial.println();
    Serial.println();

    WiFi.begin("Maria Clara", "11010000");
    WiFiMulti.addAP("Maria Clara", "11010000");
    for (uint8_t t = 4; t > 0; t--)
    {
        Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
        Serial.flush();

        delay(1000);
    }


    while (WiFiMulti.run() != WL_CONNECTED)
    {
        delay(100);
    }
}

void loop() 
{
    bool connect = false;
    bool socketConnect = false;
    Port p1;
    p1.PID = 12;
    p1.type = "Teste";
    p1.value = 0;

    std::map<String, Port> ports;
    ports.insert(std::make_pair("12", p1));
    
    DynamicJsonDocument guestAuthResponse = auth::guestToken(port);
    
    String guestToken = guestAuthResponse["data"]["token"];
    
    if (guestToken) {
       String token = auth::main(WiFi.macAddress(), guestToken,port);
       if(token != "") {
           connect = true;
       }
        delay(200);

    //    while(connect) {
    //         Serial.println("Conectado");
    //     }
    }
}
