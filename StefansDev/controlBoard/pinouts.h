#include "mbed.h"
#include "DS18B20.h"

#ifndef PINOUTS

#define THERMOMETER DS18B20
#define CUVETTE_DEVICE 1
#define LASER_DEVICE 1

#endif

THERMOMETER device(PC_8);
static PwmOut laser_servo(PA_11);
static DigitalOut laser_relay(PA_1);
static BufferedSerial raspi(D8, D2);