#include "mbed.h"

// TODO: H-Bridge and Peltiers

enum CuvetteState {cuv_open, cuv_closed};

class Cuvette {
    private:
        DigitalOut cuvette_IN1; 
        DigitalOut cuvette_IN2;
        DigitalOut cuvette_IN3;
        DigitalOut cuvette_IN4;
    
        CuvetteState cuvette_state;
        int cuvette_limit;

    public:
        // in case the cuvette is actually open at initialization
        // the initial state can be set as to not break things
        Cuvette(DigitalOut cuvette_IN1, DigitalOut cuvette_IN2, 
                DigitalOut cuvette_IN3, DigitalOut cuvette_IN4,
                CuvetteState initial = cuv_closed, int cuvette_limit = 500);
        int openTray(int msDelay = 3);
        int closeTray(int msDelay = 3);
        CuvetteState getCuvetteState() { return this->cuvette_state; }
        float getCuvetteTemperature();
};