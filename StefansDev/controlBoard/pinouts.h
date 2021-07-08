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
static BufferedSerial raspi(D8, D2, 921600);

// Laser controls
static PwmOut laser_servo(PA_11);
static DigitalOut laser_relay(PA_1);

// Stepper motor for cuvette
DigitalOut cuvette_IN1(PA_4); 
DigitalOut cuvette_IN2(PB_0);
DigitalOut cuvette_IN3(PC_1);
DigitalOut cuvette_IN4(PC_0);

//stepper motor for filter selector
DigitalOut filter_IN1(PC_14);
DigitalOut filter_IN2(PC_15);
DigitalOut filter_IN3(PH_0);
DigitalOut filter_IN4(PH_1);