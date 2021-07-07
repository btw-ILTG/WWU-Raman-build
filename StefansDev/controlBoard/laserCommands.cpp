#include "mbed.h"

#include "pinouts.h"
#include "laserCommands.h"
#include "DS18B20.h"
#include "OneWireDefs.h"

void laserPower(laser_state setState) {
    laser_relay = setState;
}

void laserShutter(laser_shutter_state setState) {
    laser_servo.pulsewidth_us(setState);
}

float laserTemperature() {
    return device.readTemperature(LASER_DEVICE);
}