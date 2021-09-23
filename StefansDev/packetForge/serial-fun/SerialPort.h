#include "mbed.h"

#define SERIAL_BUFFER_SIZE	256 // bytes
#define MAX_PACKET_SIZE		11 // Because of start + datatype + double + end

class SerialPort {
    private:
        BufferedSerial serial_port;
		uint8_t serial_buffer[SERIAL_BUFFER_SIZE]{0};

    public:
        SerialPort(PinName tx, PinName rx, int baud);
        
		/********************************************************************************
			Takes in data that is converted to a uint8_t* via "(uint8_t*) data"
				type casting.
			Returns:			0 if success and -1 if error
			tx_packet:			pointer to uint8_t array of what is to be sent
			packet_datatype:	type code (uint8_t) of the data being sent
									either: packet_int, packet_float, or packet_double
		*********************************************************************************/
        int writeSerialPacket(uint8_t* tx_packet, uint8_t packet_datatype);

		/********************************************************************************
			Adds serial series start and end control packets and sends the data in
				in tx_packet with length (in bytes)	
			Returns:			0 if success and -1 if error
			tx_packet:			pointer to uint8_t array of what is to be sent
			length:				length of tx_packet in bytes so:
									(number of data)*sizeof(data)
			packet_datatype:	type code (uint8_t) of the data being sent	
		*********************************************************************************/
        int writeSerialSeries(uint8_t* tx_packet, int length, uint8_t packet_datatype);

		/********************************************************************************
			Adds packet_start, packet_end, and packet_datatype to the uint8_t array 
				given and then sends it over the serial bus.
			Returns:			0 if success and -1 if error
			tx_packet:			pointer to uint8_t array of what is to be sent
			length:				length of tx_packet array (in Bytes)
			packet_datatype:	type code (uint8_t) of the data being sent	
		*********************************************************************************/
        int writeSerialRaw(uint8_t* tx_packet, int length);

		/********************************************************************************
			Writes exactly what you give it to the serial bus without packet_start,
				packet_end, and packet_datatype. Mostly used for testing
			Returns:			0 if success and -1 if error
			tx_packet:	pointer to uint8_t array of what is to be sent
			length:		length of tx_packet array
		*********************************************************************************/
        int writeSerialRawRaw(uint8_t* tx_packet, int length);

		/********************************************************************************
			Returns the datalength in bytes. If error returns -1 or 0 if nothing read
			rx_packet: pointer to uint8_t array, anything passed in will be overwritten
						so make sure it is a nullptr. (Pass in by reference)
			data_type: contains the type code associated with the incoming data, which
						is the second uint8_t in the sequence
		*********************************************************************************/
        int readSerialPacket(uint8_t** rx_packet, uint8_t &data_type);
};
