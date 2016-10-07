#include <FalconEngine/Context/GameEngine.h>

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngine::GameEngine(Game *game)
    : m_game(game)
{
    m_game->SetEngine(this);
}

GameEngine::GameEngine(const GameEngine& rhs)
    : m_game(rhs.m_game)
{
}

GameEngine& GameEngine::operator=(const GameEngine& rhs)
{
    m_game = rhs.m_game;
    return *this;
}

GameEngine::GameEngine(GameEngine&& rhs) noexcept
    : m_game(rhs.m_game)
{
    rhs.m_game = nullptr;
}

GameEngine& GameEngine::operator=(GameEngine&& rhs) noexcept
{
    if (this != &rhs)
    {
        m_game = rhs.m_game;
        rhs.m_game = nullptr;
    }

    return *this;
}

GameEngine::~GameEngine()
{
    m_game = nullptr;
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
inline void GameEngine::Run()
{
    if (!m_initialized)
    {
        Initialize();
    }

    Loop();
    Exit();
}

inline void GameEngine::Shutdown()
{
    m_running = false;
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
inline void GameEngine::Initialize()
{
    if(m_game != nullptr)
    {
        m_game->Initialize();
    }

    m_initialized = true;
}

inline void GameEngine::Loop()
{
    Counter = GameCounter();
    char lastFramePerformanceString[256];

    if (m_game != nullptr)
    {
        double lastFrameBegunMillisecond = Counter.GetMilliseconds();
        double lastRenderBegunMillisecond = lastFrameBegunMillisecond;
        int    lastUpdateTotalCount = 0;

        // First update has no previous elapsed time
        double lastUpdateElapsedMillisecond = 0;

        while (m_running)
        {
            double lastFrameEndedMillisecond = Counter.GetMilliseconds();
            double lastRenderEndedMillisecond = lastFrameEndedMillisecond;

            // Get the time elapsed during the LAST frame.
            double lastFrameElapsedMillisecond = lastFrameEndedMillisecond - lastFrameBegunMillisecond;
            double lastRenderElapsedMillisecond = lastRenderEndedMillisecond - lastRenderBegunMillisecond;

            // Reset frame start point.
            lastFrameBegunMillisecond = lastFrameEndedMillisecond;

            m_game->UpdateInput();

            // Reset update accumulated time elapsed.
            int    currentUpdateTotalCount = 0;
            double currentUpdateTotalElapsedMillisecond = 0;
            double lastUpdateBegunMillisecond = Counter.GetMilliseconds();
            double lastUpdateEndedMillisecond = 0;
            do
            {
                m_game->Update(currentUpdateTotalCount == 0 ? lastUpdateElapsedMillisecond + lastRenderElapsedMillisecond : lastUpdateElapsedMillisecond);
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
            m_game->RenderBegin();
            m_game->Render(1.0f);
            m_game->RenderEnd();
        }
    }
}

inline void GameEngine::Exit()
{
    if (m_game != nullptr)
    {
        m_game->Exit();
    }
}

}
