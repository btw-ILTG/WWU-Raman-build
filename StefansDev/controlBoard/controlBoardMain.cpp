#include "mbed.h"
#include <cstdint>

#include "commandCodes.h"
#include "pinouts.h"

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

}