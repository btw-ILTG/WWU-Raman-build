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
int SerialPort::writeSerialPacket(vector<uint8_t> &tx_packet) {
    if (this->serial_port.writable() == 1) {
        // use the vector like an array
        // this fixes the issue where I could not read
        // two doubles from the serial port in python
        uint8_t* write_me = &tx_packet[0];

        // for normal packets (+2 is to account for 
        //                      packet_start and packet_end)
        int total_packet_length = tx_packet.size() + 2;
        uint8_t* packet_send = new uint8_t[total_packet_length];
        packet_send[0] = packet_start;

       
        for (int i = 0; i < tx_packet.size(); i++) {
            packet_send[i + 1] = *(write_me + i);
        }
        packet_send[tx_packet.size() + 1] = packet_end;
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

int SerialPort::writeSerialSeries(uint8_t* tx_packet, int size) {
    if (this->serial_port.writable() == 1) {
        // use the vector like an array
        // this fixes the issue where I could not read
        // two doubles from the serial port in python
        uint8_t* write_me = &tx_packet[0];
        int data_length = 0;
        if (write_me[0] == packet_int || write_me[0] == packet_float) {
            data_length = 4; // 4 bytes per int or float
        } else if (write_me[0] == packet_double) {
            data_length = 8;
        }
        uint8_t series_begin[4] = {packet_start, packet_series, 
                                                0x00, packet_end};
        series_begin[2] = write_me[0];

        uint8_t series_end[3] = {packet_series, packet_final, packet_end};

        this->serial_port.write(series_begin, sizeof(series_begin));
        this->serial_port.sync();

        uint8_t* series_packet = new uint8_t[data_length + 2];
        series_packet[0] = packet_series;
        series_packet[data_length + 1] = packet_end;
        // -1 because we exclude the datatype
        for (int i = 0; i < (tx_packet.size() - 1) / data_length; i++) {
            for (int j = 0; j < data_length; j++) {
                series_packet[j + 1] = *(write_me + 1 + (i * data_length) + j);
            }
            this->serial_port.write(series_packet, data_length + 2);
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