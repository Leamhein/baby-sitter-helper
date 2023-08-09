#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <statuses.h>
#ifndef BLEHANDLER_H
#define BLEHANDLER_H

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "8a7a1720-79ad-4fc0-9643-face13fcc309"
#define CHARACTERISTIC_UUID "8c6d2876-54da-4220-bc56-5d087770e63f"

class ServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        Serial.print("Connected");
        status_bus.set_status(Passive);
    };

    void onDisconnect(BLEServer *pServer)
    {
        status_bus.set_status(Disconnected);
        pServer->getAdvertising()->start();
    }
};

class CharacteristicCallbacks : public BLECharacteristicCallbacks
{
    void onNotify()
    {
        status_bus.set_status(Active);
    }
};

class BLEHandler
{
    BLECharacteristic * Characteristic;

public:
    void setup();
    void notify();
    void sendMessage(std::string);
};

void BLEHandler::setup()
{
    BLEDevice::init("BabySitterServer");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_NOTIFY |
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_READ);

    pServer->setCallbacks(new ServerCallbacks());
    pCharacteristic->setCallbacks(new CharacteristicCallbacks());
    pService->start();

    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();

    Characteristic = pCharacteristic;
};

void BLEHandler::notify()
{
    Characteristic->notify();
}

void BLEHandler::sendMessage(std::string message)
{
    Characteristic->setValue(message);
    Characteristic->notify();
}

extern BLEHandler* BLE_handler = new BLEHandler();

#endif /* BLEHANDLER_H */