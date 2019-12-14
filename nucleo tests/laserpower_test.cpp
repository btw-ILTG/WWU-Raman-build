//testing function of voltage relay for laser
//connected to channel 1- com1 and NO1
//for NO, setting to 0 closes the switch and laser will be on
#include "mbed.h"

DigitalOut myled(LED1);
DigitalOut relay(PA_1);

int laserPower(int on){
    if(on == 1){//turn laser on
        relay = 0;
        myled = 1;    
    }
    if(on == 0){//turn laser off
        relay = 1;
        myled = 0;    
    }
}
int main() { 
    while(1) {
        laserPower(1);
        wait(10);
        laserPower(0);
        wait(10);
    }
}
