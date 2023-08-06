#include <Arduino.h>
#include <utils/BLE_setup.h>
#include <statuses.h>
#include <utils/actions.h>

void setup()
{
  pinMode(buttonLed, OUTPUT);
  pinMode(notificationLed, OUTPUT);
  BLESetup();
}

void loop()
{
  Serial.println(status_bus.get_status());

  if (status_bus.get_status() == Disconnected)
  {
    Serial.println("Dis");
    disconnect_status_blink();
  }

  if (status_bus.get_status() == Active)
  {
    Serial.println("Act");
    active_status_blink();
  }

  if (status_bus.get_status() == Passive)
  {
    Serial.println("Pas");
  }
}
