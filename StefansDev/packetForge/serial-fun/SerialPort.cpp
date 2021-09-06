#include "ThisThread.h"
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
    i.e. packet_start, packet_datatype, ... , packet_end
***********************************************************/
int SerialPort::writeSerialPacket(uint8_t* tx_packet, uint8_t packet_datatype) {
    if (this->serial_port.writable() == 1) {
        
        int packet_datalength = 0;

        switch (packet_datatype) {
            case packet_int:
                packet_datalength = 4;
                break;

            case packet_float:
                packet_datalength = 4;
                break;

            case packet_double:
                packet_datalength = 8;
                break;
        }

        // for normal packets (+3 is to account for 
        //                      packet_start, packet_datatype, and packet_end)
        int total_packet_length = packet_datalength + 3;
        uint8_t* packet_send = new uint8_t[total_packet_length];
        packet_send[0] = packet_start;
        packet_send[1] = packet_datatype;
        packet_send[packet_datalength + 2] = packet_end;

        for (int i = 0; i < packet_datalength; i++) {
            packet_send[i + 2] = *(tx_packet + i);
        }
        
        this->serial_port.write(packet_send, total_packet_length);
        this->serial_port.sync();
        delete [] packet_send;
        ThisThread::sleep_for(2ms);
        
        return 0;
    } else {
        // serial_port does not have space to write a character
        return -1;
    }
}

int SerialPort::writeSerialSeries(uint8_t* tx_packet, int length, uint8_t packet_datatype) {
    if (this->serial_port.writable() == 1) {

        int packet_datalength = 0;

        switch (packet_datatype) {
            case packet_int:
                packet_datalength = 4;
                break;

            case packet_float:
                packet_datalength = 4;
                break;

            case packet_double:
                packet_datalength = 8;
                break;
        }

        
        uint8_t series_begin[4] = {packet_start, packet_series, 
                                                0x00, packet_end};
        series_begin[2] = packet_datatype;
        uint8_t series_end[3] = {packet_series, packet_final, packet_end};

        this->serial_port.sync();
        this->serial_port.write(series_begin, sizeof(series_begin));
        this->serial_port.sync();

        uint8_t* series_packet = new uint8_t[packet_datalength + 2];
        series_packet[0] = packet_series;
        series_packet[packet_datalength + 1] = packet_end;
        // -1 because we exclude the datatype
        for (int i = 0; i < length / packet_datalength; i++) {
            for (int j = 0; j < packet_datalength; j++) {
                series_packet[j + 1] = *(tx_packet + (i * packet_datalength) + j);
            }
            this->serial_port.write(series_packet, packet_datalength + 2);
            this->serial_port.sync();
        }
        delete [] series_packet;

        this->serial_port.write(series_end, sizeof(series_end));
        this->serial_port.sync();
        ThisThread::sleep_for(2ms);
        
        return 0;
    } else {
        // serial_port does not have space to write a character
        return -1;
    }
}

// This is to write a packet with pre defined length,
// mostly for command communications. MUST PROVIDE start and end
int SerialPort::writeSerialRaw(uint8_t* tx_packet, int length) {
    if (this->serial_port.writable() == 1) {
        
        this->serial_port.write(tx_packet, length);
        this->serial_port.sync();
        ThisThread::sleep_for(2ms);
        
        return 0;
    } else {
        // serial_port does not have space to write a character
        return -1;
    }
}

int SerialPort::readSerialPacket(vector<uint8_t> &rx_packet) {
    
}

void SerialPort::timeout() {
    this->timedout = true;
}