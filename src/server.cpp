#include <iostream>
#include <enet/enet.h>


using namespace std;


int main() {

	#pragma region initializing enet

	if (enet_initialize() != 0) {
		cerr << "enet intialize error \n";
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);


	ENetAddress address;
	ENetEvent event;
	ENetHost* server;

	address.host = ENET_HOST_ANY;
	address.port = 7777;

	//						   address, amount of peers, amount of channels, ingoing and outgoing bandwith limit (2 parameters)
	server = enet_host_create(&address, 32, 1, 0, 0);

	if (server == NULL) {
		cerr << "server creation error \n";
		return EXIT_FAILURE;
	}

	printf("server \n");

	#pragma endregion



	#pragma region main loop

	while (true) {


		while (enet_host_service(server, &event, 1000) > 0) {

			char* char_data = nullptr;

			switch (event.type) {
			case ENET_EVENT_TYPE_CONNECT:
				printf("new client connected from %x:%u \n", 
					   event.peer->address.host,
					   event.peer->address.port);
				break;



			case ENET_EVENT_TYPE_RECEIVE:
				char_data = (char*)event.packet->data;

				if (strcmp(char_data, "<ping>") == 1) {
					printf("%x:%u sent '%s' \n", event.peer->address.host, event.peer->address.port, event.packet->data);

				}

				if (strcmp(char_data, "<ping>") == 0) {
					// Respond to keep connection alive
					const char* pong = "<pong>";
					ENetPacket* response = enet_packet_create(
						pong,
						strlen(pong) + 1,
						ENET_PACKET_FLAG_RELIABLE
					);
					enet_peer_send(event.peer, 0, response);
					enet_host_flush(server); // force send immediately
				}


				if (strcmp(char_data, "/exit") == 0) {
					enet_peer_disconnect(event.peer, 0);
				}

				enet_packet_destroy(event.packet);
				break;



			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%x:%u disconnected \n",
						event.peer->address.host,
						event.peer->address.port);
				break;

			}
		}



	}


	#pragma endregion

	enet_peer_disconnect(server->peers, 0);

	enet_host_destroy(server);


	return EXIT_SUCCESS;

}