#include "mbed.h"
#include "SerialPacket.h"

#include "CommandCodes.h"

SerialPacket::SerialPacket(PinName tx, PinName rx, int baud) : 
                                        serial_port(tx, rx, baud) {
}

void SerialPacket::writeSerialPacket() {
    for (int i = 0; i < PACKET_LENGTH; i++) {
        this->serial_port.write(&this->sendingPacket[i], 
                                sizeof(this->sendingPacket[i]));
    }
    this->serial_port.write("\n",1);
}

void SerialPacket::readSerialPacket() {
    
}

void SerialPacket::constructPacket(char *packet) {
    for (int i = 0; i < PACKET_LENGTH; i++) {
        this->sendingPacket[i] = packet[i];
    }
}