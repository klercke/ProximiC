#include "btsearch.h"

int main(int argc, char** argv) {
	if (argc < 2){
		printf("Usage: %s [args]\n", argv[0]);
		return 0;
	}

	char* cmd = argv[1];

	if(!strcmp(cmd, "-l")) {
		// list nearby devices
	
		int time = 10; // defalts to 10 sec

		if (argv[2] != NULL) {
			// allows user to overrwrite time
			time = strtol(argv[2], NULL, 10);
		}

		printf("Listing all nearby devices:\n");

		listAllDevices(time);
	}
	else {
		printf("Invaild command: %s\n", cmd);
	}


	return 0;
}
