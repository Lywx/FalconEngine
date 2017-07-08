#include <FalconEngine/Context/GameEngine.h>
#include <FalconEngine/Context/GameEnginePlatform.h>
#include <FalconEngine/Context/GameEngineProfiler.h>
#include <FalconEngine/Context/GameEngineGraphics.h>
#include <FalconEngine/Context/GameEngineInput.h>
#include <FalconEngine/Context/GameEngineSettings.h>

#include <mutex>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
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
    std::lock_guard<std::mutex> lock(mMutex);

    // NOTE(Wuxiang): Thread-safe singleton pattern is used in all the game engine
    // context components.
    mData = GameEngineData::GetInstance();
    mSettings = GameEngineSettings::GetInstance();

    mPlatform = GameEnginePlatform::GetInstance();
    if (mPlatform != nullptr)
    {
        mPlatform->Initialize();
    }

    mProfiler = GameEngineProfiler::GetInstance();
    if (mProfiler != nullptr)
    {
        mProfiler->Initialize();
    }

    mGraphics = GameEngineGraphics::GetInstance();
    if (mGraphics != nullptr)
    {
        mGraphics->Initialize();
    }

    mInput = GameEngineInput::GetInstance();
    if (mInput != nullptr)
    {
        mInput->Initialize();
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
    if (mGame != nullptr)
    {
        double lastFrameBegunMillisecond = GameTimer::GetMilliseconds();
        double lastRenderBegunMillisecond = lastFrameBegunMillisecond;
        int    lastFrameUpdateTotalCount = 0;

        // First update has no previous elapsed time
        double lastUpdateElapsedMillisecond = 0;

        while (mRunning)
        {
            double lastFrameEndedMillisecond = GameTimer::GetMilliseconds();
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
            double lastUpdateBegunMillisecond = GameTimer::GetMilliseconds();
            double lastUpdateEndedMillisecond = 0;
            do
            {
                mGame->Update(mGraphics, mInput, currentFrameUpdateTotalCount == 0 ? lastUpdateElapsedMillisecond + lastRenderElapsedMillisecond : lastUpdateElapsedMillisecond);
                ++currentFrameUpdateTotalCount;

                lastUpdateEndedMillisecond = GameTimer::GetMilliseconds();

                // Get the time elapsed during the LAST update.
                lastUpdateElapsedMillisecond = lastUpdateEndedMillisecond - lastUpdateBegunMillisecond;
                currentUpdateTotalElapsedMillisecond += lastUpdateElapsedMillisecond;

                // Reset update start point.
                lastUpdateBegunMillisecond = lastUpdateEndedMillisecond;
            }
            while (currentUpdateTotalElapsedMillisecond + lastUpdateElapsedMillisecond <= mSettings->mFrameElapsedMillisecond - lastRenderElapsedMillisecond);

            // Output performance profile
            double lastFrameFps = 1000 / lastFrameElapsedMillisecond;

            mProfiler->mLastFrameElapsedMillisecond  = lastFrameElapsedMillisecond;
            mProfiler->mLastFrameUpdateTotalCount    = lastFrameUpdateTotalCount;
            mProfiler->mLastFrameFps                 = lastFrameFps;
            mProfiler->mLastUpdateElapsedMillisecond = lastUpdateElapsedMillisecond;
            mProfiler->mLastRenderElapsedMillisecond = lastRenderElapsedMillisecond;

            // Store last update count
            lastFrameUpdateTotalCount = currentFrameUpdateTotalCount;

            // Reset render start point.
            lastRenderBegunMillisecond = lastUpdateEndedMillisecond;

            mGame->RenderBegin(mGraphics);

            // NEW(Wuxiang): Add interpolation support.
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
}

}
