#include "mbed.h"
#include "SerialPort.h"

SerialPort::SerialPort(PinName tx, PinName rx, int baud) : 
                                        serial_port(tx, rx, baud) {
}

int SerialPort::writeSerialPacket(SerialPacket tx_packet) {
    if (this->serial_port.writable() == 1) {
        for (int i = 0; i < tx_packet.size(); i++) {
            while (this->serial_port.writable() == 0) {
                // pause thread until can be written
                //ThisThread::sleep_for(1ms);
                wait_us(10);
            }
            this->serial_port.write(&this->sending_packet.at(i),
                        sizeof(this->sending_packet.at(i)));
        }
        return 1;
    } else {
        // serial_port does not have space to write a character
        return -1;
    }
    //this->serial_port.write("\n",1);
}

int SerialPort::readSerialPacket() {
    if (this->serial_port.readable() == 1) {
       return 1; 
    } else {
        // serial_port does not have a character to read
        return -1;
    }
}
