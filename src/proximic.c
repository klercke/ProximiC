// proximic.c
// Konnor Klercke
// klercke at prototypexenon dot com
// https://github.com/klercke/proximic

#include "btsearch.h"

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
