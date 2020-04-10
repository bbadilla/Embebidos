#ifndef _GPIO_H
#define _GPIO_H

int exportPin(int pin);
int unexportPin(int pin);
int pinMode(int pin, int mode);
int digitalWrite(int pin, int value);
int digitalRead(int pin);
void exportPins(int *pins, int size);
void unexportPins(int *pins, int size);
void setPinsValue(int *pins, int size, int value);
void setPinsDirection(int *pins, int size, int direction);
void delay(unsigned int milliseconds);

#endif