#include "Manager.h"
#include "../Core.h"

const short DEFAULT_SERVER_PORT = 27010;

using namespace OpenLH;

Network::Manager::Manager()
    : mPeer   (nullptr)
    , mHandler(nullptr)
{
    mPeer       = RakNet::RakPeerInterface::GetInstance();
    mHandler    = new Network::Handler(mPeer, &mClients);
}

Network::Manager::~Manager()
{
    mPeer->Shutdown(300);
    RakNet::RakPeerInterface::DestroyInstance( mPeer );

    delete mHandler;
}

/**
 * Server intializer code
 * sets up RakNet and starts
 * all network activty
 */
void Network::Manager::Init()
{
    Core::Instance()->Log("initializing network...");

    // TODO(inlife): move to settings.json
    mSocketDescriptor = RakNet::SocketDescriptor(DEFAULT_SERVER_PORT, 0);

    int maxplayers = 16;
    std::string password = "";

    if (mPeer->Startup(maxplayers, &mSocketDescriptor, 1) != RakNet::RAKNET_STARTED) {
        Core::Instance()->Log("Unable to startup server!");
        Core::Instance()->Log("Port might be already being used by another process!");
        return;
    }

    if (password.size() > 0) {
        mPeer->SetIncomingPassword(password.c_str(), password.size());
    }

    mPeer->SetMaximumIncomingConnections(maxplayers);
    mPeer->SetTimeoutTime(2000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
}

/**
 * Regulated ticker, should be used
 * to send regular messages to all connected clients
 */
void Network::Manager::Update()
{
    // // Use a BitStream to write a custom user message
    // // Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically
    // RakNet::BitStream bsOut;
    // bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
    // bsOut.Write("Hello world");
    // mPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
}

/**
 * Idle-ticker
 * Called with very high rate, should be used
 * only to handle some light, none-blocking ops
 */
void Network::Manager::Receive()
{
    RakNet::Packet* packet = nullptr;

    if (!(packet = mPeer->Receive())) return;

    if (mHandler) {
        mHandler->Dispatch(packet);
    }

    mPeer->DeallocatePacket(packet);
}
