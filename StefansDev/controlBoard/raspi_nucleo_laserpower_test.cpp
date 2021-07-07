// Testing communication between raspberry pi and the nucleo board
// With the laser power on
#include "mbed.h"
#include <cstdint>
#include "laserCommands.h"

#define packet_start        0xF0
#define packet_flag         0xF2
#define packet_end          0xF3

#define cmd_laser           0xA0
#define laser_on       	    0xA1
#define laser_off           0xA2
#define shutter_open        0xA3
#define shutter_close       0xA4
#define laser_temp          0xA5

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

char readChar(BufferedSerial *serialDevice) {
    char c;
    while (true) {
        if (ssize_t num = serialDevice->read(&c, 1)) {
            return c;
        }
    }
}

FileHandle *mbed::mbed_override_console(int fd) {
    return &raspi;
}

int main(){
    raspi.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );
    // Initialize laser to off
    laserPower(0);

    int packetFlag = 0;
    
    while(true) {
        char c;
       
        c = readChar(&raspi);
        switch (c) {
            case packet_start:
                printf("Packet start");
                c = readChar(&raspi); 
                switch(c) {
                    case packet_flag:
                        packetFlag = 1;
                        printf("Packet flag");
                        while (packetFlag == 1) {
                            c = readChar(&raspi);
                            switch (c) {
                                case cmd_laser:
                                    printf("Cmd laser");
                                    c = readChar(&raspi);
                                    switch(c) {  
                                        case laser_on:
                                            laserPower(1);
                                            printf("Laser on");
                                            continue;

                                        case laser_off:
                                            laserPower(0);
                                            printf("Laser off");
                                            continue;

                                        default:
                                            printf("Laser cmd fail");
                                    }
                                    continue;

                                case packet_end:
                                    packetFlag = 0;
                                    printf("Packet end\n");
                                    break;

                                default:
                                    printf("Not IMP");
                            }
                        }
                        continue;
                    default:
                        break;
                }                          
                        
            default:
                raspi.write("Different\n", 10);
                continue;
            }
    }
}