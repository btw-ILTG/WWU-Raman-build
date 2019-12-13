#include "mbed.h"

DigitalOut cuvette_IN1(PA_4); //stepper motor for filter selector
DigitalOut cuvette_IN2(PB_0);
DigitalOut cuvette_IN3(PC_1);
DigitalOut cuvette_IN4(PC_0);
DigitalOut grnLED(LED1);

bool trayOpen;
const int mDelay = 3;
int y = 0;

int openTray() {
    while (y < 500) {
        y++;
        grnLED = 1;
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_ms(mDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 1;
        wait_ms(mDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_ms(mDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_ms(mDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_ms(mDelay);
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_ms(mDelay);
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_ms(mDelay);
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_ms(mDelay);
    }
    cuvette_IN1 = 0;
    cuvette_IN2 = 0;
    cuvette_IN3 = 0;
    cuvette_IN4 = 0;
    y = 0;
    trayOpen = true;
    return(0);
}

int closeTray() {
    while (y < 500) {
        y++;
        grnLED = 0;

        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_ms(mDelay);
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_ms(mDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_ms(mDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_ms(mDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_ms(mDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 1;
        wait_ms(mDelay);
        
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_ms(mDelay);
        
        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_ms(mDelay);
    }
    cuvette_IN1 = 0;
    cuvette_IN2 = 0;
    cuvette_IN3 = 0;
    cuvette_IN4 = 0;
    y = 0;
    trayOpen = false;
    return(0);
}

int main(){
    while(1){
        openTray();
        wait(1);
        closeTray();
        wait(1);
    }    
}
