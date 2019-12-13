#include "mbed.h"

PwmOut cuvettePeltA(PB_13);
PwmOut cuvettePeltB(PB_14);
PwmOut ccdPeltA (PB_15);
PwmOut ccdPeltB (PB_5);

DigitalOut led(LED1);
int main(){
cuvettePeltA.period_ms(5);
cuvettePeltA.pulsewidth_ms(1);
cuvettePeltB.period_ms(5);
cuvettePeltB.pulsewidth_ms(1);
ccdPeltA.period_ms(5);
ccdPeltA.pulsewidth_ms(1);
ccdPeltB.period_ms(5);
ccdPeltB.pulsewidth_ms(1);

    while(1){
                    cuvettePeltA = 0;
                    cuvettePeltB = 0;
                    ccdPeltA = 0;
                    ccdPeltB = 0;
                    wait(5);
                    cuvettePeltA = 0.25;
                    cuvettePeltB = 0;
                    ccdPeltA = 0;
                    ccdPeltB = 0.25;
                    wait(5);
        }
}