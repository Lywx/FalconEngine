#include <FalconEngine/Core/Game.h>
#include <iostream>

namespace FalconEngine {
namespace Core {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Game::Game(GameContext *context)
    : Context(context)
{
    Context->Game = this;
}

Game::Game(const Game& rhs)
    : Context(rhs.Context)
{
}

Game& Game::operator=(const Game& rhs)
{
    Context = rhs.Context;
    return *this;
}

Game::Game(Game&& rhs) noexcept
    : Context(rhs.Context)
{
    rhs.Context = nullptr;
}

Game& Game::operator=(Game&& rhs) noexcept
{
    if (this != &rhs)
    {
        Context = rhs.Context;
        rhs.Context = nullptr;
    }

    return *this;
}

Game::~Game()
{
    Context = nullptr;
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
inline void Game::Run()
{
    if (!m_initialized)
    {
        Initialize();
    }

    Loop();
    Exit();
}

inline void Game::Shutdown()
{
    m_running = false;
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
inline void Game::Initialize()
{
    if(Context != nullptr)
    {
        Context->Initialize();
    }

    m_initialized = true;
}

// Main loop
//
// The main goal of this algorithm is to ensure the render rate is constant and update rate is flexible.
inline void Game::Loop()
{
    PerformanceCounter = Core::GamePerformanceCounter();
    char lastFramePerformanceString[256];

    if (Context != nullptr)
    {
        double lastFrameBegunMillisecond = PerformanceCounter.GetMilliseconds();
        double lastRenderBegunMillisecond = lastFrameBegunMillisecond;
        int    lastUpdateTotalCount = 0;

        // First update has no previous elapsed time
        double lastUpdateElapsedMillisecond = 0;

        while (m_running)
        {
            double lastFrameEndedMillisecond = PerformanceCounter.GetMilliseconds();
            double lastRenderEndedMillisecond = lastFrameEndedMillisecond;

            // Get the time elapsed during the LAST frame.
            double lastFrameElapsedMillisecond = lastFrameEndedMillisecond - lastFrameBegunMillisecond;
            double lastRenderElapsedMillisecond = lastRenderEndedMillisecond - lastRenderBegunMillisecond;

            // Reset frame start point.
            lastFrameBegunMillisecond = lastFrameEndedMillisecond;

            Context->UpdateInput();

            // Reset update accumulated time elapsed.
            int    currentUpdateTotalCount = 0;
            double currentUpdateTotalElapsedMillisecond = 0;
            double lastUpdateBegunMillisecond = PerformanceCounter.GetMilliseconds();
            double lastUpdateEndedMillisecond = 0;
            do
            {
                Context->Update(currentUpdateTotalCount == 0 ? lastUpdateElapsedMillisecond + lastRenderElapsedMillisecond : lastUpdateElapsedMillisecond);
                ++currentUpdateTotalCount;

                lastUpdateEndedMillisecond = PerformanceCounter.GetMilliseconds();

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
            Context->RenderBegin();
            Context->Render(1.0f);
            Context->RenderEnd();
        }
    }
}

inline void Game::Exit()
{
    if (Context != nullptr)
    {
        Context->Exit();
    }
}

}
}
