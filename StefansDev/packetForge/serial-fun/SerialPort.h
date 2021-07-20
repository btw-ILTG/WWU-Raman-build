#include "mbed.h"
#include <vector>


class SerialPort {
    private:
        BufferedSerial serial_port;

    public:
        SerialPort(PinName tx, PinName rx, int baud);
        int writeSerialPacket(vector<char> tx_packet);
        int readSerialPacket(vector<char> rx_packet);
};