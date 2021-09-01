#include "mbed.h"
#include <vector>

#define TIMEOUT 2000ms

enum DataType {int_packet = 4, float_packet = 4, double_packet = 8};


class SerialPort {
    private:
        BufferedSerial serial_port;
        char MAX_BUFFER_SIZE = 32;
        volatile bool timedout = false;

    public:
        SerialPort(PinName tx, PinName rx, int baud);
        int writeSerialPacket(vector<uint8_t> &tx_packet);
        int writeSerialSeries(uint8_t* tx_packet, int length, DataType packet_datatype);
        int readSerialPacket(vector<uint8_t> &rx_packet);
        void timeout();
};