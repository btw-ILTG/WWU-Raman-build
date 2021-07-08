//functions for filter selection
#include "mbed.h"

#include "filterCommands.h"
#include "pinouts.h"

int filterBackward(int uDelay) {
    while (filterCounter < 514) {
        filterCounter++;
        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        wait_us(uDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 0;
        wait_us(uDelay);

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_us(uDelay);

        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_us(uDelay);
    }
    filter_IN1 = 0;
    filter_IN2 = 0;     
    filter_IN3 = 0;
    filter_IN4 = 0;
    filterCounter = 0;
    return(0);
}

int filterForward(int uDelay) {
    while (filterCounter < 514) {
        filterCounter++;

        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        wait_us(uDelay);

        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_us(uDelay);

        filter_IN1 = 1;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_us(uDelay);

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_us(uDelay);

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 1;
        filter_IN4 = 0;
        wait_us(uDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 0;
        wait_us(uDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 1;
        wait_us(uDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        wait_us(uDelay);
    }
    filter_IN1 = 0;
    filter_IN2 = 0;
    filter_IN3 = 0;
    filter_IN4 = 0;
    filterCounter = 0;
    return(0);
}