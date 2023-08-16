#include <WiFi.h>
#include "ESPNowW.h"
#include <constants.h>
#include <statuses.h>
#ifndef COMMUNICATIONHANDLER_H
#define COMMUNICATIONHANDLER_H

uint8_t broadcastAddress[] = BOARD_1_MAC_UINT8;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    if (status != ESP_OK)
    {
        status_bus.set_status(Disconnected);
    }
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    status_bus.set_status(Active);
}

class CommunicationHandler
{
public:
    void setup();
    void reconnect();
    void sendMessage(uint8_t message);
};

void CommunicationHandler::setup()
{
    Serial.println("ESP setup begin");
    WiFi.mode(WIFI_MODE_STA);
    WiFi.disconnect();
    ESPNow.init();
    ESPNow.reg_send_cb(OnDataSent);
    ESPNow.reg_recv_cb(OnDataRecv);
    reconnect();
}

void CommunicationHandler::reconnect()
{
    Serial.println("reconnecting");

    if (ESPNow.add_peer(broadcastAddress) != ESP_OK)
    {
        status_bus.set_status(Disconnected);
    }
    else
    {
        status_bus.set_status(Passive);
    }
}

void CommunicationHandler::sendMessage(uint8_t message)
{
    Serial.println("Sending message");
    ESPNow.send_message(broadcastAddress, &message, 1);
}

extern CommunicationHandler *Communication_handler = new CommunicationHandler();

#endif