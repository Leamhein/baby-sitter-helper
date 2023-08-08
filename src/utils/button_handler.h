#include <Arduino.h>
#include <statuses.h>
#include <BLE_handler.h>

int buttonPin = D6;
int lastState = LOW;
int currentState;

void handleButtonPress()
{
    currentState = digitalRead(buttonPin);

    if (lastState == HIGH && currentState == LOW)
    {
        if (status_bus.get_status() == Passive)
        {
            Serial.println("send message");
            BLE_handler->sendMessage("HELLO WORLD");
        }

        if (status_bus.get_status() == Active)
        {
            status_bus.set_status(Passive);
            Serial.println("to passive");
        }
    }

    lastState = currentState;
}