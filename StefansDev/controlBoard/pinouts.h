#include "mbed.h"
#include "DS18B20.h"

#ifndef PINOUTS

#define THERMOMETER DS18B20
#define CUVETTE_DEVICE 1
#define LASER_DEVICE 1

#endif

// Thermometer port
THERMOMETER device(PC_8);

// Raspberry Pi serial
static BufferedSerial raspi(D8, D2);

// Laser controls
static PwmOut laser_servo(PA_11);
static DigitalOut laser_relay(PA_1);

// Stepper motor for cuvette
DigitalOut cuvette_IN1(PA_4); 
DigitalOut cuvette_IN2(PB_0);
DigitalOut cuvette_IN3(PC_1);
DigitalOut cuvette_IN4(PC_0);