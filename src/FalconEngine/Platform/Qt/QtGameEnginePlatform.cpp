#include <FalconEngine/Core/GameEnginePlatform.h>
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Core/GameEngineWindow.h>
#include <FalconEngine/Core/GameEngineDebugger.h>

#if defined(FALCON_ENGINE_WINDOW_QT)
#include <FalconEngine/Core/GameEngineData.h>
namespace FalconEngine
{

void
GameEnginePlatform::InitializePlatform()
{
    // NOTE(Wuxiang): You have to initialize OpenGL context first.
    InitializeContextPlatform();
    InitializeLoaderPlatform();
}

void
GameEnginePlatform::InitializeContextPlatform()
{
    auto gameEngineData = GameEngineData::GetInstance();
    auto gameEngineSettings = GameEngineSettings::GetInstance();

    // Initialize Qt window.
    auto window = std::make_shared<GameEngineWindow>();
    window->Initialize();

    window->setWindowTitle(gameEngineSettings->mWindowTitle.c_str());
    window->resize(gameEngineSettings->mWindowWidth,
                   gameEngineSettings->mWindowHeight);

    // TODO(Wuxiang):
    gameEngineData->mWindow = window;
}

}
#endif
