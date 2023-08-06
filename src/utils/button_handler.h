#include <Arduino.h>
#include <statuses.h>

int buttonPin = D6;
int lastState = LOW;
int currentState;

void handleButtonPress()
{
    currentState = digitalRead(buttonPin);

    if (lastState == HIGH && currentState == LOW)
        if (status_bus.get_status() == Passive)
            status_bus.set_status(Active);
        if (status_bus.get_status() == Active)
            status_bus.set_status(Passive);

    lastState = currentState;
}