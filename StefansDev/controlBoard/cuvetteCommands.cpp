#include "mbed.h"

#include "pinouts.h"
#include "cuvetteCommands.h"
#include <chrono>

Cuvette::Cuvette(DigitalOut cuvette_IN1, DigitalOut cuvette_IN2, 
                DigitalOut cuvette_IN3, DigitalOut cuvette_IN4, 
                CuvetteState initial, int cuvette_limit) 
                : cuvette_IN1(cuvette_IN1), cuvette_IN2(cuvette_IN2), 
                cuvette_IN3(cuvette_IN3), cuvette_IN4(cuvette_IN4) {
    this->cuvette_state = initial;
    this->cuvette_limit = cuvette_limit;
}

float Cuvette::getCuvetteTemperature() {
    return device.readTemperature(CUVETTE_DEVICE);
}

int Cuvette::openTray(int msDelay) {
    if (this->cuvette_state == cuv_open) {
        // Don't open and open cuvette
        return -1;
    }
    int cuvetteCounter = 0;
    while (cuvetteCounter < this->cuvette_limit) {
        cuvetteCounter++;
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        // Sleep this thread cause we don't need to do anything
        // while we wait
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 1;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
    }
    cuvette_IN1 = 0;
    cuvette_IN2 = 0;
    cuvette_IN3 = 0;
    cuvette_IN4 = 0;
    return 0;
}

int Cuvette::closeTray(int msDelay) {
    if (this->cuvette_state == cuv_closed) {
        // Don't close and closed cuvette
        return -1;
    }
    int cuvette_counter;
    while (cuvette_counter < this->cuvette_limit) {
        cuvette_counter++;

        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 1;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        ThisThread::sleep_for(chrono::milliseconds(msDelay));
    }
    cuvette_IN1 = 0;
    cuvette_IN2 = 0;
    cuvette_IN3 = 0;
    cuvette_IN4 = 0;
    return 0;
}