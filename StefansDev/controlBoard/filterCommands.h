#include "mbed.h"

// TODO: Rotary encoder

class Filter {
    private:
        DigitalOut filter_IN1; 
        DigitalOut filter_IN2;
        DigitalOut filter_IN3;
        DigitalOut filter_IN4;

        int filter_limit;

    public:
        Filter(DigitalOut filter_IN1, DigitalOut filter_IN2, 
                DigitalOut filter_IN3, DigitalOut filter_IN4,
                int filter_limit = 514);
        int filterForward(int msDelay = 3);
        int filterBackward(int msDelay = 3);
};