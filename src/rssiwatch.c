// rssiwatch.c
// Konnor Klercke
// klercke at prototypexenon dot com
// Provides RSSI tools for ProximiC

#include "rssiwatch.h"

void watchDevice(const char* mac, int time) {
	connectToMAC(mac);

	int rssi;

	while (1) {
		rssi = getRSSI(mac);

		if (rssi == -128) {
			perror("Error getting RSSI");
			exit(1);
		}

		printf("RSSI for %s: %d\n", mac, rssi);

		sleep(time);
	}
}
