#include "mbed.h"
#include "DS18B20.h"

#ifndef PINOUTS

#define THERMOMETER DS18B20
#define CUVETTE_DEVICE 0
#define LASER_DEVICE 1

// Laser controls
#define LASER_RELAY PA_1
#define LASER_SERVO PA_11

// Cuvette output
#define CUVETTE_IN1 PA_4
#define CUVETTE_IN2 PB_0
#define CUVETTE_IN3 PC_1
#define CUVETTE_IN4 PC_0

// Filter selector
#define FILTER_IN1 PC_14
#define FILTER_IN2 PC_15
#define FILTER_IN3 PH_0
#define FILTER_IN4 PH_1

// Thermometer port
static THERMOMETER device(PC_8);

#endif


// Raspberry Pi serial
//static BufferedSerial raspi(D8, D2, 921600);
