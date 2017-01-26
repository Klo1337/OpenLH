#include "Client.h"

Client::Client(std::string nickName, RakNet::SystemAddress systemAddress, std::string serial)
    : mNickName(nickName)
    , mSystemAddress(systemAddress)
    , mSerial(serial)
{
    // some additional data
}

Client::~Client()
{

}
