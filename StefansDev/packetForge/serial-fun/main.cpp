#include "mbed.h"

#define BUFFER_SIZE 32

static BufferedSerial raspi(D8, D2, 9600);

FileHandle *mbed::mbed_override_console(int fd) {
    return &raspi;
}

char readChar(BufferedSerial *serialDevice) {
    char c[BUFFER_SIZE];
    wait_us(2000000);
    while (true) {
        if (ssize_t num = serialDevice->read(&c, sizeof(c))) {
            return *c;
        }
    }
}


// main() runs in its own thread in the OS
int main() {
    raspi.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );

    char packet[BUFFER_SIZE] = {0};

    while (true) {
        if (ssize_t num = raspi.read(packet, sizeof(packet))) {
            raspi.write(packet, num);
            printf("\n");
        }
        //printf("value of packet: %.*s\n", (int)sizeof(packet), packet);
    }
}