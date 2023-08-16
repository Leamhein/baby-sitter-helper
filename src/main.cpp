#include <Arduino.h>
#include <statuses.h>
#include <utils/actions.h>
#include <utils/button_handler.h>
#include <communication_handler.h>
#include <WiFi.h>
#include "ESPNowW.h"
#include <constants.h>

void setup()
{
  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonLed, OUTPUT);
  pinMode(notificationLed, OUTPUT);

  Communication_handler->setup();

}

void loop()
{
  handleButtonPress();
  Statuses status = status_bus.get_status();

  if (status == Disconnected)
  {
    Serial.println("Disconnected");
    disconnect_status_blink();
    Communication_handler->reconnect();
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
