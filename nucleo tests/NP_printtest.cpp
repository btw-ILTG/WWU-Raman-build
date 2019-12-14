/*
Testing what kinds of data can be sent through the serial port.
Can do float (%f), int (%d), and string (%s) works also.
*/
#include "mbed.h"
#include <string>

DigitalIn button(USER_BUTTON);

Serial raspi(USBTX, USBRX);

#define packet_start 0xF0

int main() {
    float x = 1.23456;
    string test = "Good Evening.";
    while(1) {
        if(raspi.readable()==1){
            switch(raspi.getc()){
                case packet_start:
                    raspi.printf("Hello! %s\n" , test);
                    raspi.printf("x = %.3f\n" , x);
                continue;
                default:
                    raspi.printf("error\n");
                continue;
            }
        }
    }
}