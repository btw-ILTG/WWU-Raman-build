#include "BufferedSerial.h"
#include "PinNames.h"
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

vector<uint8_t> doubleToVector(double* double_convert) {
    uint8_t* double_convert_pointer = (uint8_t *) double_convert; 
    vector<uint8_t> vector_double(double_convert_pointer, double_convert_pointer + sizeof(double));
    return vector_double;
}

vector<uint8_t> doubleToVector(double* double_convert, int size) {
    uint8_t* double_convert_pointer = (uint8_t *) double_convert; 
    vector<uint8_t> vector_double(double_convert_pointer, double_convert_pointer + size);
    return vector_double;
}

vector<uint8_t> floatToVector(float* float_convert) {
    uint8_t* float_convert_pointer = (uint8_t *) float_convert; 
    vector<uint8_t> vector_float(float_convert_pointer, float_convert_pointer + sizeof(float));
    return vector_float;
}

vector<uint8_t> floatToVector(float* float_convert, int size) {
    uint8_t* float_convert_pointer = (uint8_t *) float_convert; 
    vector<uint8_t> vector_float(float_convert_pointer, float_convert_pointer + size);
    return vector_float;
}

vector<uint8_t> intToVector(int* int_convert) {
    uint8_t* int_convert_pointer = (uint8_t *) int_convert; 
    vector<uint8_t> vector_int(int_convert_pointer, int_convert_pointer + sizeof(int));
    return vector_int;
}

vector<uint8_t> intToVector(int* int_convert, int size) {
    uint8_t* int_convert_pointer = (uint8_t *) int_convert; 
    vector<uint8_t> vector_int(int_convert_pointer, int_convert_pointer + size);
    return vector_int;
}

// main() runs in its own thread in the OS
int main() {
    //SerialPacket raspi(D8, D2, 9600);
    //thread.start(callback(dispatchThread));
    //serialRead.start(callback(readThread));
    //serialWrite.start(callback(writeThread));

    SerialPort raspi(D8, D2, 9600);
/*
    float number1 = -42.0;
    float number2 = -512.0;
    vector<uint8_t> test = floatToVector(&number1);
    vector<uint8_t> test2 = floatToVector(&number2);
    test.insert(std::end(test), std::begin(test2), std::end(test2));
*/  

    #define ARR_TEST_SIZE 350
    double double_array[ARR_TEST_SIZE];
    for (int i = 0; i < ARR_TEST_SIZE; i++) {
        double_array[i] = i;
    }
    vector<uint8_t> test = doubleToVector(double_array, sizeof(double_array));
    test.insert(test.begin(), packet_double);
    raspi.writeSerialSeries(test);


    //vector<uint8_t> single_packet = { cmd_laser, laser_on};
    //raspi.writeSerialPacket(single_packet);
/*
    int test_int = 500;
    vector<uint8_t> test_int_packet = intToVector(&test_int);
    test_int_packet.insert(test_int_packet.begin(), packet_int);
    raspi.writeSerialPacket(test_int_packet);

    float test_float = 420.0;
    vector<uint8_t> test_float_packet = floatToVector(&test_float);
    test_float_packet.insert(test_float_packet.begin(), packet_float);
    raspi.writeSerialPacket(test_float_packet);

    double test_double = 42.0;
    vector<uint8_t> test_double_packet = doubleToVector(&test_double);
    test_double_packet.insert(test_double_packet.begin(), packet_double);
    raspi.writeSerialPacket(test_double_packet);

    double test_double_array[] = {500, 420, 42, 1337};
    vector<uint8_t> test_series_double = doubleToVector(test_double_array, sizeof(test_double_array));
    test_series_double.insert(test_series_double.begin(), packet_double);
    raspi.writeSerialSeries(test_series_double);
*/

    //float float_array[2] = {42.0, 69.0};
    //vector<uint8_t> test = floatToVector(float_array, sizeof(float_array));

    

    //vector<uint8_t> testing = {'Y', 'o', 0xf3};
    //raspi.writeSerialPacket(testing);
    
    
    //vector<uint8_t> test = { uint8_t(-11), 0xF3 };
    //vector<uint8_t> test1 = {'Y', 'o', '\n'};

    //vector<uint8_t> test_read;
    //volatile int status;
    //status = raspi.readSerialPacket(test_read);    
    
    //while (raspi.readSerialPacket(test_read) == -1) {
        //ThisThread::sleep_for(11ms);
    //}

    //raspi.writeSerialPacket(test);
    //raspi.writeSerialPacket(test_read);

    return 0;
}