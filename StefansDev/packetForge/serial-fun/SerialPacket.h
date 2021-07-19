#include "mbed.h"

#define RX_BUFFER_SIZE  32
#define TX_BUFFER_SIZE  32
#define PACKET_LENGTH   5

class SerialPacket {
    private:
        BufferedSerial serial_port;

        char recieveBuffer[RX_BUFFER_SIZE] = {0};
        //char transmitBuffer[TX_BUFFER_SIZE] = {0}; may not be needed

        char receivedPacket[PACKET_LENGTH] = {0};
        char sendingPacket[PACKET_LENGTH] = {0};


    public:
        SerialPacket(PinName tx, PinName rx, int baud);
        void writeSerialPacket();
        void readSerialPacket();
        void constructPacket(char *packet);
};