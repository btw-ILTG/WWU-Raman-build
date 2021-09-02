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
        int writeSerialPacket(uint8_t* tx_packet, uint8_t packet_datatype);
        int writeSerialSeries(uint8_t* tx_packet, int length, uint8_t packet_datatype);
        int readSerialPacket(vector<uint8_t> &rx_packet);
        void timeout();
};