#include <Arduino.h>
#include <statuses.h>
#include <BLE_handler.h>
#include <utils/actions.h>
#include <utils/button_handler.h>

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonLed, OUTPUT);
  pinMode(notificationLed, OUTPUT);
  BLE_handler->setup();
}

void loop()
{
  handleButtonPress();
  if (status_bus.get_status() == Disconnected)
  {
    disconnect_status_blink();
  }

  if (status_bus.get_status() == Active)
  {
    active_status_blink();
  }
}
