#include <FalconEngine/Context/GameEnginePlatform.h>
#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Context/GameEngineWindow.h>
#include <FalconEngine/Context/GameDebug.h>

#if defined(FALCON_ENGINE_WINDOW_QT)
#include <FalconEngine/Context/GameEngineData.h>
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
