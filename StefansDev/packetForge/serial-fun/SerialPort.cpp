#include "mbed.h"
#include <vector>
#include "SerialPort.h"

//static DigitalOut led(LED1);

SerialPort::SerialPort(PinName tx, PinName rx, int baud) : 
                                        serial_port(tx, rx, baud) {
}

int SerialPort::writeSerialPacket(vector<char> tx_packet) {
    if (this->serial_port.writable() == 1) {
        for (int i = 0; i < tx_packet.size(); i++) {
            while (this->serial_port.writable() == 0) {
                // pause thread until can be written
                //led = !led;
                ThisThread::sleep_for(1ms);
                //wait_us(10);
            }
            this->serial_port.write(&tx_packet.at(i), sizeof(tx_packet.at(i)));
        }
        return 0;
    } else {
        // serial_port does not have space to write a character
        return -1;
    }
    //this->serial_port.write("\n",1);
}

int SerialPort::readSerialPacket(vector<char> rx_packet) {
    if (this->serial_port.readable() == 1) {
       return 0; 
    } else {
        // serial_port does not have a character to read
        return -1;
    }
}
