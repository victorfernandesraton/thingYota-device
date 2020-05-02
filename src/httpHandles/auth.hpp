
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
    // That function make login in api and return result
    DynamicJsonDocument login(String mac_addres);
    // That function make singup in platform
    DynamicJsonDocument registaer(String mac_address, String token, std::map<String, Port> port);
    // Tgat function returns guest token user in basix auth and login
    DynamicJsonDocument guestToken();
} // authspace auth
