
#include "HttpRequest.hpp"
#include "HttpResponse.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

using namespace std;


HttpRequest::HttpRequest(WiFiClient wifiClient, String host, u16_t port, String uri) {
    _wifiClient = wifiClient;
    _baseUrl = uri;
    _host= host;
    _port= port;
    _headers = "";
}

HttpRequest::HttpRequest(WiFiClient wifiClient, String host, u16_t port, String uri, String headers) {
    _wifiClient = wifiClient;
    _baseUrl = uri;
    _host= host;
    _port= port;
    _headers = headers;
}

HttpResponse HttpRequest::get(String url) {
    HTTPClient http;
    HttpResponse httpResult;
    if (http.begin(_host, _port, _baseUrl)) {
        if (http.GET()) {
            httpResult.responseCode = http.GET();
            httpResult.response = http.getString();
            httpResult.responseError = "";
         } else {
            httpResult.response = "Error: Server internal Errror";
            httpResult.responseCode = 500;
            httpResult.responseError = http.errorToString(httpResult.responseCode).c_str();   
         } 
    } else {
        httpResult.response = "Error: Not Found";
        httpResult.responseCode = 400;
        httpResult.responseError = "";
    }
    return httpResult;
}