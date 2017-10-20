#include <FalconEngine/Context/GameEnginePlatform.h>
#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Context/GameDebug.h>

#if defined(FALCON_ENGINE_API_OPENGL) && defined(FALCON_ENGINE_API_OPENGL_GLEW)
#include <FalconEngine/Context/Platform/GLEW/Common.h>
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
        GameDebug::OutputString("GLEW initialization succeeded.\n");
    }
    else
    {
        GameDebug::OutputString("GLEW initialization failed.\n");
        exit(FALCON_ENGINE_API_ERROR);
    }
}

}
#endif