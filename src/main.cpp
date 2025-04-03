
#include "main.h"
#include <enet/enet.h>


using namespace std;



// using this tutorial "https://www.youtube.com/watch?v=FxrKS_1zE9s"



int main()
{
	if (enet_initialize()) {
		cerr << "enet intialize error \n";
		return EXIT_FAILURE;
	}
	cout << "Hello CMake. \n";

	atexit(enet_deinitialize);

	ENetHost* client;
	//						server IP, connecting count, channel count, outcoming and incoming bandwith (2 parameters) (0 = no limit = infinite)
	client = enet_host_create(NULL, 1, 1, 0, 0);

	if (!client) {
		cerr << "client creation host error \n";
		return EXIT_FAILURE;
	}

	ENetAddress address;
	ENetEvent event;  // all event that we are receiving from the server
	ENetPeer* peer;  // the device that is connected to the server


	//					   adress, IP (local)
	enet_address_set_host(&address, "127.0.0.1");
	address.port = 7777;

	//						client,	  address,  channels count, any data that we want to send right away
	peer = enet_host_connect(client, &address, 1, 0);
	if (!peer) {
		cerr << "peer initializion error \n";
		return EXIT_FAILURE;
	}

	// this function allows us to see events received from the server
	if (enet_host_service(client, &event, 5000) > 0 &&  // client, reference to the event, amount of milisecond we want to wait to see if we received anything
		event.type == ENET_EVENT_TYPE_CONNECT)
	{
		puts("connection to 127.0.0.1:7777 successfully established");
	}
	else {
		enet_peer_reset(peer);
		puts("connection to 127.0.0.1:7777 failed to established");
		return EXIT_SUCCESS;
	}



	while (enet_host_service(client, &event, 1000) > 0) {
		switch (event.type) {
		case ENET_EVENT_TYPE_RECEIVE:

		}
	}



	delete client;
}
