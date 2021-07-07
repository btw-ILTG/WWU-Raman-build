#include "mbed.h"

static int cuvetteCounter = 0;
static bool trayOpen = false;

int openTray(int uDelay);
int closeTray(int uDelay);

// TODO: H-Bridge and Peltiers