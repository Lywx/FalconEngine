#include <FalconEngine/Core/GameEngine.h>
#include <FalconEngine/Core/GameEngineData.h>
#include <FalconEngine/Core/GameEnginePlatform.h>
#include <FalconEngine/Core/GameEngineProfiler.h>
#include <FalconEngine/Core/GameEngineGraphics.h>
#include <FalconEngine/Core/GameEngineInput.h>
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Core/Exception.h>

#include <mutex>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngine::GameEngine(Game *game) :
    mData(nullptr),
    mGame(game),
    mGraphics(nullptr),
    mInput(nullptr),
    mPlatform(nullptr),
    mProfiler(nullptr),
    mSettings(nullptr)
{
    FALCON_ENGINE_CHECK_NULLPTR(game);

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
    mData->mRunning = false;
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

    // NOTE(Wuxiang): GLFW or Qt context is initialized here.
    mPlatform = GameEnginePlatform::GetInstance();
    mPlatform->Initialize();

    mProfiler = GameEngineProfiler::GetInstance();
    mProfiler->Initialize();

    mGraphics = GameEngineGraphics::GetInstance();
    mGraphics->Initialize();

    mInput = GameEngineInput::GetInstance();
    mInput->Initialize();

    mGame->Initialize();

    mInitialized = true;
}

void
GameEngine::Loop()
{
    mData->mRunning = true;

    double lastFrameBegunMillisecond = Timer::GetMilliseconds();
    double lastRenderBegunMillisecond = lastFrameBegunMillisecond;
    int    lastFrameUpdateTotalCount = 0;

    // First update has no previous elapsed time
    double lastUpdateElapsedMillisecond = 0;

    while (mData->mRunning)
    {
        double lastFrameEndedMillisecond = Timer::GetMilliseconds();
        double lastRenderEndedMillisecond = lastFrameEndedMillisecond;

        // Get the time elapsed during the LAST frame.
        double lastFrameElapsedMillisecond = lastFrameEndedMillisecond - lastFrameBegunMillisecond;
        double lastRenderElapsedMillisecond = lastRenderEndedMillisecond - lastRenderBegunMillisecond;

        // Reset frame start point.
        lastFrameBegunMillisecond = lastFrameEndedMillisecond;

        // NOTE(Wuxiang): Elapsed time count from before last input update
        // to before current input update.
        mInput->UpdateFrame(lastFrameElapsedMillisecond);

        // NOTE(Wuxiang): Update frame-rate sensitive data.
        mGame->UpdateFrame(mGraphics, mInput, lastFrameElapsedMillisecond);

        // Reset update accumulated time elapsed.
        int    currentFrameUpdateTotalCount = 0;
        double currentUpdateTotalElapsedMillisecond = 0;
        double lastUpdateBegunMillisecond = Timer::GetMilliseconds();
        double lastUpdateEndedMillisecond = 0;

        // NOTE(Wuxiang): Elapsed time count from before frame-sensitive
        // update to after frame-sensitive update.
        double currentFrameSensitiveUpdateElapsedMillisecond = lastUpdateBegunMillisecond - lastFrameEndedMillisecond;

        do
        {
            // NOTE(Wuxiang): Elapsed time count from before last game update
            // to before current game update.
            mGame->Update(mGraphics, mInput, currentFrameUpdateTotalCount == 0
                          ? lastUpdateElapsedMillisecond
                          + lastRenderElapsedMillisecond
                          + currentFrameSensitiveUpdateElapsedMillisecond
                          : lastUpdateElapsedMillisecond);
            ++currentFrameUpdateTotalCount;

            lastUpdateEndedMillisecond = Timer::GetMilliseconds();

            // Get the time elapsed during the LAST update.
            lastUpdateElapsedMillisecond = lastUpdateEndedMillisecond - lastUpdateBegunMillisecond;
            currentUpdateTotalElapsedMillisecond += lastUpdateElapsedMillisecond;

            // Reset update start point.
            lastUpdateBegunMillisecond = lastUpdateEndedMillisecond;
        }
        while (currentUpdateTotalElapsedMillisecond <= mSettings->mFrameElapsedMillisecond - lastRenderElapsedMillisecond);

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
        lastRenderBegunMillisecond = Timer::GetMilliseconds();

        mGame->RenderBegin(mGraphics);

        // NEW(Wuxiang): Add interpolation support.
        mGame->Render(mGraphics, 1.0f);
        mGame->RenderEnd(mGraphics);
    }
}

void
GameEngine::Destory()
{
    mGame->Destory();
    mProfiler->Destroy();

    mGraphics->Destroy();
    mInput->Destroy();
    mPlatform->Destroy();
}

}
