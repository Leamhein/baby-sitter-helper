#include <Arduino.h>
#include <statuses.h>
#include <BLE_handler.h>
#include <utils/actions.h>
#include <utils/button_handler.h>

void setup()
{
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonLed, OUTPUT);
  pinMode(notificationLed, OUTPUT);
  BLE_handler->setup();
}

void loop()
{
  handleButtonPress();
  Statuses status = status_bus.get_status();

  Serial.println(status);

  if (status == Disconnected)
  {
    disconnect_status_blink();
  }

  if (status == Active)
  {
    active_status_blink();
  }

  if (status == Passive)
  {
    turn_off_notification_led();
  }
}
