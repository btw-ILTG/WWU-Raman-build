/*MAIN controlboard program*/

#include "mbed.h"
#include "DS18B20.h"
#include "OneWireDefs.h"

#define THERMOMETER DS18B20
#define packet_start    0xF0
#define packet_flag     0xF2
#define packet_end      0xF3

#define cmd_laser       0xA0
#define laser_on        0xA1
#define laser_off       0xA2
#define shutter_open    0xA3
#define shutter_close   0xA4
#define laser_temp      0xA5

#define cmd_cuvette     0xB0
#define tray_open       0xB1
#define tray_close      0xB2
#define tray_heat       0xB3
#define tray_cool       0xB4
#define tray_temp       0xB5

#define cmd_filter      0xC0
#define filter_open     0xC1
#define filter_forward  0xC2
#define filter_back     0xC3

#define cmd_ccd_pelt    0xD0
#define ccd_heat        0xD1
#define ccd_cool        0xD2

Serial raspi(USBTX, USBRX, 921600);
DigitalOut grnLED(LED1);
DigitalOut relay(PA_1); //laser relay pin
DigitalOut cuvette_IN1(PA_4); //tray motor pins
DigitalOut cuvette_IN2(PB_0);
DigitalOut cuvette_IN3(PC_1);
DigitalOut cuvette_IN4(PC_0);
DigitalOut filter_IN1(PC_14); //filter selector motor pins
DigitalOut filter_IN2(PC_15);
DigitalOut filter_IN3(PH_0);
DigitalOut filter_IN4(PH_1);
PwmOut cuvettePeltA(PB_13); //peltier for tray
PwmOut cuvettePeltB(PB_14);
PwmOut ccdPeltA(PB_15); //peltier for CCD
PwmOut ccdPeltB(PB_5);
PwmOut servo(PA_11); //laser shutter control

THERMOMETER device(PC_8);

bool trayOpen;
float temp;
const int mDelay = 3;
int filterPosition;
int z = 0; //counter for filter motor
int y = 0; //counter for cuvette motor


void readTemp(int deviceNum){
    temp = device.readTemperature(deviceNum);
    if (deviceNum == 0) {
        raspi.printf("Cuvette Temp: %.3f degrees Celsius.\n", temp);
    }
    if (deviceNum == 1) {
        raspi.printf("Laser Temp: %.3f degrees Celsius.\n", temp);
    }
}

int laserPower(int on) {
    if (on == 1) {//turn laser on
        relay = 0;
        //grnLED = 1;
    }
    if (on == 0) {//turn laser off
        relay = 1;
        //grnLED = 0;
    }
}

int filterForward() {
    while (z < 514) {
        z++;
        //grnLED = 0;

        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 1;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 1;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 1;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        wait_ms(mDelay);

        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        wait_ms(mDelay);
    }
    filter_IN1 = 0;
    filter_IN2 = 0;
    filter_IN3 = 0;
    filter_IN4 = 0;
    z = 0;
    return(0);
}

int filterBack() {
    while (z < 514) {
        z++;
        //grnLED = 1;

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 1;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 0;
        filter_IN3 = 1;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 1;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 0;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 1;
        filter_IN2 = 1;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 0;
        wait_ms(mDelay);

        filter_IN1 = 1;
        filter_IN2 = 0;
        filter_IN3 = 0;
        filter_IN4 = 1;
        wait_ms(mDelay);
    }
    filter_IN1 = 0;
    filter_IN2 = 0;
    filter_IN3 = 0;
    filter_IN4 = 0;
    z = 0;
    return(0);
}

