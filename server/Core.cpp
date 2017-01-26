#include "Core.h"

using namespace MOServer;

Core* Core::mInstance;

Core::Core()
    : mRunning(false)
    , mNetworkManager(nullptr)
    , mGameManager(nullptr)
{
    this->Init();
}

Core::~Core()
{
    delete mNetworkManager; mNetworkManager = nullptr;
    delete mGameManager; mGameManager = nullptr;

    this->Log("exiting...");
}

void Core::Log(const char* format, ...)
{
    va_list ap;
    char message[1024] = { 0 };
    va_start(ap, format);
    vsprintf(message, format, ap);
    va_end(ap);

    // TODO(inlife): move to async trigger -> callback
    printf("[SERVER] [%s] - %s\n", Utils::currentDateTime().c_str(), message);
}

/**
 * Main initialzing function
 */
void Core::Init()
{
    std::string test = "";

    test.append("==================================================\n");
    test.append("==                                              ==\n");
    test.append("==                 ¯\\_(ツ)_/¯                   ==\n");
    test.append("==                                              ==\n");
    test.append("==================================================\n");

    printf("%s\n\n", test.c_str());

    mNetworkManager = new Network::Manager();
    mNetworkManager->Init();

    mGameManager = new Game::Manager();
    mGameManager->Init();

    mRunning  = true;
    mInstance = this;
}

/**
 * Main ticker function
 */
void Core::Tick(int64_t tick)
{
    // this->Log("tick tock: %d", tick);
    if (mNetworkManager) {
        mNetworkManager->Update();
    }
}

/**
 * Main idle function
 */
void Core::Idle()
{
    if (mNetworkManager) {
        mNetworkManager->Receive();
    }
    // this->Log("idle...");
}
