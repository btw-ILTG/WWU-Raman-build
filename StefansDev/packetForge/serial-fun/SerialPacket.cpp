#include "mbed.h"
#include "SerialPacket.h"

SerialPacket::SerialPacket(PinName tx, PinName rx) : 
                                        serial_port(tx, rx) {
}