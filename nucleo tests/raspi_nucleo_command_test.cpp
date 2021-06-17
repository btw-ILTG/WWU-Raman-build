//testing communication between raspberry pi and the nucleo board
#include "mbed.h"

#define packet_start    0xF0
#define tray_open       0xA1

DigitalOut grnLED(LED1);
DigitalOut cuvette_IN1(PA_4); 
DigitalOut cuvette_IN2(PB_0); 
DigitalOut cuvette_IN3(PC_1); 
DigitalOut cuvette_IN4(PC_0);  

Serial raspi(USBTX, USBRX, 9600);

int z;
const int usDelay = 1000;

int openTray(){
    while (z < 500) {
        z++;
        grnLED = 1;
        wait_us(1);
        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_us(usDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 1;
        wait_us(usDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_us(usDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_us(usDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_us(usDelay);

        cuvette_IN1 = 1;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_us(usDelay);

        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_us(usDelay);

        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_us(usDelay);
    }
    cuvette_IN1 = 0;
    cuvette_IN2 = 0;        
    cuvette_IN3 = 0;
    cuvette_IN4 = 0;
    z = 0;
    return(0);
}

int main(){
    z = 0;
    while(1){
        if(raspi.readable()==1){
            switch (raspi.getc()){
                case packet_start:
                    switch (raspi.getc()){
                        case tray_open:
                            openTray();
                            raspi.printf("Opening Tray\n");
                            continue;
                        default:
                            raspi.printf("Fail Switch Two\n");
                            continue;
                    } 
                default:
                    raspi.printf("Fail Switch One\n");
                    continue;
                    
            }    
        }
    }
}
