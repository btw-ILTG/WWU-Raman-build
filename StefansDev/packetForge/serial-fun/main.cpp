#include "BufferedSerial.h"
#include "PinNames.h"
#include "ThisThread.h"
#include "UnbufferedSerial.h"
#include "mbed.h"
#include "SerialPort.h"
#include "CommandCodes.h"
#include "mbed_wait_api.h"


// Flags
#define READ_FLAG   0x1

//static DigitalOut led(LED1);

//Thread thread;
//Thread serialRead;
//Thread serialWrite;

/*
void writeThread() {
    int counter = 0;
    char write_packet[PACKET_LENGTH] = {0};
    write_packet[0] = 'S';
    write_packet[1] = 'F';
    write_packet[2] = 'D';
    write_packet[4] = 'E';
    while (true) {
        ThisThread::flags_wait_any(0x2);
        //counter++;
        //write_packet[3] = (char)counter;
        //raspi.constructPacket(write_packet);
        //raspi.writeSerialPacket();
        if (raspi.writable()) {
            raspi.write("Wow\n", 4);
        }
    }
}


void readThread() {
    char buf[RX_BUFFER_SIZE] = {0};
    while (true) {
        ThisThread::flags_wait_any(READ_FLAG);
        led = !led;
        if (raspi.readable()) {
            uint32_t num = raspi.read(buf, sizeof(buf));
            raspi.write(buf, num);
            raspi.write("\n", 1);
        }
    }
}


void dispatchThread() {
    while (true) {
        ThisThread::sleep_for(100ms);
        serialRead.flags_set(READ_FLAG);
        ThisThread::sleep_for(100ms);
        serialWrite.flags_set(0x2);
    }
}
*/

static DigitalOut led(LED1);

// main() runs in its own thread in the OS
int main() {
    //SerialPacket raspi(D8, D2, 9600);
    //thread.start(callback(dispatchThread));
    //serialRead.start(callback(readThread));
    //serialWrite.start(callback(writeThread));

    SerialPort raspi(D8, D2, 921600);
    //UnbufferedSerial unbufRaspi(D8, D2, 921600);
/*
    float number1 = -42.0;
    float number2 = -512.0;
    vector<uint8_t> test = floatToVector(&number1);
    vector<uint8_t> test2 = floatToVector(&number2);
    test.insert(std::end(test), std::begin(test2), std::end(test2));
*/  
/*
    #define ARR_TEST_SIZE 10000
    double* double_array = new double[ARR_TEST_SIZE];
    for (int i = 0; i < ARR_TEST_SIZE; i++) {
        double_array[i] = i;
    }

    raspi.writeSerialSeries((uint8_t*) double_array, sizeof(double) * ARR_TEST_SIZE, double_packet);
    delete [] double_array;
*/
/*
    #define ARR_TEST_SIZE 22000
    float* float_array = new float[ARR_TEST_SIZE];
    for (int i = 0; i < ARR_TEST_SIZE; i++) {
        float_array[i] = i;
    }

    raspi.writeSerialSeries((uint8_t*) float_array, sizeof(float) * ARR_TEST_SIZE, float_packet);
    delete [] float_array;
*/
    //vector<uint8_t> single_packet = { cmd_laser, laser_on};
    //raspi.writeSerialPacket(single_packet);
/*
    int test_int = 500;
    raspi.writeSerialPacket((uint8_t*) &test_int, packet_int);

    float test_float = 420.0;
    raspi.writeSerialPacket((uint8_t*) &test_float, packet_float);

    double test_double = 42.0;
    raspi.writeSerialPacket((uint8_t*) &test_double, packet_double);

    double test_double_array[] = {500, 420, 42, 1337};
    raspi.writeSerialSeries((uint8_t*) test_double_array, sizeof(double) * 4, packet_double);
*/

    //float float_array[2] = {42.0, 69.0};
    //vector<uint8_t> test = floatToVector(float_array, sizeof(float_array));

    

    //vector<uint8_t> testing = {'Y', 'o', 0xf3};
    //raspi.writeSerialPacket(testing);
    
    
    //vector<uint8_t> test = { uint8_t(-11), 0xF3 };
    //vector<uint8_t> test1 = {'Y', 'o', '\n'};

        
 
    //if (test_read[0] == cmd_laser) {
        //led = 1;
    //}
    //while (raspi.readSerialPacket(test_read) != 0) {
    //    ThisThread::sleep_for(2ms);
    //}
    
    //double test_double = 42.0;
    //raspi.writeSerialPacket((uint8_t*) &test_double, packet_double);

    //uint8_t* echo_back = new uint8_t[32];
    //for (int i = 0; i < 32; i++) {
    //    echo_back[i] = test_read[i];
    //}
    //ThisThread::sleep_for(1500ms);

	while (true) {
		uint8_t* test_read = nullptr;
		uint8_t data_return;

		int length = -1;
		while (length == -1 || length == 0) {
			length = raspi.readSerialPacket(&test_read, data_return);
		}
		//raspi.writeSerialPacket((uint8_t *) &length, packet_int);
		double* test_read_final = (double *) test_read;
		if (length != -1) {
			raspi.writeSerialRawRaw(test_read, length);
			//raspi.writeSerialPacket(test_read, data_return);   
		}

		delete [] test_read;
		test_read = nullptr;
	}

    return 0;
}
