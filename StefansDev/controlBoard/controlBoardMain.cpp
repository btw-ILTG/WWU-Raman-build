#include "mbed.h"
#include <cstdint>

#include "commandCodes.h"

static BufferedSerial raspi(D8, D2, 9600);

static DigitalOut myled(LED1);

FileHandle *mbed::mbed_override_console(int fd) {
    return &raspi;
}

char readChar(BufferedSerial *serialDevice) {
    char c;
    while (true) {
        if (ssize_t num = serialDevice->read(&c, 1)) {
            return c;
        }
    }
}

// main() runs in its own thread in the OS
int main()
{
    raspi.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );

    int packetFlag = 0;
    myled = 0;

    while (true) {
        char c;

        c = readChar(&raspi);
            switch (c) {
                case packet_start:
                    raspi.write(&c, 1);
                    c = readChar(&raspi);
                    switch (c) {
                        case packet_flag:
                            raspi.write(&c, 1);
                            packetFlag = 1;
                            while (packetFlag == 1) {
                                c = readChar(&raspi);
                                raspi.write(&c, 1);
                                switch (c) {
                                    case control_board:
                                        myled = !myled;
                                        continue;
                                    case packet_end:
                                        packetFlag = 0;
                                        break;
                                }
                            }
                    }

            }
    }
}