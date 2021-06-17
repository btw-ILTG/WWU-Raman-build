// Testing communication between raspberry pi and the nucleo board
// With the laser power on
#include "mbed.h"

#define packet_start    0xF0
#define laser_on       	0xA1
#define laser_off       0xA2

Serial raspi(USBTX, USBRX, 9600);

const int usDelay = 1000;

DigitalOut myled(LED1);
DigitalOut relay(PA_1);

void laserPower(int on){
    if(on == 1){//turn laser on
        relay = 0;
        myled = 1;
    }
    if(on == 0){//turn laser off
        relay = 1;
        myled = 0;
    }
}

int main(){
    while(1){
        if(raspi.readable()==1){
            switch (raspi.getc()){
                case packet_start:
                    switch (raspi.getc()){
                        case laser_on:
							laserPower(1);
                            raspi.printf("Powering on laser\n");
                            continue;
						case laser_off:
							laserPower(0);
                            raspi.printf("Powering off laser\n");
                        default:
                            raspi.printf("Fail power on laser\n");
                            continue;
                    } 
                default:
                    raspi.printf("Fail Switch One\n");
                    continue;
                    
            }    
        }
    }
}
