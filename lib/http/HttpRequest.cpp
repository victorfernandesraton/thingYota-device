
#include "HttpRequest.hpp"
#include "HttpResponse.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <vector>
#include <map>
#include <ArduinoJson.h>

HttpRequest::HttpRequest(String host, u16_t port, String uri)
{
    _baseUrl = uri;
    _host = host;
    _port = port;
    _headers.insert(std::make_pair("Content-Type", "plain/text"));
}

HttpRequest::HttpRequest(String host, u16_t port, String uri, std::map<String, String> headers)
{
    _baseUrl = uri;
    _host = host;
    _port = port;
    _headers = headers;
}

HttpResponse HttpRequest::get(String url)
{
    HTTPClient http;
    HttpResponse httpResult;
    Serial.println("REQUEST :[GET] ::" + _host + _port + _baseUrl + url);
    http.begin(_host + ":" + _port + _baseUrl + url);
    if (_headers.size() > 0)
    {
        for (auto it = _headers.begin(); it != _headers.end(); it++)
            http.addHeader(it->first, it->second);
    }
    if (http.GET() > 0)
    {

        httpResult.responseCode = http.GET();
        httpResult.response = http.getString();
        httpResult.responseError = "";
    }
    else
    {
        httpResult.response = "Error: Server internal Errror";
        httpResult.responseCode = 500;
        httpResult.responseError = http.errorToString(httpResult.responseCode).c_str();
    }
    http.end();
    return httpResult;
}

HttpResponse HttpRequest::get(String url, String query)
{

    HTTPClient http;
    HttpResponse httpResult;
    Serial.println("REQUEST :[GET] ::" + _host + _port + _baseUrl + url + query);
    http.begin(_host + ":" + _port + _baseUrl + url + query);
    if (http.GET() > 0)
    {

        httpResult.responseCode = http.GET();
        httpResult.response = http.getString();
        httpResult.responseError = "";
    }
    else
    {
        httpResult.response = "Error: Server internal Errror";
        httpResult.responseCode = 500;
        httpResult.responseError = http.errorToString(httpResult.responseCode).c_str();
    }
    http.end();
    return httpResult;
}

HttpResponse HttpRequest::get(String url, String query, String parans)
{
    HTTPClient http;
    HttpResponse httpResult;
    Serial.println("REQUEST :[GET] ::" + _host + _port + _baseUrl + url + query + parans);
    http.begin(_host + ":" + _port + _baseUrl + url + query + "?" + parans);

    if (http.GET())
    {
        httpResult.responseCode = http.GET();
        httpResult.response = http.getString();
        httpResult.responseError = "";
    }
    else
    {
        httpResult.response = "Error: Server internal Errror";
        httpResult.responseCode = 500;
        httpResult.responseError = http.errorToString(httpResult.responseCode).c_str();
    }

    http.end();
    return httpResult;
}

HttpResponse HttpRequest::post(String url)
{
    HTTPClient http;
    HttpResponse httpResult;

    Serial.println("Not Implemented");
    httpResult.response = "Error: Not Found";
    httpResult.responseCode = 400;
    httpResult.responseError = "";

    return httpResult;
}
HttpResponse HttpRequest::post(String url, String query)
{
    HTTPClient http;
    HttpResponse httpResult;

    Serial.println("Not Implemented");
    httpResult.response = "Error: Not Found";
    httpResult.responseCode = 400;
    httpResult.responseError = "";
    return httpResult;
}
HttpResponse HttpRequest::post(String url, String query, String parans)
{
    HTTPClient http;
    HttpResponse httpResult;

    Serial.println("Not Implemented");
    httpResult.response = "Error: Not Found";
    httpResult.responseCode = 400;
    httpResult.responseError = "";
    return httpResult;
}
HttpResponse HttpRequest::post(String url, String query, String parans, String body)
{

    HTTPClient http;
    HttpResponse httpResult;
    http.begin(_host + _baseUrl + url + query + "?" + parans);
    std::map <String , String>::iterator itr;
    if (_headers.size() > 0) {
        for (itr = _headers.begin(); itr != _headers.end(); ++itr)
        {
            http.addHeader(itr->first, itr->second);
        }
    }
    Serial.println("REQUEST :[POST] ::" + _host + ":" + _port +"/"+ _baseUrl +"/"+ url + query + parans);
    Serial.println(body);
    httpResult.responseCode = http.POST(body);
    if (httpResult.responseCode > 0) {
        httpResult.response = http.getString();
        httpResult.responseError = "";  
    }
    else
    {
        httpResult.response = "Error: Server internal Errror + "+ http.getString() + http.errorToString(httpResult.responseCode);
        httpResult.responseCode = 500;
        httpResult.responseError = http.errorToString(httpResult.responseCode).c_str();
    }

    http.end();
    return httpResult;
}

// Métodos put
HttpResponse HttpRequest::put(String url)
{
    HTTPClient http;
    HttpResponse httpResult;

    Serial.println("Not Implemented");
    httpResult.response = "Error: Not Found";
    httpResult.responseCode = 400;
    httpResult.responseError = "";
    return httpResult;
}
HttpResponse HttpRequest::put(String url, String query)
{
    HTTPClient http;
    HttpResponse httpResult;

    Serial.println("Not Implemented");
    httpResult.response = "Error: Not Found";
    httpResult.responseCode = 400;
    httpResult.responseError = "";
    return httpResult;
}
HttpResponse HttpRequest::put(String url, String query, String parans)
{
    HTTPClient http;
    HttpResponse httpResult;

    Serial.println("Not Implemented");
    httpResult.response = "Error: Not Found";
    httpResult.responseCode = 400;
    httpResult.responseError = "";
    return httpResult;
}
HttpResponse HttpRequest::put(String url, String query, String parans, String body)
{
    HTTPClient http;
    HttpResponse httpResult;

    Serial.println("Not Implemented");
    httpResult.response = "Error: Not Found";
    httpResult.responseCode = 400;
    httpResult.responseError = "";
    return httpResult;
}

// Métodos delete
HttpResponse HttpRequest::del(String url)
{
    HTTPClient http;
    HttpResponse httpResult;

    Serial.println("Not Implemented");
    httpResult.response = "Error: Not Found";
    httpResult.responseCode = 400;
    httpResult.responseError = "";
    return httpResult;
}
HttpResponse HttpRequest::del(String url, String query)
{
    HTTPClient http;
    HttpResponse httpResult;

    Serial.println("Not Implemented");
    httpResult.response = "Error: Not Found";
    httpResult.responseCode = 400;
    httpResult.responseError = "";
    return httpResult;
}
HttpResponse HttpRequest::del(String url, String query, String parans)
{
    HTTPClient http;
    HttpResponse httpResult;

    Serial.println("Not Implemented");
    httpResult.response = "Error: Not Found";
    httpResult.responseCode = 400;
    httpResult.responseError = "";
    return httpResult;
}


void HttpRequest::updateHeader(String key, String value)
{
    if (_headers.find(key) != _headers.end())
    {
        _headers[key] = value;
    }
    else
    {
        _headers.insert(std::make_pair(key, value));
    }
}