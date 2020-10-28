// proximic.c
// Konnor Klercke
// klercke at prototypexenon dot com
// https://github.com/klercke/proximic

#include <getopt.h>

#include "btsearch.h"
#include "rssiwatch.h"

void help(char* binName) {
	// Print helptext for user
	//
	// char* binName:	Name of binary used to launch ProximiC. Assumed to be
	// proximic if NULL.

	if (binName == NULL) {
		binName = "proximic";
	}

	printf("Usage: %s [OPTION]\n", binName);
	printf("\n");
	printf("-h\t\tPrint this message.\n");
	printf("-l [TIME]\tSearch for TIME seconds, or 10 seconds if TIME is not provided.\n");
	printf("-c ADDR\t\tConnect to device with address ADDR.\n");
	printf("-r ADDR\t\tConnect to device with address ADDR and print its RSSI value.\n");
	printf("-w ADDR [TIME]\tPrint RSSI value of device ADDR every TIME seconds.\n");
}

int main(int argc, char** argv) {
	int option;
	int sock, rssi;
	double time = -1;

	while ((option = getopt(argc, argv, ":ht:lc:r:w:")) != -1) {
		switch(option) {
			case 'h':
				// help

				help(argv[0]);
				break;
			case 't':
				// set time to a different value

				time = strtol(optarg, NULL, 10);
				continue;
			case 'l':
				// list nearby devices
				
				// set time if user hasn't changed it
				if (time == -1)
					time = 10;

				printf("Listing all nearby devices:\n");
				listAllDevices(time);				
				break;	
			case 'c':
				// connect

				sock = connectToMAC(optarg);
				printf("Connected to device %s on socket %d.\n", optarg, sock);
				break;
			case 'r':
				// get rssi

				sock = connectToMAC(optarg);

				printf("Connected to device %s on socket %d.\n", optarg, sock);

				rssi = getRSSI(optarg);

				if (rssi != -128) {
					printf("RSSI for device %s: %d.\n", optarg, rssi);
				}
				else {
					printf("Failed to obtain RSSI value.\n");
				}

				break;
			case 'w':
				// watch rssi of device

				if (time == -1)
					time = 1;

				watchDevice(optarg, time);
				break;
			case ':':
				// missing args

				printf("Option %c missing required argument\n", optopt);
				break;
			case '?':
				// unknown option
				
				printf("Option -%c unknown\n", optopt);
				break;
		}			
	}
	
	for(; optind < argc; optind++) {
		printf("Unexpected arguement: %s\n", argv[optind]);
	}

	return 0;
}
