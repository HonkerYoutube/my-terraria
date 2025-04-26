#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <enet/enet.h>

using namespace std;

int main()
{
    // Initializing ENet
    if (enet_initialize() != 0) {
        cerr << "enet intialize error \n";
        return EXIT_FAILURE;
    }
    cout << "Hello CMake. \n";

    atexit(enet_deinitialize);

    // Setting up the client
    ENetHost* client;
    client = enet_host_create(NULL, 1, 1, 0, 0);
    if (client == NULL) {
        cerr << "client creation host error \n";
        return EXIT_FAILURE;
    }


    // Preparing the address and peer for connection
    ENetAddress address;
    ENetEvent event;
    ENetPeer* peer;



    enet_address_set_host(&address, "127.0.0.1");
    address.port = 7777;


    peer = enet_host_connect(client, &address, 1, 0);
    if (!peer) {
        cerr << "peer initialization error \n";
        return EXIT_FAILURE;
    }



    // Checking connection to server
    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        puts("Connection to 127.0.0.1:7777 successfully established");
    }
    else {
        enet_peer_reset(peer);
        puts("Connection to 127.0.0.1:7777 failed to establish");
        return EXIT_SUCCESS;
    }

    // Buffer for user input
    const int buffer_size = 256; // size of the buffer
    char input[buffer_size];  // C-style string to store the input




    // Main loop to send messages
    while (true) {
        // Process events
        while (enet_host_service(client, &event, 3000) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                printf("Disconnection succeeded\n");
                break;
            }
        }

        // Check if user input is available
        if (cin.peek() != EOF) {
            cin.getline(input, buffer_size);  // Get the input from the user

            // Print the input to confirm
            cout << "You entered: " << input << "\n";

            // Create ENet packet
            ENetPacket* packet = enet_packet_create(
                input,                      // Use user input directly as message
                strlen(input) + 1,          // Include null-terminator
                ENET_PACKET_FLAG_RELIABLE   // Send reliably (like TCP)
            );

            // Send packet to server
            enet_peer_send(peer, 0, packet);
            enet_host_flush(client);  // Immediately flush the packet
        }
    }

    return EXIT_SUCCESS;
}
