#include <FalconEngine/Content/AssetTool.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLShader.h>

namespace FalconEngine
{

void
AssetTool::OGLValidateShader(Shader& shader)
{
    PlatformShader shaderPlatform(nullptr, &shader);
}

}

#endif