#include <FalconEngine/Context/GameEngine.h>
#include <FalconEngine/Context/GameEnginePlatform.h>
#include <FalconEngine/Context/GameEngineProfiler.h>
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
double
GameEngine::GetMillisecondPerRender() const
{
    return mMillisecondPerRender;
}

void
GameEngine::SetMillisecondPerRender(double millisecondPerRender)
{
    mMillisecondPerRender = millisecondPerRender;
}

const GameEngineData *
GameEngine::GetData() const
{
    return mData;
}

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

    mProfiler = GameEngineProfiler::GetInstance();
    if (mProfiler != nullptr)
    {
        auto settings = mGame->GetEngineSettings();
        mProfiler->Initialize(mData, settings);
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
    char lastFramePerformanceString[256];

    if (mGame != nullptr)
    {
        double lastFrameBegunMillisecond = GameCounter::GetMilliseconds();
        double lastRenderBegunMillisecond = lastFrameBegunMillisecond;
        int    lastFrameUpdateTotalCount = 0;

        // First update has no previous elapsed time
        double lastUpdateElapsedMillisecond = 0;

        while (mRunning)
        {
            double lastFrameEndedMillisecond = GameCounter::GetMilliseconds();
            double lastRenderEndedMillisecond = lastFrameEndedMillisecond;

            // Get the time elapsed during the LAST frame.
            double lastFrameElapsedMillisecond = lastFrameEndedMillisecond - lastFrameBegunMillisecond;
            double lastRenderElapsedMillisecond = lastRenderEndedMillisecond - lastRenderBegunMillisecond;

            // Reset frame start point.
            lastFrameBegunMillisecond = lastFrameEndedMillisecond;

            mInput->Update();

            // Reset update accumulated time elapsed.
            int    currentFrameUpdateTotalCount = 0;
            double currentUpdateTotalElapsedMillisecond = 0;
            double lastUpdateBegunMillisecond = GameCounter::GetMilliseconds();
            double lastUpdateEndedMillisecond = 0;
            do
            {
                mGame->Update(mInput, currentFrameUpdateTotalCount == 0 ? lastUpdateElapsedMillisecond + lastRenderElapsedMillisecond : lastUpdateElapsedMillisecond);
                ++currentFrameUpdateTotalCount;

                lastUpdateEndedMillisecond = GameCounter::GetMilliseconds();

                // Get the time elapsed during the LAST update.
                lastUpdateElapsedMillisecond = lastUpdateEndedMillisecond - lastUpdateBegunMillisecond;
                currentUpdateTotalElapsedMillisecond += lastUpdateElapsedMillisecond;

                // Reset update start point.
                lastUpdateBegunMillisecond = lastUpdateEndedMillisecond;
            }
            while (currentUpdateTotalElapsedMillisecond + lastUpdateElapsedMillisecond <= mMillisecondPerRender);

            // Output performance profile
            double lastFrameFPS = 1000 / lastFrameElapsedMillisecond;

            mProfiler->mLastFrameElapsedMillisecond  = lastFrameElapsedMillisecond;
            mProfiler->mLastFrameUpdateTotalCount    = lastFrameUpdateTotalCount;
            mProfiler->mLastFrameFPS                 = lastFrameFPS;
            mProfiler->mLastUpdateElapsedMillisecond = lastUpdateElapsedMillisecond;
            mProfiler->mLastRenderElapsedMillisecond = lastRenderElapsedMillisecond;

            sprintf_s(lastFramePerformanceString, "f%.02fms, u%.02fms, r%.02fms, %du/f, %0.2ff/s\n",
                      lastFrameElapsedMillisecond,
                      lastUpdateElapsedMillisecond,
                      lastRenderElapsedMillisecond,
                      lastFrameUpdateTotalCount,
                      lastFrameFPS);
            GameDebug::OutputString(lastFramePerformanceString);

            // Store last update count
            lastFrameUpdateTotalCount = currentFrameUpdateTotalCount;

            // Reset render start point.
            lastRenderBegunMillisecond = lastUpdateEndedMillisecond;
            mGame->RenderBegin(mGraphics);
            mGame->Render(mGraphics, 1.0f);
            mGame->RenderEnd(mGraphics);
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
