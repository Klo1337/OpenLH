#include <stdio.h>
#include <string.h>
#include <iostream>
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>
#include <RakNetTypes.h>  // MessageID
#include <BuildVersion.h>
#include <MessageID.h>

#define SERVER_PORT 27010

int main(void)
{
    std::string ipAddress;

    RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
    RakNet::Packet *packet;

    RakNet::SocketDescriptor sd;
    peer->Startup(1,&sd, 1);

    printf("Enter server IP or any letter and enter for 127.0.0.1\n");
    std::cin >> ipAddress;

    if (ipAddress.size() == 1) {
        // strcpy(ipAddress, "127.0.0.1");
        ipAddress = "127.0.0.1";
    }

    printf("Connecting to %s:%d...\n", ipAddress.c_str(), SERVER_PORT);
    peer->Connect(ipAddress.c_str(), SERVER_PORT, 0,0);


    while (1)
    {
        for (packet=peer->Receive(); packet; peer->DeallocatePacket(packet), packet=peer->Receive())
        {
            switch (packet->data[0])
            {
            case ID_REMOTE_DISCONNECTION_NOTIFICATION:
                printf("Another client has disconnected.\n");
                break;
            case ID_REMOTE_CONNECTION_LOST:
                printf("Another client has lost the connection.\n");
                break;
            case ID_REMOTE_NEW_INCOMING_CONNECTION:
                printf("Another client has connected.\n");
                break;
            case ID_NEW_INCOMING_CONNECTION:
                printf("A connection is incoming.\n");
                break;
            case ID_NO_FREE_INCOMING_CONNECTIONS:
                printf("The server is full.\n");
                break;
            case ID_DISCONNECTION_NOTIFICATION:
                printf("We have been disconnected.\n");
                break;
            case ID_CONNECTION_LOST:
                printf("Connection lost.\n");
                break;


            case ID_CONNECTION_REQUEST_ACCEPTED:
                {
                    printf("Our connection request has been accepted.\n");
                    printf("Sending OnClientConnect packet\n");

                    /**
                     * This data-packet is used to validate
                     * game mod compability, and add client to server list
                     *
                     * Data template
                     * @param int MOSERVER_PROTOCOL_VERSION
                     * @param int MOSERVER_BUILD_VERSION
                     * @param string Client Name
                     */
                    RakNet::BitStream data;
                    data.Write((RakNet::MessageID)MessageID::CONNECTION_INIT);
                    data.Write(MO_PLATFORM_ID);
                    data.Write(MO_PROTOCOL_VERSION);
                    data.Write(MO_BUILD_VERSION);
                    data.Write("Test Player");
                    data.Write("4555ASDASD4555ASDASD4555");

                    peer->Send(&data, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
                }
                break;

            case MessageID::CONNECTION_ACCEPTED:
                {
                    printf("Successfuly connected to server.\n");
                }
                break;

            default:
                printf("Message with identifier %i has arrived.\n", packet->data[0]);
                break;
            }
        }
    }


    RakNet::RakPeerInterface::DestroyInstance(peer);

    return 0;
}
