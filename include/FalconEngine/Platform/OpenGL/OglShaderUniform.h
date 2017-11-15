#pragma once

#include <FalconEngine/Platform/OpenGL/OglMapping.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

namespace FalconEngine
{

template <typename T>
class ShaderUniformValue;

class FALCON_ENGINE_API PlatformShaderUniform
{
public:

    // @remark The implementation of this method is platform dependent. Though the
    // template function definition would normally reside in the header files, it
    // is possible to define the it as explicit specialization.
    static void
    UpdateContext(ShaderUniform *shaderUniform);

private:
    template <typename T>
    static void
    Update(ShaderUniformValue<T> *shaderUniform);

    template <typename T>
    static ShaderUniformValue<T> *
    Cast(ShaderUniform *shaderUniform);
};

template<>
inline void
PlatformShaderUniform::Update<bool>(ShaderUniformValue<bool> *shaderUniform)
{
    glUniform1i(shaderUniform->mLocation, shaderUniform->GetValue());
}

template<>
inline void
PlatformShaderUniform::Update<int>(ShaderUniformValue<int> *shaderUniform)
{
    glUniform1i(shaderUniform->mLocation, shaderUniform->GetValue());
}

template<>
inline void
PlatformShaderUniform::Update<Vector2i>(ShaderUniformValue<Vector2i> *shaderUniform)
{
    auto& value = shaderUniform->GetValue();
    glUniform2i(shaderUniform->mLocation, value.x, value.y);
}

template<>
inline void
PlatformShaderUniform::Update<Vector3i>(ShaderUniformValue<Vector3i> *shaderUniform)
{
    auto& value = shaderUniform->GetValue();
    glUniform3i(shaderUniform->mLocation, value.x, value.y, value.z);
}

template<>
inline void
PlatformShaderUniform::Update<Vector4i>(ShaderUniformValue<Vector4i> *shaderUniform)
{
    auto& value = shaderUniform->GetValue();
    glUniform4i(shaderUniform->mLocation, value.x, value.y, value.z, value.w);
}

template<>
inline void
PlatformShaderUniform::Update<float>(ShaderUniformValue<float> *shaderUniform)
{
    glUniform1f(shaderUniform->mLocation, shaderUniform->GetValue());
}

template<>
inline void
PlatformShaderUniform::Update<Vector2f>(ShaderUniformValue<Vector2f> *shaderUniform)
{
    auto& value = shaderUniform->GetValue();
    glUniform2f(shaderUniform->mLocation, value.x, value.y);
}

template<>
inline void
PlatformShaderUniform::Update<Vector3f>(ShaderUniformValue<Vector3f> *shaderUniform)
{
    auto& value = shaderUniform->GetValue();
    glUniform3f(shaderUniform->mLocation, value.x, value.y, value.z);
}

template<>
inline void
PlatformShaderUniform::Update<Vector4f>(ShaderUniformValue<Vector4f> *shaderUniform)
{
    auto& value = shaderUniform->GetValue();
    glUniform4f(shaderUniform->mLocation, value.x, value.y, value.z, value.w);
}

template<>
inline void
PlatformShaderUniform::Update<Matrix3f>(ShaderUniformValue<Matrix3f> *shaderUniform)
{
    auto& value = shaderUniform->GetValue();
    glUniformMatrix3fv(shaderUniform->mLocation, 1, GL_FALSE, &value[0][0]);
}

template<>
inline void
PlatformShaderUniform::Update<Matrix4f>(ShaderUniformValue<Matrix4f> *shaderUniform)
{
    auto& value = shaderUniform->GetValue();
    glUniformMatrix4fv(shaderUniform->mLocation, 1, GL_FALSE, &value[0][0]);
}

template <typename T>
ShaderUniformValue<T> *
PlatformShaderUniform::Cast(ShaderUniform *shaderUniform)
{
    return reinterpret_cast<ShaderUniformValue<T>*>(shaderUniform);
}

}