int openTray() {
    while (y < 500) {
        y++;
        //grnLED = 1;

        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_ms(mDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 1;
        wait_ms(mDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_ms(mDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_ms(mDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_ms(mDelay);

        cuvette_IN1 = 1;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_ms(mDelay);

        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_ms(mDelay);

        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_ms(mDelay);
    }
    cuvette_IN1 = 0;
    cuvette_IN2 = 0;
    cuvette_IN3 = 0;
    cuvette_IN4 = 0;
    y = 0;
    trayOpen = true;
    return(0);

}

int closeTray() {
    while (y < 500) {
        y++;
        //grnLED = 0;

        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_ms(mDelay);

        cuvette_IN1 = 1;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_ms(mDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 0;
        cuvette_IN4 = 0;
        wait_ms(mDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 1;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_ms(mDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 0;
        wait_ms(mDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 1;
        cuvette_IN4 = 1;
        wait_ms(mDelay);

        cuvette_IN1 = 0;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_ms(mDelay);

        cuvette_IN1 = 1;
        cuvette_IN2 = 0;
        cuvette_IN3 = 0;
        cuvette_IN4 = 1;
        wait_ms(mDelay);
    }
    cuvette_IN1 = 0;
    cuvette_IN2 = 0;
    cuvette_IN3 = 0;
    cuvette_IN4 = 0;
    y = 0;
    trayOpen = false;
    return(0);
}

int main() {
    laserPower(0); //making sure laser is not on until told
    int packetFlag = 0;
    raspi.baud(921600);
    device.initialize(); //initialize temp sensors
    int deviceCount = device.getDeviceCount(); //count number of temp sensors
    device.setResolution(twelveBit); //set temp sensor resolution

    servo.period_ms(20); //set shutter servo period
    cuvettePeltA.period_ms(5); //set peltier period and pulsewidth
    cuvettePeltA.pulsewidth_ms(1);
    cuvettePeltB.period_ms(5);
    cuvettePeltB.pulsewidth_ms(1);
    ccdPeltA.period_ms(5);
    ccdPeltA.pulsewidth_ms(1);
    ccdPeltB.period_ms(5);
    ccdPeltB.pulsewidth_ms(1);

    while (1) {
        if (raspi.readable()) {
            switch (raspi.getc()) {
                case packet_start:
                    switch (raspi.getc()) {
                        case packet_flag:
                            packetFlag = 1;
                            while (packetFlag == 1) {
                                switch (raspi.getc()) {
                                    case cmd_laser:
                                        switch (raspi.getc()) {
                                            case laser_on:
                                                raspi.printf("Laser on and shutter opened.\n");
                                                laserPower(1); //turn laser on
                                                servo.pulsewidth_us(600); //opens shutter
                                                continue;
                                            case laser_off:
                                                raspi.printf("Laser off.\n");
                                                laserPower(0); //turns laser off
                                                continue;
                                            case shutter_open:
                                                raspi.printf("Opening shutter.\n");
                                                servo.pulsewidth_us(600);
                                                continue;
                                            case shutter_close:
                                                raspi.printf("Closing shutter.\n");
                                                servo.pulsewidth_us(1500); //closes shutter
                                                continue;
                                            case laser_temp:
                                                readTemp(1);
                                                continue;
                                            default:
                                                break;
                                        }
                                    case cmd_cuvette:
                                        switch (raspi.getc()) {
                                            case tray_open:
                                                if (trayOpen == true) { //don't open the tray if its already open
                                                    raspi.printf("Tray is open.\n");
                                                }
                                                else if (trayOpen == false) {
                                                    raspi.printf("Opening tray.\n"); 
                                                    openTray();
                                                }
                                                else {
                                                    raspi.printf("error\n");
                                                }
                                                continue;
                                            case tray_close:
                                                if (trayOpen == false) { //don't close the tray if it's already closed
                                                    raspi.printf("Tray is closed.\n");
                                                }
                                                else if (trayOpen == true) {
                                                    raspi.printf("Closing tray.\n"); 
                                                    closeTray();            
                                                }
                                                else {
                                                    raspi.printf("error\n");
                                                }
                                                continue;
                                            case tray_heat:
                                                raspi.printf("Heating tray sample.\n");
                                                cuvettePeltA = 0.25;
                                                cuvettePeltB = 0;
                                                wait(5);
                                                cuvettePeltA = 0;
                                                continue;
                                            case tray_cool:
                                                raspi.printf("Cooling tray sample.\n");
                                                cuvettePeltA = 0;
                                                cuvettePeltB = 0.25;    
                                                wait(5);
                                                cuvettePeltB = 0;
                                                continue;
                                            case tray_temp:
                                                readTemp(0);
                                                continue;
                                            default:
                                                break;
                                        }
                                    case cmd_filter:
                                        switch (raspi.getc()) {
                                            case filter_forward:
                                                raspi.printf("Changing filter forward.\n");
                                                filterForward();
                                                continue;
                                            case filter_back:
                                                raspi.printf("Changing filter back.\n");
                                                filterBack();
                                                continue;
                                        }
                                    case cmd_ccd_pelt:
                                        switch (raspi.getc()) {
                                            case ccd_heat:
                                                raspi.printf("Heating CCD.\n");
                                                ccdPeltA = 0.25;
                                                ccdPeltB = 0;
                                                wait(5);
                                                ccdPeltA = 0;
                                                continue;
                                            case ccd_cool:
                                                raspi.printf("Cooling CCD.\n");
                                                ccdPeltA = 0;
                                                ccdPeltB = 0.25;                        
                                                wait(5);
                                                ccdPeltB = 0;
                                                continue;
                                            default:
                                                break;
                                        }
                                    case packet_end:
                                        packetFlag = 0;
                                        raspi.printf("Packet end found.\n");
                                        break;
                                    default:
                                        break;
                                }
                            }
                        default:
                            break;

                    }
                default:
                    grnLED = 1;
                    break;
            }
        }
    }
}
