#ifndef _mo_game_handler_h
#define _mo_game_handler_h

namespace MOServer {
namespace Game     {

const short EVENT_LIMIT = 255;

class Handler
{
public:
    Handler();
    ~Handler();

    void Dispatch(short eventId, void* data);
private:
    void OnTest(void* data);

    void (Handler::*mRegistry[EVENT_LIMIT])(void* data);
};


} // namespace Game
} // namespace MOServer

#endif // _mo_game_handler_h
