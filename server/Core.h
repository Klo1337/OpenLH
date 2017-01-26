#ifndef _mo_core
#define _mo_core

#include <Utils.h>
#include "Network/Manager.h"
#include "Game/Manager.h"

namespace MOServer {

class Core
{
private:
    static Core* mInstance;
    bool mRunning;

    Network::Manager* mNetworkManager;
    Game::Manager* mGameManager;

public:
    Core();
    ~Core();

    void Init();
    void Idle();
    void Tick(int64_t tick);
    static void Log(const char* format, ...);

    /**
     * Return current isntance of the core
     * @return Core*
     */
    static Core* Instance()
    {
        return mInstance;
    }

    static Game::Manager* Game()
    {
        return mInstance->mGameManager;
    }

    /**
     * Return if core is currently running
     * @return bool
     */
    bool IsRunning()
    {
        return mRunning;
    }
};


} // namespace MOServer


#endif // _mo_core
