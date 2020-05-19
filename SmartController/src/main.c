#include <unistd.h>
#include <mqtt.h>
#include <gpio.h>

#define OUT_PINS 5
#define IN_PINS 4

int main(int argc, char *argv[])
{
  int ch;

  int ledPins[] = {17, 27, 22, 10, 9};
  int doorPins[] = {6, 13, 19, 26};

  exportPins(ledPins, OUT_PINS);
  exportPins(doorPins, IN_PINS);

  setPinsDirection(ledPins, OUT_PINS, 1);
  setPinsDirection(doorPins, IN_PINS, 0);

  initMqtt(ledPins, OUT_PINS);

  do
  {
    if (!digitalRead(6))
    {
      sendMessage("1", "doors/6");
    }

    if (!digitalRead(13))
    {
      sendMessage("1", "doors/13");
    }

    if (!digitalRead(19))
    {
      sendMessage("1", "doors/19");
    }

    if (!digitalRead(26))
    {
      sendMessage("1", "doors/26");
    }

    usleep(500 * 1000);
  } while (1);
}
