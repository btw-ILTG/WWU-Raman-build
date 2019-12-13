#include "mbed.h"

DigitalOut filter_IN1(PC_14); //stepper motor for filter selector
DigitalOut filter_IN2(PC_15);
DigitalOut filter_IN3(PH_0);
DigitalOut filter_IN4(PH_1);
DigitalOut grnLED(LED1);

const int mDelay = 3;
int z = 0;

int filterBack() {
    while (z < 514) {
        z++;
        grnLED = 1;
        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_ms(mDelay);
    }
    filter_IN1 = 0;
    filter_IN2 = 0;     
    filter_IN3 = 0;
    filter_IN4 = 0;
    z = 0;
    return(0);
}

int filterForward() {
    while (z < 514) {
        z++;
        grnLED = 0;
        wait_ms(1);
        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        wait_ms(mDelay);

        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 1;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 1;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 1;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        wait_ms(mDelay);
    }
    filter_IN1 = 0;
    filter_IN2 = 0;
    filter_IN3 = 0;
    filter_IN4 = 0;
    z = 0;
    return(0);
}

int main(){
    while(1){
        filterForward();
        wait(1);
        filterForward();
        wait(1);
        filterBack();
        wait(1);
        filterBack();
        wait(1);
    }    
}