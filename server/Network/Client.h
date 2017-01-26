#ifndef _mo_network_client
#define _mo_network_client

#include <RakPeerInterface.h>
#include <string>

class Client
{
public:
    Client(std::string nickName, RakNet::SystemAddress systemAddress, std::string serial);
    ~Client();

    // Player* GetPlayer() { return mPlayer; }

private:
    RakNet::SystemAddress mSystemAddress;
    std::string mNickName;
    std::string mSerial;
    // Player* mPlayer;
};

#endif // _mo_network_client
