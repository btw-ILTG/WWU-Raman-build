#include "mbed.h"
#include <vector>
#include "SerialPort.h"
#include "CommandCodes.h"

//static DigitalOut led(LED1);

SerialPort::SerialPort(PinName tx, PinName rx, int baud) : 
                                        serial_port(tx, rx, baud) {
}

/**********************************************************
This must be called with a vector that contains a full
serial packet. 
    i.e. packet_start, packet_flag, ... , packet_end
***********************************************************/
int SerialPort::writeSerialPacket(vector<char> tx_packet) {
    if (this->serial_port.writable() == 1) {
        for (int i = 0; i < tx_packet.size(); i++) {
            while (this->serial_port.writable() == 0) {
                // pause thread until can be written
                // Note: serial_port.writable() is still
                // writable even if nothing is plugged
                // in to that port.
                ThisThread::sleep_for(11ms);
            }
            this->serial_port.write(&tx_packet.at(i), sizeof(tx_packet.at(i)));
        }
        ThisThread::sleep_for(11ms);
        return 0;
    } else {
        // serial_port does not have space to write a character
        return -1;
    }
    //this->serial_port.write("\n",1);
}

int SerialPort::readSerialPacket(vector<char> &rx_packet) {
    if (this->serial_port.readable() == 1) {
        while (this->serial_port.readable() == 1) {
            char read[this->MAX_BUFFER_SIZE];
            this->serial_port.read(read, sizeof(read));
            for (int i = 0; i < sizeof(read); i++) {
                rx_packet.push_back(read[i]);
                if (read[i] == packet_end) {
                    return 0;
                }
            }
        }
        return 0; 
    } else {
        // serial_port does not have a character to read
        return -1;
    }
}
