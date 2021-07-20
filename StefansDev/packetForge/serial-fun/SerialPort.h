#include "mbed.h"
#include "SerialPacket.h"

class SerialPort {
    private:
        BufferedSerial serial_port;

    public:
        SerialPort(PinName tx, PinName rx, int baud);
        int writeSerialPacket(SerialPacket tx_packet);
        int readSerialPacket(SerialPacket rx_packet);
};