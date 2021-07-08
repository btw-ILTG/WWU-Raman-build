#include "mbed.h"

static BufferedSerial raspi(D8, D2, 9600);

FileHandle *mbed::mbed_override_console(int fd) {
    return &raspi;
}

char readChar(BufferedSerial *serialDevice) {
    char c[4];
    while (true) {
        if (ssize_t num = serialDevice->read(&c, 4)) {
            return *c;
        }
    }
}


// main() runs in its own thread in the OS
int main() {
    char packet[4] = {0};
    *packet = readChar(&raspi);
    raspi.write(packet, 4);
}