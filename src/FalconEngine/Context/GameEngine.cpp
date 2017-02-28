#include <FalconEngine/Context/GameEngine.h>
#include <FalconEngine/Context/GameEnginePlatform.h>
#include <FalconEngine/Context/GameEngineGraphics.h>
#include <FalconEngine/Context/GameEngineInput.h>
#include <FalconEngine/Context/GameEngineSettings.h>

#if FALCON_ENGINE_PLATFORM_GLFW
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>
#endif

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngine::GameEngine(Game *game) :
    mGame(game),
    mInput(nullptr)
{
    mGame->SetEngine(this);
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
    Destory();
}

void
GameEngine::Exit()
{
    mRunning = false;
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
GameEngine::Initialize()
{
    mData = new GameEngineData();

    mPlatform = GameEnginePlatform::GetInstance();
    if (mPlatform != nullptr)
    {
        auto settings = mGame->GetEngineSettings();
        mPlatform->Initialize(mData, settings);
    }

    mGraphics = GameEngineGraphics::GetInstance();
    if (mGraphics != nullptr)
    {
        auto settings = mGame->GetEngineSettings();
        mGraphics->Initialize(mData, settings);
    }

    mInput = GameEngineInput::GetInstance();
    if (mInput != nullptr)
    {
        auto settings = mGame->GetEngineSettings();
        mInput->Initialize(mData, settings);
    }

    if(mGame != nullptr)
    {
        mGame->Initialize();
    }

    mInitialized = true;
}

void
GameEngine::Loop()
{
    mCounter = GameCounter();
    char lastFramePerformanceString[256];

    if (mGame != nullptr)
    {
        double lastFrameBegunMillisecond = mCounter.GetMilliseconds();
        double lastRenderBegunMillisecond = lastFrameBegunMillisecond;
        int    lastUpdateTotalCount = 0;

        // First update has no previous elapsed time
        double lastUpdateElapsedMillisecond = 0;

        while (mRunning)
        {
            double lastFrameEndedMillisecond = mCounter.GetMilliseconds();
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
            double lastUpdateBegunMillisecond = mCounter.GetMilliseconds();
            double lastUpdateEndedMillisecond = 0;
            do
            {
                mGame->Update(mInput, currentUpdateTotalCount == 0 ? lastUpdateElapsedMillisecond + lastRenderElapsedMillisecond : lastUpdateElapsedMillisecond);
                ++currentUpdateTotalCount;

                lastUpdateEndedMillisecond = mCounter.GetMilliseconds();

                // Get the time elapsed during the LAST update.
                lastUpdateElapsedMillisecond = lastUpdateEndedMillisecond - lastUpdateBegunMillisecond;
                currentUpdateTotalElapsedMillisecond += lastUpdateElapsedMillisecond;

                // Reset update start point.
                lastUpdateBegunMillisecond = lastUpdateEndedMillisecond;
            }
            while (currentUpdateTotalElapsedMillisecond + lastUpdateElapsedMillisecond <= mMillisecondPerRender);

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
GameEngine::Destory()
{
    if (mGame != nullptr)
    {
        mGame->Destory();
    }

    delete mData;
}

}
