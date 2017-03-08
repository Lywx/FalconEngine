#include <FalconEngine/ContentInclude.h>
#include <FalconEngine/Content/AssetProcessor.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLShader.h>

using namespace std;
using namespace FalconEngine;

void
BakeAssets()
{
    auto assetProcessor = AssetProcessor();

    // Fonts
    assetProcessor.BakeFont("Content/Fonts/LuciadaConsoleDistanceField.fnt");
    //assetProcessor.BakeFont("Content/Fonts/NSimSunDistanceField.fnt");

    // Models
    // assetProcessor.BakeModel("Content/Models/Axe.obj");
    // assetProcessor.BakeModel("Content/Models/Carl.stl");
    //assetProcessor.BakeModel("Content/Models/nanosuit.obj");
}

void
CompileShaders()
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

    glewInit();

    // Shader Compiling Test
    auto shader = std::make_shared<Shader>();
    //shader->PushShaderFile(ShaderType::VertexShader, "Content/Shaders/PhongLighting.vert.glsl");
    //shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shaders/PhongLighting.frag.glsl");
    shader->PushShaderFile(ShaderType::VertexShader, "Content/Shaders/BoundingBox.vert.glsl");
    shader->PushShaderFile(ShaderType::FragmentShader, "Content/Shaders/BoundingBox.frag.glsl");
    auto platformShader = PlatformShader(shader.get());
    platformShader.CollectUniformActive();
}

int
main(int argc, char **argv)
{
    BakeAssets();
    //CompileShaders();

    return 0;
}

