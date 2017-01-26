#include <MessageID.h>
#include <MessageIdentifiers.h>
#include "../Handler.h"

#ifdef DEBUG
#include "../../Core.h"
#endif

using namespace OpenLH;

Network::Handler::Handler(RakNet::RakPeerInterface *peer, std::map<RakNet::RakNetGUID, Client*> *Clients)
    : mPeer(peer)
    , mClients(Clients)
{
    // reset all registry to nulls
    for (int i = 0; i < MO_PACKET_LIMIT; ++i) {
        mRegistry[i] = nullptr;
    }

    // connection stuff
    mRegistry[ID_NEW_INCOMING_CONNECTION]       =   &Handler::OnClientConnectAttempt;
    mRegistry[ID_CONNECTION_LOST]               =   &Handler::OnClientDisconnect;
    mRegistry[ID_DISCONNECTION_NOTIFICATION]    =   &Handler::OnClientDisconnect;
    mRegistry[MessageID::CONNECTION_INIT]       =   &Handler::OnClientConnect;

    // player stuff
    // mRegistry[MessageID::PLAYER_SYNC_ONFOOT]    =   &Handler::OnPlayerFootSync;

    // vehicle stuff
};

Network::Handler::~Handler() {};

void Network::Handler::Dispatch(RakNet::Packet* packet)
{
    RakNet::MessageID id = packet->data[0];

    if (mRegistry[id]) {
        (this->*mRegistry[id])(packet);
    }
};

void Network::Handler::OnTest(RakNet::Packet* packet)
{
#ifdef DEBUG
    Core::Instance()->Log("called OnTest");
#endif
}
