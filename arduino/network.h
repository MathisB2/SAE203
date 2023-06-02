#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>

using namespace std;

class Network
{
private:
    WiFiServer server;
    WiFiClient client;
public:
    Network();
    void connectTo(const char* ssid, const char* password, String serverIP);
    void createServer(const char* ssid, const char* password, int port);
    String getMessage();
    int clientConnected();
};

#endif // NETWORK_H
