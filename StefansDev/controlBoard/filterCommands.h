#include "mbed.h"

static int filterCounter = 0;

int filterForward(int uDelay = 3000);
int filterBackward(int uDelay = 3000);