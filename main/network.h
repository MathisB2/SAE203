#ifndef NETWORK_H
#define NETWORK_H
#include <WiFi.h>

class Network
{
private:
    WiFiServer server;
    WiFiClient client;
public:
    Network();
    void connectTo(const char* ssid, const char* password, const char* serverIP);
    void createServer(const char* ssid, const char* password, int port);
    void sendMessage(String message);
    String getMessage();
    int clientAvailable();
    int clientConnected();

    int getClientNumber();
};

#endif // NETWORK_H
