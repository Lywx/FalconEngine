#include <FalconEngine/Content/AssetTool.h>

#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Core/Debug.h>
#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Core/Path.h>
#include <FalconEngine/Core/String.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>

#ifndef FALCON_ENGINE_API_OPENGL
#define FALCON_ENGINE_API_OPENGL
#endif
#include <FalconEngine/Platform/OpenGL/OpenGLShader.h>

#if defined(FALCON_ENGINE_OS_WINDOWS)
#include <FalconEngine/Platform/Win32/Win32Utility.h>
#endif

using namespace std;
using namespace FalconEngine;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
AssetTool::AssetTool()
{
    OGLInitializeContextPlatform();
}

AssetTool::~AssetTool()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
AssetTool::D3DBakeShader(const std::string& shaderFilePath)
{
    auto shaderType = GetShaderType(shaderFilePath);
    auto shaderOutputPath = AddAssetExtension(shaderFilePath);

    string shaderProfile;
    switch (shaderType)
    {
    case ShaderType::VertexShader:
        shaderProfile = "vs_5_1";
        break;
    case ShaderType::TessellationControlShader:
        shaderProfile = "hs_5_1";
        break;
    case ShaderType::TessellationEvaluationShader:
        shaderProfile = "ds_5_1";
        break;
    case ShaderType::GeometryShader:
        shaderProfile = "gs_5_1";
        break;
    case ShaderType::FragmentShader:
        shaderProfile = "ps_5_1";
        break;
    case ShaderType::ComputeShader:
        shaderProfile = "cs_5_1";
        break;
    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }

    auto cmd = GetStringFormat("%s /T %s /Fo %s /Zi %s", mFxcCompilerPath.c_str(), shaderProfile.c_str(), shaderOutputPath.c_str(), shaderFilePath.c_str());
    auto output = StartProcess(cmd);
    if (output.first != 0)
    {
        OpenMessageBox("Error", output.second);
    }
}

void
AssetTool::D3DSetShaderCompiler(const std::string& fxcCompilerPath)
{
    mFxcCompilerPath = fxcCompilerPath;
}

ShaderType
AssetTool::GetShaderType(const std::string& shaderFilePath)
{
    auto shaderExtension = GetFileExtension(GetFileStem(shaderFilePath));
    if (shaderExtension == ".vert")
    {
        return ShaderType::VertexShader;
    }

    if (shaderExtension == ".tesc")
    {
        return ShaderType::TessellationControlShader;
    }

    if (shaderExtension == ".tese")
    {
        return ShaderType::TessellationEvaluationShader;
    }

    if (shaderExtension == ".geom")
    {
        return ShaderType::GeometryShader;
    }

    if (shaderExtension == ".frag")
    {
        return ShaderType::FragmentShader;
    }

    if (shaderExtension == ".comp")
    {
        return ShaderType::ComputeShader;
    }

    FALCON_ENGINE_THROW_RUNTIME_EXCEPTION(
        GetStringFormat("Unidentified shader type: '%s'.", shaderExtension));
}

void
AssetTool::OGLValidateShader(Shader& shader)
{
    PlatformShader shaderPlatform(nullptr, &shader);
}

}
