#include "mbed.h"

static int cuvetteCounter = 0;
static bool trayOpen = false;

int openTray(int uDelay = 3000);
int closeTray(int uDelay = 3000);

// TODO: H-Bridge and Peltiers