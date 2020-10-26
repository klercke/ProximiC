// proximic.c
// Konnor Klercke
// klercke at prototypexenon dot com
// https://github.com/klercke/proximic

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
	if (argc < 2){
		printf("Usage: %s [args]\n", argv[0]);
		return 0;
	}

	char* cmd = argv[1];

	if (!strcmp(cmd, "-l")) {
		// list nearby devices
	
		int time = 10; // defalts to 10 sec

		if (argv[2] != NULL) {
			// allows user to overrwrite time
			time = strtol(argv[2], NULL, 10);
		}

		printf("Listing all nearby devices:\n");

		listAllDevices(time);
	}
	else if (!strcmp(cmd, "-c")) {
		// connect to device
			
		if (argv[2] == NULL) {
			printf("-c: missing address.\n");
			return 0;
		}

		int sock = connectToMAC(argv[2]);

		printf("Connected to device %s on socket %d.\n", argv[2], sock);
	}
	else if (!strcmp(cmd, "-r")) {
		// print RSSI

		if (argv[2] == NULL) {
			printf("-r: missing address.\n");
			return 0;
		}

		int sock = connectToMAC(argv[2]);

		printf("Connected to device %s on socket %d.\n", argv[2], sock);

		int rssi = getRSSI(argv[2]);

		if (rssi != -128) {
			printf("RSSI for device %s: %d.\n", argv[2], rssi);
		}
		else {
			printf("Failed to obtain RSSI value.\n");
		}
    }
	else if (!strcmp(cmd, "-w")) {
		// watch RSSI
		
		if (argv[2] == NULL) {
			printf("-w: missing address.\n");
		}
		
		double time = 1;

		if (argv[3] != NULL) {
			time = strtod(argv[3], NULL);
		}

		watchDevice(argv[2], time);
	}
	else if (!strcmp(cmd, "-h")) {
		// print help statement

		help(argv[0]);
	}
	else {
		// tell user input is invalid and print help statement
		printf("Invaild command: %s\n", cmd);
		help(argv[0]);
	}


	return 0;
}
