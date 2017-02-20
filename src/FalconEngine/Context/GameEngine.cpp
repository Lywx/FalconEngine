#include <FalconEngine/Context/GameEngine.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngine::GameEngine(Game *game)
    : mGame(game)
{
    mGame->SetEngine(this);
}

GameEngine::GameEngine(const GameEngine& rhs)
    : mGame(rhs.mGame)
{
}

GameEngine& GameEngine::operator=(const GameEngine& rhs)
{
    mGame = rhs.mGame;
    return *this;
}

GameEngine::GameEngine(GameEngine&& rhs) noexcept
    : mGame(rhs.mGame)
{
    rhs.mGame = nullptr;
}

GameEngine& GameEngine::operator=(GameEngine&& rhs) noexcept
{
    if (this != &rhs)
    {
        mGame = rhs.mGame;
        rhs.mGame = nullptr;
    }

    return *this;
}

GameEngine::~GameEngine()
{
    mGame = nullptr;
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEngine::Run()
{
    if (!mInitialized)
    {
        Initialize();
    }

    Loop();
    Exit();
}

void
GameEngine::Shutdown()
{
    mRunning = false;
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
GameEngine::Initialize()
{
    if(mGame != nullptr)
    {
        mGame->Initialize();
    }

    mInitialized = true;
}

void
GameEngine::Loop()
{
    Counter = GameCounter();
    char lastFramePerformanceString[256];

    if (mGame != nullptr)
    {
        double lastFrameBegunMillisecond = Counter.GetMilliseconds();
        double lastRenderBegunMillisecond = lastFrameBegunMillisecond;
        int    lastUpdateTotalCount = 0;

        // First update has no previous elapsed time
        double lastUpdateElapsedMillisecond = 0;

        while (mRunning)
        {
            double lastFrameEndedMillisecond = Counter.GetMilliseconds();
            double lastRenderEndedMillisecond = lastFrameEndedMillisecond;

            // Get the time elapsed during the LAST frame.
            double lastFrameElapsedMillisecond = lastFrameEndedMillisecond - lastFrameBegunMillisecond;
            double lastRenderElapsedMillisecond = lastRenderEndedMillisecond - lastRenderBegunMillisecond;

            // Reset frame start point.
            lastFrameBegunMillisecond = lastFrameEndedMillisecond;

            mGame->UpdateInput();

            // Reset update accumulated time elapsed.
            int    currentUpdateTotalCount = 0;
            double currentUpdateTotalElapsedMillisecond = 0;
            double lastUpdateBegunMillisecond = Counter.GetMilliseconds();
            double lastUpdateEndedMillisecond = 0;
            do
            {
                mGame->Update(currentUpdateTotalCount == 0 ? lastUpdateElapsedMillisecond + lastRenderElapsedMillisecond : lastUpdateElapsedMillisecond);
                ++currentUpdateTotalCount;

                lastUpdateEndedMillisecond = Counter.GetMilliseconds();

                // Get the time elapsed during the LAST update.
                lastUpdateElapsedMillisecond = lastUpdateEndedMillisecond - lastUpdateBegunMillisecond;
                currentUpdateTotalElapsedMillisecond += lastUpdateElapsedMillisecond;

                // Reset update start point.
                lastUpdateBegunMillisecond = lastUpdateEndedMillisecond;
            }
            while (currentUpdateTotalElapsedMillisecond + lastUpdateElapsedMillisecond <= MillisecondPerRender);

            // Output performance profile
            double lastFrameFPS = 1000 / lastFrameElapsedMillisecond;
            sprintf_s(lastFramePerformanceString, "f%.02fms, u%.02fms, r%.02fms, %du/f, %0.2ff/s\n",
                      lastFrameElapsedMillisecond,
                      lastUpdateElapsedMillisecond,
                      lastRenderElapsedMillisecond,
                      lastUpdateTotalCount,
                      lastFrameFPS);
            GameDebug::OutputString(lastFramePerformanceString);

            // Store last update count
            lastUpdateTotalCount = currentUpdateTotalCount;

            // Reset render start point.
            lastRenderBegunMillisecond = lastUpdateEndedMillisecond;
            mGame->RenderBegin();
            mGame->Render(1.0f);
            mGame->RenderEnd();
        }
    }
}

void
GameEngine::Exit()
{
    if (mGame != nullptr)
    {
        mGame->Exit();
    }
}

}
