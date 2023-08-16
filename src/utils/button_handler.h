#include <Arduino.h>
#include <statuses.h>
#include <communication_handler.h>

int buttonPin = D6;
int lastState = LOW;
int currentState;

void handleButtonPress()
{
    currentState = digitalRead(buttonPin);

    if (lastState == HIGH && currentState == LOW)
    Serial.println("Press");
    {
        if (status_bus.get_status() == Passive)
        {
            Communication_handler->sendMessage(21);
        }

        if (status_bus.get_status() == Active)
        {
            status_bus.set_status(Passive);
        }
    }

    lastState = currentState;
}