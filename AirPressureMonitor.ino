#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WifiCredentials.h"
ESP8266WebServer server(80);

const int PIN = A0;

void setup()
{
    Serial.begin(57600);

    pinMode(PIN, INPUT);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ...");

    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    { // Wait for the Wi-Fi to connect
        delay(1000);
        Serial.print(++i);
        Serial.print(' ');
    }

    Serial.println('\n');
    Serial.println("Connection established!");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer

    server.on("/", handle_root);
    server.onNotFound(handle_NotFound);

    server.begin();
}

void loop()
{
    server.handleClient();
}

int getPSI()
{
    int val = analogRead(A0);
    int pressure = map(val, 1024 / 10, 9 * 1024 / 10, 0, 146);
    if (pressure <= 10)
    {
        pressure = 0;
    }
    return pressure;
}

void handle_root()
{
    //Lazy way to make JSON. Really should not to this.

    String temp = "{\"uptime\": ";
    temp += millis();
    temp += ", \"psi\": ";
    temp += getPSI();
    temp += "}";
    server.send(200, "application/json", temp.c_str());
}

void handle_NotFound()
{
    server.send(404, "text/plain", "Not found");
}