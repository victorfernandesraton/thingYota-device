
#include "HttpRequest.hpp"
#include "HttpResponse.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <vector>
#include <map>
#include <ArduinoJson.h>
#include "../port/port.hpp"

DynamicJsonDocument logonResponseSerialize(String jsonfly);
DynamicJsonDocument registerResponseSerialize(String jsonfly);
namespace auth
{

    DynamicJsonDocument login(String mac_addres);
    DynamicJsonDocument registaer(String mac_address, std::map<String, Port>);
} // authspace auth
