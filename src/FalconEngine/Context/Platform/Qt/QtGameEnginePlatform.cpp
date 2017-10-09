#include <FalconEngine/Context/GameEnginePlatform.h>
#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Context/GameEngineWindow.h>
#include <FalconEngine/Context/GameDebug.h>

#if defined(FALCON_ENGINE_WINDOW_QT)
#include <FalconEngine/Context/Platform/Qt/QtGameEngineData.h>

namespace FalconEngine
{

void
GameEnginePlatform::InitializePlatform()
{
    auto gameEngineSettings = GameEngineSettings::GetInstance();
    auto gameEngineData = GameEngineData::GetInstance();

    // Initialize Qt.
    {
        auto window = &gameEngineData->mWindow;
        window->setWindowTitle(gameEngineSettings->mWindowTitle.c_str());
        window->resize(gameEngineSettings->mWindowWidth, gameEngineSettings->mWindowHeight);
    }

    // Initialize GLEW.
    {
        // NOTE(Wuxiang): Need to initialize glew after window has been created.
        // http://stackoverflow.com/questions/13943825/access-violation-when-using-glew-and-glfw
        if (glewInit() == GLEW_OK)
        {
            GameDebug::OutputString("GLEW initialization succeeded.\n");
        }
        else
        {
            GameDebug::OutputString("GLEW initialization failed.\n");

            // TODO(Wuxiang): 2017-10-06 21:57 ???
            exit(1);
        }
    }
}

}
#endif
