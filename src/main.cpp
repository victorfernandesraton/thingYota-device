
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SocketIoClient.h>
#include "HttpRequest.hpp"
#include <vector>
#include <ArduinoJson.h>
#include "httpHandles/auth.hpp"


ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;
StaticJsonDocument<200> doc;

const String apiDomain = "http://123.23.23.20";
// const String macAddres = WiFi.macAddress;
// bool connect = false;

// eventos
void event(const char *payload, size_t length)
{
    Serial.printf("got message: %s\n", payload);
}

void teste(const char *payload, size_t length)
{
    Serial.println("Teste %s");
    Serial.printf("%s\n", payload);
    // emiter
    webSocket.emit("ok", "ok");
}


// void connectHandler(const char *payload, size_t length)
// {
//     connect = true;
// }
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

    webSocket.on("event", event);
    webSocket.on("teste", teste);
    // webSocket.on("connect", connectHandler);
    webSocket.begin("123.23.23.20/arduino", 8000);
    // use HTTP Basic Authorization this is optional remove if not needed
    // webSocket.setAuthorization("username", "password");
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
    
    DynamicJsonDocument guestAuthResponse = auth::guestToken();
    
    String guestToken = guestAuthResponse["data"]["token"];
    
    if (guestToken) {
       String token = auth::main(WiFi.macAddress(), guestToken);
       if(token) {
           connect = true;
       }
       
       while(connect) {
            Serial.println("Conectado");
            webSocket.loop();
            delay(200);
        }
    }

}
