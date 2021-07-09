#include "lfs2.h"
#include "mbed.h"
#include "PwmOut.h"

#include "pinouts.h"
#include "laserCommands.h"
#include "DS18B20.h"
#include "OneWireDefs.h"

Laser::Laser(DigitalOut laser_relay_in, PwmOut laser_servo_in) : 
        laser_relay(laser_relay_in), laser_servo(laser_servo_in) {
    this->setLaserPower(off);
    this->setLaserShutter(shutt_close);
}

void Laser::setLaserPower(LaserState setState) {
    this->laser_relay = setState;
    this->laser_power = setState;
}

void Laser::setLaserShutter(LaserShutterState setState) {
    this->laser_servo.pulsewidth_us(setState);
    this->shutter_state = setState;
}

float Laser::getLaserTemperature() {
    return device.readTemperature(LASER_DEVICE);
}