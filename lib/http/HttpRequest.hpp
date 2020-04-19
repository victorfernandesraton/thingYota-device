
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "HttpResponse.h"

using namespace std;

struct HttpResponse
{
    String response;
    String responseError;
    int responseCode;

};

typedef HttpResponse HttpResponse;

class HttpRequest
{
private:
    String _baseUrl;
    String _headers;
    String _host;
    u16_t _port;

public:
    HttpRequest(String host, uint16_t port, String uri);
    HttpRequest(String host, uint16_t port, String uri, String headers);

    // Métodos get
    HttpResponse get(String url);
    HttpResponse get(String url, String query);
    HttpResponse get(String url, String query, String parans);

    // Métodos post
    HttpResponse post(String url);
    HttpResponse post(String url, String query);
    HttpResponse post(String url, String query, String parans);
    HttpResponse post(String url, String query, String parans, String body);

    // Métodos put
    HttpResponse put(String url);
    HttpResponse put(String url, String query);
    HttpResponse put(String url, String query, String parans);
    HttpResponse put(String url, String query, String parans, String body);

    // Métodos delete
    HttpResponse del(String url);
    HttpResponse del(String url, String query);
    HttpResponse del(String url, String query, String parans);

    //  mudança do header
    void updateHeader(String header);
};
// }

#endif