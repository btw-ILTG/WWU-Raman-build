#include "mbed.h"
#include <vector>

#define TIMEOUT 2000ms
#define BYTES_PER_SEND 4

class SerialPort {
    private:
        BufferedSerial serial_port;
        char MAX_BUFFER_SIZE = 32;
        volatile bool timedout = false;

    public:
        SerialPort(PinName tx, PinName rx, int baud);
        int writeSerialPacket(vector<uint8_t> &tx_packet);
        int writeSerialSeries(uint8_t* tx_packet, int size);
        int readSerialPacket(vector<uint8_t> &rx_packet);
        void timeout();
};