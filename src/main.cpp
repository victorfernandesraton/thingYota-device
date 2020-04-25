
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SocketIoClient.h>
#include "HttpRequest.hpp"
#include <vector>


ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;
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

const String apiDomain = "http://123.23.23.20";

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
        // Serial.println(WiupdateHeaderFi.macAddress);
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
    
    HttpRequest *custonHttp = new HttpRequest(apiDomain, 8000, "/helth");
    custonHttp->updateHeader("Content-Type", "application/json");
    HttpRequest *postHttp = new HttpRequest(apiDomain, 8000, "/auth");
    postHttp->updateHeader("Content-Type", "application/json");
    
    HttpResponse resp; 
    HttpResponse respost;
    // resp = custonHttp->get("");
    respost = postHttp->post("/guest", "", "", "{\"api_key\":\"tPmAT5Ab3j7F9\"");
    // Serial.println(resp.response); 
    // Serial.println(resp.responseCode); 
    // Serial.println(resp.responseError); 
    
    Serial.println(respost.response); 
    Serial.println(respost.responseCode); 
    Serial.println(respost.responseError); 

    // webSocket.loop();
    // if (connect) 
    // {
    //     Serial.println("Conectado");
    // }
}
