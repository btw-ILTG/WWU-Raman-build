// Testing communication between raspberry pi and the nucleo board
// With the laser power on
#include "mbed.h"
#include <cstdint>

#define packet_start        0xF0
#define laser_on       	    0xA1
#define laser_off           0xA2

static BufferedSerial raspi(D8, D2, 9600);

const int usDelay = 1000;

static DigitalOut myled(LED1);
static DigitalOut relay(PA_1);

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
    raspi.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );
    // Initialize laser to off
    laserPower(0);

    // Register a callback to process a Rx (receive) interrupt.
    while(true) {
        char c;
       
        if (ssize_t num = raspi.read(&c, 1)) {
            if (c == laser_on) {
                laserPower(1);
                raspi.write("Laser on\n",9);
            } else if (c == laser_off) {
                laserPower(0);
                raspi.write("Laser off\n",10);
            }
        }
    }
    
}
