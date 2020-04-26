#include "HttpRequest.hpp"
#include "HttpResponse.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <vector>
#include <map>
#include <ArduinoJson.h>
#include "auth.hpp"
#include "../port/port.hpp"

const String apiDomain = "http://123.23.23.20";
const size_t capacity = 25000;
DynamicJsonDocument loginResponseSerialize(String jsonfly)
{
    DynamicJsonDocument doc(capacity);
    // Tratamento de json
    deserializeJson(doc, jsonfly);
    doc["res"] = true;
    return doc;
}
DynamicJsonDocument registerResponseSerialize(String jsonfly)
{
    DynamicJsonDocument doc(capacity);
    // Tratamento de json
    deserializeJson(doc, jsonfly);
    doc["res"] = true;
    return doc;
}
namespace auth
{
DynamicJsonDocument login(String mac_addres)
{
    const size_t capacity = JSON_OBJECT_SIZE(1);
    DynamicJsonDocument doc(capacity);

    doc["res"] = false;
    HttpRequest *authRequest = new HttpRequest(apiDomain, 8000, "/auth");
    authRequest->updateHeader("Content-Type", "application/json");
    HttpResponse response = authRequest->post("/device", "", "", "{\"mac_addres\":\"" + mac_addres + "\"}");
    Serial.println(response.response);
    if (response.responseCode == 200)
    {
        return loginResponseSerialize(response.response);
    }
    else
    {
        return doc;
    }
}
DynamicJsonDocument registaer(String mac_address, std::map<String, Port>) {
    const size_t capacity = JSON_OBJECT_SIZE(1);
    DynamicJsonDocument doc(capacity);

    doc["res"] = false;

    return doc;    
}
} // namespace auth
