#include "mbed.h"
#include <vector>

#define TIMEOUT 2000ms

class SerialPort {
    private:
        BufferedSerial serial_port;
        char MAX_BUFFER_SIZE = 32;
        volatile bool timedout = false;

    public:
        SerialPort(PinName tx, PinName rx, int baud);
        int writeSerialPacket(vector<unsigned char> tx_packet);
        int readSerialPacket(vector<unsigned char> &rx_packet);
        void timeout();
};