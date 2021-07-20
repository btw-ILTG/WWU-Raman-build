#include "PinNames.h"
#include "mbed.h"
#include "SerialPort.h"
#include "CommandCodes.h"

//FileHandle *mbed::mbed_override_console(int fd) {
//        return &raspi;
//}

// Flags
#define READ_FLAG   0x1

//static DigitalOut led(LED1);

Thread thread;
Thread serialRead;
Thread serialWrite;

//static BufferedSerial raspi(D8, D2, 9600);

/*
void writeThread() {
    int counter = 0;
    char write_packet[PACKET_LENGTH] = {0};
    write_packet[0] = 'S';
    write_packet[1] = 'F';
    write_packet[2] = 'D';
    write_packet[4] = 'E';
    while (true) {
        ThisThread::flags_wait_any(0x2);
        //counter++;
        //write_packet[3] = (char)counter;
        //raspi.constructPacket(write_packet);
        //raspi.writeSerialPacket();
        if (raspi.writable()) {
            raspi.write("Wow\n", 4);
        }
    }
}


void readThread() {
    char buf[RX_BUFFER_SIZE] = {0};
    while (true) {
        ThisThread::flags_wait_any(READ_FLAG);
        led = !led;
        if (raspi.readable()) {
            uint32_t num = raspi.read(buf, sizeof(buf));
            raspi.write(buf, num);
            raspi.write("\n", 1);
        }
    }
}


void dispatchThread() {
    while (true) {
        ThisThread::sleep_for(100ms);
        serialRead.flags_set(READ_FLAG);
        ThisThread::sleep_for(100ms);
        serialWrite.flags_set(0x2);
    }
}
*/

static DigitalOut led(LED1);

// main() runs in its own thread in the OS
int main() {
    //SerialPacket raspi(D8, D2, 9600);
    //thread.start(callback(dispatchThread));
    //serialRead.start(callback(readThread));
    //serialWrite.start(callback(writeThread));

    SerialPort raspi(D8, D2, 9600);
    vector<char> test = {'H', 'e', 'l', 'l', 'o', '\n'};
    vector<char> test1 = {'Y', 'o', '\n'};
    //while (true) {
    //led = 0;
    wait_us(1000000);

    //while (true) {
    //    wait_us(500000);
        led = !led;
        raspi.writeSerialPacket(test);
        raspi.writeSerialPacket(test1);
    //}

    //while (raspi.writeSerialPacket(test) != 0) {
        //led = !led;
    //}
    /*
    if (write_status == -1) {
        led = 0;
    } else {
        led = 1;
    }
    */
    //wait_us(1000000);
    //}
    return 0;
}