#include <FalconEngine/Core/GameEnginePlatform.h>

#if defined(FALCON_ENGINE_API_OPENGL_GLEW)
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Core/GameEngineDebugger.h>
#include <FalconEngine/Platform/GLEW/GLEWLib.h>
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
        FALCON_ENGINE_THROW_API_EXCEPTION("GLEW initialization failed.\n");
    }
}

}

#endif