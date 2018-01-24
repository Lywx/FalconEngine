#include <FalconEngine/Content/AssetTool.h>
#include <FalconEngine/Core/GameEngineDebugger.h>

// NOTE(Wuxiang): Always used GLFW to create OpenGL context.
#include <FalconEngine/Platform/GLFW/Common.h>
#include <FalconEngine/Platform/OpenGL/Common.h>
#include <FalconEngine/Platform/OpenGL/OglShader.h>

namespace FalconEngine
{

void
AssetTool::InitializeContextPlatform()
{
    glfwInit();

    // GLFW Window Hints
    {
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // NOTE(Wuxiang): Don't show window because this is a console application.
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    }

    // OpenGL Context Hints
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
    }

    auto window = glfwCreateWindow(1, 1, "Compile", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (glewInit() == GLEW_OK)
    {
        GameEngineDebugger::OutputString("GLEW initialization succeeded.\n");
    }
    else
    {
        GameEngineDebugger::OutputString("GLEW initialization failed.\n");
        glfwTerminate();
    }
}

}