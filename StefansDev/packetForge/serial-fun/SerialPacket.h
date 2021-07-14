#include "mbed.h"

#define RX_BUFFER_SIZE  32
#define TX_BUFFER_SIZE  32

class SerialPacket {
    private:
        char recieveBuffer[RX_BUFFER_SIZE];
        char transmitBuffer[TX_BUFFER_SIZE];


    public:
        SerialPacket();
        void writeSerialPacket();
        void readSerialPacket();
};