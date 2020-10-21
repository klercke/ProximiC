#ifndef BTSERACH_H
#define BTSEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>

void listAllDevices();

int connectToMAC(const char* mac);

int getRSSI(const char* mac, const int sock);

#endif
