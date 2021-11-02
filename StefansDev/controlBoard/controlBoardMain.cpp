#include "mbed.h"
#include <cstdint>

#include "CommandCodes.h"
#include "LaserCommands.h"
#include "pinouts.h"
#include "SerialPort.h"
#include "CuvetteCommands.h"
#include "FilterCommands.h"

// main() runs in its own thread in the OS
int main() {
	SerialPort raspi(D8, D2, 921600);
	Laser laser(LASER_RELAY, LASER_SERVO);
	Cuvette cuvette(CUVETTE_IN1, CUVETTE_IN2, CUVETTE_IN3, CUVETTE_IN4);
	Filter filter(FILTER_IN1, FILTER_IN2, FILTER_IN3, FILTER_IN4);

	uint8_t* read_packet = nullptr;
	uint8_t data_return;
	int* data_int = nullptr;
	float* data_float = nullptr;
	double* data_double = nullptr;

	float laser_temperature = 0;
	float cuvette_temperature = 0;

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
				switch (read_packet[0]) {
					case laser_on:
						laser.setLaserPower(on);
						uint8_t ok_packet = packet_ok;
						raspi.writeSerialRaw(&ok_packet, 1);
						break;

					case laser_off:
						laser.setLaserPower(off);
						break;

					case shutter_open:
						laser.setLaserShutter(shutt_open);
						break;

					case shutter_close:
						laser.setLaserShutter(shutt_close);
						break;

					case laser_temp:
						laser_temperature = laser.getLaserTemperature();
						break;
						
				}
				break;

			case cmd_cuvette:
				switch (read_packet[0]) {
					case tray_open:
						if (cuvette.getCuvetteState() != cuv_open) {
							cuvette.openTray();	
						}
						break;

					case tray_close:
						if (cuvette.getCuvetteState() != cuv_closed) {
							cuvette.openTray();	
						}
						break;

					case tray_heat:
						// TODO: Implement
						break;

					case tray_cool:
						// TODO: Implement
						break;

					case tray_temp:
						cuvette_temperature = cuvette.getCuvetteTemperature();
						break;
				}
				break;
				
			case cmd_filter:
				switch (read_packet[0]) {
					case filter_open:
						// TODO: Figure out if this is actually needed
						break;

					case filter_forward:
						filter.filterForward();
						break;

					case filter_backward:
						filter.filterBackward();
						break;
				}
				break;

			case cmd_ccd_pelt:
				// TODO: Implement
				break;

			default:
				uint8_t error_packet = packet_error;
				raspi.writeSerialRaw(&error_packet, 1);
				break;
		}
		ThisThread::sleep_for(1000ms);
	}
	return 0;
}
