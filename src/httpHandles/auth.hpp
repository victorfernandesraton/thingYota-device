
#include "HttpRequest.hpp"
#include "HttpResponse.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <vector>
#include <map>
#include <ArduinoJson.h>

namespace auth
{
    DynamicJsonDocument logonResponseSerialize(String jsonfly);
    DynamicJsonDocument login(String mac_addres);
} // authspace auth
