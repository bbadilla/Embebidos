#include <unistd.h>
#include <mqtt.h>
#include <gpio.h>

#define OUT_PINS 2
#define IN_PINS 1

int main(int argc, char *argv[])
{
  int ch;

  int ledPins[] = {22, 27};
  int doorPins[] = {17};

  exportPins(ledPins, OUT_PINS);
  exportPins(doorPins, IN_PINS);

  setPinsDirection(ledPins, OUT_PINS, 1);
  setPinsDirection(doorPins, IN_PINS, 0);

  initMqtt(ledPins, OUT_PINS);

  do
  {
    if (!digitalRead(17))
    {
      sendMessage("1", "doors/22");
    }
    usleep(1000 * 1000);
  } while (ch != 'Q' && ch != 'q');
}
