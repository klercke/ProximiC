#ifndef RSSIWATCH_H
#define RSSIWATCH_H

#include <unistd.h>

#include "btsearch.h"

void watchDevice(const char* mac, int time);

#endif
