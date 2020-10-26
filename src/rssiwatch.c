// rssiwatch.c
// Konnor Klercke
// klercke at prototypexenon dot com
// Provides RSSI tools for ProximiC

#include "rssiwatch.h"

void watchDevice(const char* mac, int time) {
	// ensure device is connected
	connectToMAC(mac);

	int rssi;

	// run forever
	while (1) {
		// get rssi value
		rssi = getRSSI(mac);

		// check for errors
		if (rssi == -128) {
			perror("Error getting RSSI");
			exit(1);
		}

		printf("RSSI for %s: %d\n", mac, rssi);

		sleep(time);
	}
}
