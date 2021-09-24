#include "mbed.h"
#include <cstdint>

#include "CommandCodes.h"
#include "laserCommands.h"
#include "pinouts.h"
#include "SerialPort.cpp"
#include "SerialPort.h"


// main() runs in its own thread in the OS
int main() {
	SerialPort raspi(D8, D2, 921600);
	uint8_t* read_packet = nullptr;
	uint8_t data_return;
	int* data_int = nullptr;
	float* data_float = nullptr;
	double* data_double = nullptr;

	while (true) {
		int read_length = raspi.readSerialPacket(&read_packet, data_return);
		switch (data_return) {
			case packet_int:
				data_int = (int *) read_packet;
				break;

			case packet_float:
				data_float = (float *) read_packet;
				break;

			case packet_double:
				data_double = (double *) read_packet;
				break;

			case cmd_laser:
				break;
			
			case cmd_cuvette:
				break;

			case cmd_filter:
				break;

			case cmd_ccd_pelt:
				break;
		}
	}
	return 0;
}
