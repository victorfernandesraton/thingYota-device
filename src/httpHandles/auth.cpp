#include "HttpRequest.hpp"
#include "HttpResponse.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <vector>
#include <map>
#include <ArduinoJson.h>
#include "auth.hpp"
#include "../port/port.hpp"

// const String apiDomain = "http://123.23.23.20:8000";
const String apiDomain = "http://ic-iot-unifacs-api-2.herokuapp.com";
const size_t capacity = 10*JSON_ARRAY_SIZE(10) + 10*JSON_OBJECT_SIZE(10) + JSON_OBJECT_SIZE(10) + 1000;
DynamicJsonDocument loginResponseSerialize(String jsonfly)
{
    DynamicJsonDocument doc(capacity);
    // Tratamento de json
    deserializeJson(doc, jsonfly);
    return doc;
}
DynamicJsonDocument registerResponseSerialize(String jsonfly)
{
    DynamicJsonDocument doc(capacity);
    // Tratamento de json
    deserializeJson(doc, jsonfly);
    return doc;
}
DynamicJsonDocument guestResponseSerialize(String jsonfly)
{
    DynamicJsonDocument doc(capacity);
    // Tratamento de json
    deserializeJson(doc, jsonfly);
    doc["res"] = true;
    return doc;
}


namespace auth
{
DynamicJsonDocument login(String mac_addres, int Port)
{
    const size_t capacity = JSON_OBJECT_SIZE(1);
    DynamicJsonDocument doc(capacity);

    HttpRequest *authRequest = new HttpRequest(apiDomain, Port, "/auth");
    authRequest->updateHeader("Content-Type", "application/json");
    HttpResponse response = authRequest->post("/device", "", "", "{\"mac_addres\":\"" + mac_addres + "\"}");
    Serial.println(response.response);
    if (response.responseCode == 200)
    {
        return loginResponseSerialize(response.response);
    }
    else
    {
        doc["data"]["token"]= "error";
        doc["res"] = false;
        return doc;
    }
}
DynamicJsonDocument registaer(String mac_address, String token, int Port)
{

    const size_t capacity = JSON_OBJECT_SIZE(1);
    DynamicJsonDocument doc(capacity);

    doc["res"] = false;

    HttpRequest *request = new HttpRequest(apiDomain, Port, "/singup");
    request->updateHeader("Content-Type", "application/json");
    request->updateHeader("Authorization", "Bearer "+token);
    String object = "{\"name\":\"esp-teste\",\"mac_addres\":\""+mac_address+"\",\"type\":\"esp-8266\"}";
    HttpResponse response = request->post("/device", "", "",object);
    Serial.println(response.response);
    if(response.responseCode == 200) {
        return registerResponseSerialize(response.response);
    } else {
        return doc;
    }
}
DynamicJsonDocument guestToken(int Port) {
    const size_t capacity = JSON_OBJECT_SIZE(1);
    DynamicJsonDocument doc(capacity);
    doc["res"] = false;

    HttpRequest *request = new HttpRequest(apiDomain, Port, "/auth");
    request->updateHeader("Content-Type", "application/json");
    HttpResponse response = request->post("/guest", "", "","" );
    Serial.println(response.response);
    if(response.responseCode == 200) {
        return guestResponseSerialize(response.response);
    } else {
        return doc;
    }    
}

String main(String mac_address, String guestToken, int Port) {
    DynamicJsonDocument resAuth =auth::login(mac_address, Port);
    String tokenAuth = resAuth["data"]["token"];
    bool isLogged = resAuth["res"];
    Serial.println(tokenAuth+ isLogged);
    if (!isLogged) {
        DynamicJsonDocument registerResponse = auth::registaer(mac_address, guestToken, Port);
        return resAuth["data"]["token"];        
    } else {
        return tokenAuth;
    }    
}
} // namespace auth
