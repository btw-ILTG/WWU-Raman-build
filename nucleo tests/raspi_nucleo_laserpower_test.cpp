// Testing communication between raspberry pi and the nucleo board
// With the laser power on
#include "mbed.h"
#include <cstdint>

#define packet_start        0xF0
#define laser_on       	    0xA1
#define laser_off           0xA2
#define MAXIMUM_BUFFER_SIZE 8

static UnbufferedSerial raspi(D1, D0, 9600);

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
void on_rx_interrupt()
{
    char c;

    // Read the data to clear the receive interrupt.
    raspi.read(&c, 1);

    if (c == 0xA1) {
        laserPower(1);
    } else if (c == 0xA2) {
        laserPower(0);
    }
}

int main(){
    raspi.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 0
    );

    // Initialize laser to off
    laserPower(0);

    // Register a callback to process a Rx (receive) interrupt.
    raspi.attach(&on_rx_interrupt, SerialBase::RxIrq);
    
}
