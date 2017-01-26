#ifndef _mo_message_id
#define _mo_message_id

#include "MessageIdentifiers.h"

namespace MessageID
{
    enum MainIDS {
        CONNECTION_INIT = ID_USER_PACKET_ENUM + 1,
        CONNECTION_REFUSED,
        CONNECTION_ACCEPTED,
        CONNECTION_DISCONNECTED,
        PLAYER_SYNC_ONFOOT,
        PLAYER_EVENT_CREATE,
    };
};

#endif // _mo_message_id
