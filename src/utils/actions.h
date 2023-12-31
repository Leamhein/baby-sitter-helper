#include <Arduino.h>

int buttonLed = D10;
int notificationLed = D9;
int fadeAmount = 5; // Amount to fade the LED by
int brightness = 0; // Current brightness of the LED

void active_status_blink()
{
    digitalWrite(buttonLed, HIGH);
    delay(50);
    digitalWrite(buttonLed, LOW);
    delay(50);
}

void turn_off_notification_led()
{
    analogWrite(notificationLed, 0);
}

void disconnect_status_blink()
{
    analogWrite(notificationLed, brightness);
    brightness = brightness + fadeAmount;
    if (brightness <= 0 || brightness >= 255)
    {
        fadeAmount = -fadeAmount;
    }
    delay(50);
}