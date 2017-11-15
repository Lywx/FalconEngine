#include <FalconEngine/Platform/OpenGL/OglShaderUniform.h>

namespace FalconEngine
{

void
PlatformShaderUniform::UpdateContext(ShaderUniform *shaderUniform)
{
    switch (shaderUniform->mType)
    {
    case ShaderUniformType::None:
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    case ShaderUniformType::Bool:
        Update(Cast<bool>(shaderUniform));
        break;
    case ShaderUniformType::Float:
        Update(Cast<float>(shaderUniform));
        break;
    case ShaderUniformType::FloatVec2:
        Update(Cast<Vector2f>(shaderUniform));
        break;
    case ShaderUniformType::FloatVec3:
        Update(Cast<Vector3f>(shaderUniform));
        break;
    case ShaderUniformType::FloatVec4:
        Update(Cast<Vector4f>(shaderUniform));
        break;
    case ShaderUniformType::FloatMat2:
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        break;
    case ShaderUniformType::FloatMat3:
        Update(Cast<Matrix3f>(shaderUniform));
        break;
    case ShaderUniformType::FloatMat4:
        Update(Cast<Matrix4f>(shaderUniform));
        break;
    case ShaderUniformType::Int:
        Update(Cast<int>(shaderUniform));
        break;
    case ShaderUniformType::IntVec2:
        Update(Cast<Vector2i>(shaderUniform));
        break;
    case ShaderUniformType::IntVec3:
        Update(Cast<Vector3i>(shaderUniform));
        break;
    case ShaderUniformType::IntVec4:
        Update(Cast<Vector4i>(shaderUniform));
        break;
    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
}


}
