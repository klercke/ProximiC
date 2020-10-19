// btsearch.c
// Konnor Klercke
// klercke at prototypexenon dot com
// Provides Bluetooth search functionality for ProximiC

#include "btsearch.h"

void listAllDevices(int time) {
	// Original code adapted from Albert Huang:
	// https://people.csail.mit.edu/albert/bluez-intro/c404.html
	// 
	// Prints a list of all devices eligible for pairing to stdout
	// 
	// int time:	Number of seconds to search for devices
	
	inquiry_info *ii = NULL;
	int max_rsp, num_rsp;
	int dev_id, sock;
	int i;
	int flags = IREQ_CACHE_FLUSH;
	char addr[19] = {0};
	char name[248] = {0};

	dev_id = hci_get_route(NULL);
	sock = hci_open_dev(dev_id);
	if (dev_id < 0 || sock < 0) {
		perror("opening socket");
		exit(1);
	}

	max_rsp = 255;
	ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));

	num_rsp = hci_inquiry(dev_id, time, max_rsp, NULL, &ii, flags);
	if (num_rsp < 0) {
		perror("hci_inquiry");
	}

	for (i = 0; i < num_rsp; i++) {
		ba2str(&(ii+i)->bdaddr, addr);
		memset(name, 0, sizeof(name));
		if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name),
								name, 0) < 0) {
			strcpy(name, "[unknown]");
		}
		printf("Found device %s\t%s\n", addr, name);
	}

	if (num_rsp < 1) {
		printf("No devices found after %d seconds.\n", time);
	}

	free(ii);
	close(sock);
}
