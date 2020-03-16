#include <unistd.h>
#include <mqtt.h>
#include <gpio.h>

#define ALL_PINS 3
#define OUT_PINS 2
#define IN_PINS 1

int allPins[] = {17, 27, 22};
int doorPins[] = {22};

int main(int argc, char *argv[])
{
  int ch;

  exportPins(allPins, ALL_PINS);
  setPinsDirection(allPins, OUT_PINS, 1);
  setPinsDirection(doorPins, IN_PINS, 0);

  initMqtt();

  do
  {
    if (!digitalRead(22))
    {
      sendMessage("22;0;", "doors");
    }
    usleep(1000 * 1000);
  } while (ch != 'Q' && ch != 'q');
}