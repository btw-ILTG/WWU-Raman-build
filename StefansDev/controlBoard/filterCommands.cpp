//functions for filter selection
#include "mbed.h"

#include "filterCommands.h"
#include "pinouts.h"

Filter::Filter(DigitalOut filter_IN1, DigitalOut filter_IN2, 
                DigitalOut filter_IN3, DigitalOut filter_IN4, 
                int filter_limit) 
                : filter_IN1(filter_IN1), filter_IN2(filter_IN2), 
                filter_IN3(filter_IN3), filter_IN4(filter_IN4) {
    this->filter_limit = filter_limit;
}

int Filter::filterBackward(int msDelay) {
    int filter_counter = 0;
    while (filter_counter < this->filter_limit) {
        filter_counter++;
        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));

        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
    }
    filter_IN1 = 0;
    filter_IN2 = 0;     
    filter_IN3 = 0;
    filter_IN4 = 0;
    return 0;
}

int Filter::filterForward(int msDelay) {
    int filter_counter = 0;
    while (filter_counter < this->filter_limit) {
        filter_counter++;

        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));

        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));

        filter_IN1 = 1;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 1;
        filter_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 1;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
    }
    filter_IN1 = 0;
    filter_IN2 = 0;
    filter_IN3 = 0;
    filter_IN4 = 0;
    return 0;
}