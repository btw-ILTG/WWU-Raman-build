#include "mbed.h"

#define MAX_PAGES 64
#define PAGE_LENGTH 1024 // Bytes

#define SERIAL_BUFFER_SIZE	256

class SerialPort {
    private:
        BufferedSerial serial_port;
		uint8_t serial_buffer[SERIAL_BUFFER_SIZE]{0};

    public:
        SerialPort(PinName tx, PinName rx, int baud);
        
        int writeSerialPacket(uint8_t* tx_packet, uint8_t packet_datatype);
        int writeSerialSeries(uint8_t* tx_packet, int length, uint8_t packet_datatype);
        int writeSerialRaw(uint8_t* tx_packet, int length);
        int writeSerialRawRaw(uint8_t* tx_packet, int length);

        // Returns datalength in bytes
        // packet_start data_type indicates cmd packet
        // PASS in nullptr because the pointer will be overwritten
        int readSerialPacket(uint8_t** rx_packet, uint8_t &data_type);
};
