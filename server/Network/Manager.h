#ifndef _mo_network_manager
#define _mo_network_manager

#include <map>
#include <RakPeerInterface.h>
#include "Client.h"
#include "Handler.h"

namespace OpenLH {
namespace Network  {


class Manager
{
public:
    Manager();
    ~Manager();
    void Init();
    void Tick();

    void Update();
    void Receive();

    RakNet::RakPeerInterface* GetPeer() { return mPeer; }

private:
    RakNet::RakPeerInterface* mPeer;
    RakNet::SocketDescriptor mSocketDescriptor;
    std::map<RakNet::RakNetGUID, Client*> mClients;
    Network::Handler* mHandler;
};


} // Netwrok
} // OpenLH

#endif // _mo_network_manager
