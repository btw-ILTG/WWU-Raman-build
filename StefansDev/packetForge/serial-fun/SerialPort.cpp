#include "mbed.h"
#include <chrono>
#include <ratio>
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
int SerialPort::writeSerialPacket(vector<uint8_t> &tx_packet) {
    if (this->serial_port.writable() == 1) {
        /*
        while (this->serial_port.writable() == 0) {
            // pause thread until can be written
            // Note: serial_port.writable() is still
            // writable even if nothing is plugged
            // in to that port.
            ThisThread::sleep_for(11ms);
        }
        */

        // use the vector like an array
        // this fixes the issue where I could not read
        // two doubles from the serial port in python
        uint8_t* write_me = &tx_packet[0];
        this->serial_port.write(write_me, tx_packet.size());
        this->serial_port.sync();
        ThisThread::sleep_for(2ms);
        return 0;
    } else {
        // serial_port does not have space to write a character
        return -1;
    }
    //this->serial_port.write("\n",1);
}

int SerialPort::readSerialPacket(vector<uint8_t> &rx_packet) {
    if (this->serial_port.readable() == 1) {
        
        bool packet_started = false;
        uint8_t read[this->MAX_BUFFER_SIZE];

        Timeout read_timeout;
        this->timedout = false;
        read_timeout.attach(callback(this, &SerialPort::timeout), TIMEOUT);

        while (this->timedout == false) {
            memset(read, 0, sizeof(read));
            this->serial_port.read(read, sizeof(read));
            for (int i = 0; i < sizeof(read); i++) {
                if (read[i] == packet_start) {
                    packet_started = true;
                    rx_packet.push_back(read[i]);
                    read_timeout.detach();
                    goto started_packet;
                }
            }
        }

started_packet:

        while (packet_started == true) {
            memset(read, 0, sizeof(read));
            this->serial_port.read(read, sizeof(read));
            for (int i = 0; i < sizeof(read); i++) {
                rx_packet.push_back(read[i]);
                if (read[i] == packet_end) {
                    return 0;
                }
            }
        }
        return -2; //TIMEOUT
    } else {
        // serial_port does not have a character to read
        return -1;
    }
}

void SerialPort::timeout() {
    this->timedout = true;
}