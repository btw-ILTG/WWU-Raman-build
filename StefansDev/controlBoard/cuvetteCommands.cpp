#include "mbed.h"

#include "pinouts.h"
#include "cuvetteCommands.h"
#include "DS18B20.h"
#include "OneWireDefs.h"

int openTray(int uDelay) {
    while (cuvetteCounter < 500) {
        cuvetteCounter++;
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_us(uDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 1;
        wait_us(uDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_us(uDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_us(uDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_us(uDelay);
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_us(uDelay);
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_us(uDelay);
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_us(uDelay);
    }
    cuvette_IN1 = 0;
    cuvette_IN2 = 0;
    cuvette_IN3 = 0;
    cuvette_IN4 = 0;
    cuvetteCounter = 0;
    trayOpen = true;
    return(0);
}

int closeTray(int uDelay) {
    while (cuvetteCounter < 500) {
        cuvetteCounter++;

        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_us(uDelay);
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_us(uDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_us(uDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_us(uDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_us(uDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 1;
        wait_us(uDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_us(uDelay);
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_us(uDelay);
    }
    cuvette_IN1 = 0;
    cuvette_IN2 = 0;
    cuvette_IN3 = 0;
    cuvette_IN4 = 0;
    cuvetteCounter = 0;
    trayOpen = false;
    return(0);
}