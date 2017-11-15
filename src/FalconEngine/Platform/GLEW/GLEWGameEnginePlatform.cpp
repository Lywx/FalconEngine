#include <FalconEngine/Core/GameEnginePlatform.h>
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Core/GameEngineDebugger.h>

#if defined(FALCON_ENGINE_API_OPENGL) && defined(FALCON_ENGINE_API_OPENGL_GLEW)
#include <FalconEngine/Platform/Common.h>
namespace FalconEngine
{

void
GameEnginePlatform::InitializeLoaderPlatform()
{
    // Initialize GLEW.
    //
    // NOTE(Wuxiang): Need to initialize glew after window has been created.
    // http://stackoverflow.com/questions/13943825/access-violation-when-using-glew-and-glfw
    if (glewInit() == GLEW_OK)
    {
        GameEngineDebugger::OutputString("GLEW initialization succeeded.\n");
    }
    else
    {
        GameEngineDebugger::OutputString("GLEW initialization failed.\n");
        exit(FALCON_ENGINE_API_ERROR);
    }
}

}
#endif