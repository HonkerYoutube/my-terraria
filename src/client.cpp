#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdint>  // for uint32_t
#include <enet/enet.h>
#include <SFML/Graphics.hpp>
#include "UI utility.hpp"
#include "game_data.hpp"

using namespace std;


unsigned int window_width = 1200, window_height = 800;


bool should_connect_to_server = false;



int main()
{


    #pragma region initializing enet

    // Initializing ENet
    if (enet_initialize() != 0) {
        cerr << "enet intialize error \n";
        return EXIT_FAILURE;
    }
    printf("client \n");

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


    if (should_connect_to_server) {

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

    }



    #pragma endregion



    #pragma region initializing sfml

    sf::RenderWindow window(sf::VideoMode({ window_width, window_height }, 32), "my terraria");

    #pragma endregion




    #pragma region initializing variables used in main loop

    uint32_t lastPingTime = enet_time_get();
    const uint32_t pingInterval = 3000; // milliseconds

    #pragma endregion




    #pragma region initializing start screen

    sf::RectangleShape start_screen_background(sf::Vector2f(window_width, window_height));
    start_screen_background.setFillColor(sf::Color::Green);

    myUI::button singleplayerButton(sf::Vector2f(200, 75), sf::Vector2f(window_width / 2 - 100, window_height / 2 - 75), game_data::font, "singleplayer");

    sf::Text start_screen_title(game_data::font, "My Terraria", 40);
    start_screen_title.setPosition(sf::Vector2f(window_width / 2 - start_screen_title.getCharacterSize() * 4, window_height / 2 - 25 - 250));

    #pragma endregion




    #pragma region main loop


    // Main loop to send messages
    while (true) {


        #pragma region server things

        if (should_connect_to_server) {

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



            uint32_t now = enet_time_get();
            if (now - lastPingTime >= pingInterval) {
                const char* pingMessage = "<ping>";
                ENetPacket* pingPacket = enet_packet_create(pingMessage, strlen(pingMessage) + 1, ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(peer, 0, pingPacket);
                enet_host_flush(client);
                //printf("Sent <ping>\n");  // <-- Add this
                lastPingTime = now;
            }
        }

        #pragma endregion




        #pragma region event checker

        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return 0;
            }

        }


        // get the current mouse position in the window
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

        // convert it to world coordinates
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);


        if (singleplayerButton.isMouseOver(worldPos)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                //printf("here \n");
                game_data::in_game = true;
            }
                

        }



        #pragma endregion




        #pragma region drawing

        window.clear();

        if (!game_data::in_game) {

            window.draw(start_screen_background);
            singleplayerButton.draw(window);
            window.draw(start_screen_title);
        }


        window.display();


        #pragma endregion



    }

    #pragma endregion

    return EXIT_SUCCESS;
}
