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
		perror("Error opening socket");
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

int connectToMAC(const char* mac) {
	int sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    struct sockaddr_rc addr = { 0 };
    int status = 0;

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 12;
    str2ba( mac, &addr.rc_bdaddr );

    // connect to server
    status = connect(sock, (struct sockaddr *)&addr, sizeof(addr));

	if (status < 0) {
		perror("Error when connecting to device");
	}

	return sock;
}

int getRSSI(const char* mac) {

	int dev_id = hci_get_route(NULL);
	int8_t rssi = -128;
	bdaddr_t bdaddr;
	struct hci_conn_info_req *cr;

	str2ba(mac, &bdaddr);

	if (dev_id < 0) {
		perror("Device not connected");
	}

	int dd = hci_open_dev(dev_id); 
	if (dd < 0) {
		perror("HCI device open failed");
	}

	cr = malloc(sizeof(*cr) + sizeof(struct hci_conn_info));
	if (cr == NULL) {
		perror("Failed to allocate memory");
	}

	bacpy(&cr->bdaddr, &bdaddr);
	cr->type = ACL_LINK;
	if (ioctl(dd, HCIGETCONNINFO, (unsigned long) cr) < 0) {
		perror("Getting connection info failed");
	}

	if (hci_read_rssi(dd, htobs(cr->conn_info->handle), &rssi, 1000) < 0) {
      	perror("RSSI read failed");
	}


	return rssi;
}
