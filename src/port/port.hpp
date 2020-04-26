#ifndef PORT_H
#define PORT_H

#include <map>
#include <ArduinoJson.h>

typedef struct Port { 
    String PID;
    String type;
    double value; 
} Port;
#endif