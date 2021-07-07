//testing servo (laser shutter) function
#include "mbed.h"

PwmOut servo(PA_11);
DigitalOut grnLED(LED1);

int main() {
    servo.period_ms(20);

    while(1){
        grnLED = 0;
        //servo.pulsewidth_us(600); //pulsewidth 600 is shutter open
        wait_us(2000000);
        grnLED = 1;
        //servo.pulsewidth_us(1500); //rotate 90 to close shutter
        wait_us(2000000);
    }
}