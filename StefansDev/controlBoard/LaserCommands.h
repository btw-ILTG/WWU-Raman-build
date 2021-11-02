#include "PwmOut.h"
#include "mbed.h"

// TODO: Laser TTL

// laser relay states for on and off:
enum LaserState {on = 0, off = 1};
// servo pulsewidth (in us) for open and close:
enum LaserShutterState {shutt_open = 600, shutt_close = 1500}; 

class Laser {

    private:
        DigitalOut laser_relay;
        PwmOut laser_servo;
    
        LaserState laser_power;
        LaserShutterState shutter_state;

    public:
        Laser(DigitalOut laser_relay, PwmOut laser_servo);
        void setLaserPower(LaserState setState);
        void setLaserShutter(LaserShutterState setState);
        LaserState getLaserPower() { return this->laser_power; }
        LaserShutterState getLaserShutter() { return this->shutter_state; }
        float getLaserTemperature();

};