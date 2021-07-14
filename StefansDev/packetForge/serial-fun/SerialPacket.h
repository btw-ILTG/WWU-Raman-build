#include "mbed.h"

#define RX_BUFFER_SIZE  32
#define TX_BUFFER_SIZE  32

class SerialPacket {
    private:
        BufferedSerial serial_port;

        char recieveBuffer[RX_BUFFER_SIZE] = {0};
        char transmitBuffer[TX_BUFFER_SIZE] = {0};


    public:
        SerialPacket(PinName tx, PinName rx);
        void writeSerialPacket();
        void readSerialPacket();
};