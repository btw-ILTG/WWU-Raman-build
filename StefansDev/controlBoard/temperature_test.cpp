#include "mbed.h"
#include "DS18B20.h"
#include "OneWireDefs.h"

#define hello 0xF0
#define THERMOMETER DS18B20

THERMOMETER device(PC_8);
BufferedSerial raspi(D8, D2);
DigitalOut grnled(LED1);

float temp;

void readTemp(int deviceNum)
{
   temp = device.readTemperature(deviceNum);
    if(deviceNum == 0){
        printf("Cuvette Temp: %.3f degrees Celsius.\n", temp);
    }
    if(deviceNum == 1){
        printf("Laser Temp: %.3f degrees Celsius.\n", temp);
    }
}

FileHandle *mbed::mbed_override_console(int fd) {
    return &raspi;
}



int main(){
    raspi.set_baud(9600);
    raspi.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );
    wait_us(2000000);       // DO NOT PUT ANYTHING IN BETWEEN THESE LINES!!
    device.initialize();    // I don't know why but it won't recognize devices if you do
    printf("Initialized\n");
    int deviceCount = device.getDeviceCount();
    
    device.setResolution(twelveBit);
    while(1){
        if(raspi.readable()==1){ 
            grnled = 1;
            switch (deviceCount){
                case 0:
                    printf("deviceCount is zero.\n");
                    continue;
                case 1:
                    printf("deviceCount is one.\n");
                    continue;
                case 2:
                    printf("deviceCount is two.\n");
                    readTemp(0);
                    wait_us(1000000);
                    readTemp(1);
                    continue;
                default:
                    printf("deviceCount is something else.\n");
                    break;    
            }    
        }
        else{
            continue;
        }
    }
}
