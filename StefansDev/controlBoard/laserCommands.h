#include "mbed.h"

// TODO: Laser TTL 

// laser relay states for on and off:
enum laser_state {on = 0, off = 1};
// servo pulsewidth (in us) for open and close:
enum laser_shutter_state {shutt_open = 600, shutt_close = 1500}; 

void laserPower(laser_state setState);
void laserShutter(laser_shutter_state setState);
float laserTemperature();