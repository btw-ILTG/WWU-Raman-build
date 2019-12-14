#include "mbed.h"
#include "DS18B20.h"
#include "OneWireDefs.h"

#define hello 0xF0
#define THERMOMETER DS18B20

THERMOMETER device(PC_8);
Serial raspi(USBTX, USBRX);
DigitalOut grnled(LED1);

float temp;

void readTemp(int deviceNum)
{
   temp = device.readTemperature(deviceNum);
    if(deviceNum == 0){
        raspi.printf("Cuvette Temp: %.3f degrees Celsius.\n", temp);
    }
    if(deviceNum == 1){
        raspi.printf("Laser Temp: %.3f degrees Celsius.\n", temp);
    }
}

int main(){
    raspi.baud(9600);
    wait(2);
    device.initialize();
    int deviceCount = device.getDeviceCount();
    
    device.setResolution(twelveBit);
    while(1){
        if(raspi.readable()==1){ 
            grnled = 1;
            switch (deviceCount){
                case 0:
                    raspi.printf("deviceCount is zero.\n");
                    continue;
                case 1:
                    raspi.printf("deviceCount is one.\n");
                    continue;
                case 2:
                    raspi.printf("deviceCount is two.\n");
                    readTemp(0);
                    wait(1);
                    readTemp(1);
                    continue;
                default:
                    raspi.printf("deviceCount is something else.\n");
                    break;    
            }    
        }
        else{
            continue;
        }
    }
}
