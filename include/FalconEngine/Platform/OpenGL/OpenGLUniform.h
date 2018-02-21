#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>

namespace FalconEngine
{

template <typename T>
class UniformValue;

FALCON_ENGINE_CLASS_BEGIN PlatformUniform
{
public:
    // @remark The implementation of this method is platform dependent. Though the
    // template function definition would normally reside in the header files, it
    // is possible to define the it as explicit specialization.
    static void
    UpdateContext(Uniform * uniform);

private:
    template <typename T>
    static void
    Update(UniformValue<T> *uniform);

    template <typename T>
    static UniformValue<T> *
    Cast(Uniform * uniform);
};
FALCON_ENGINE_CLASS_END

template<>
inline void
PlatformUniform::Update<bool>(UniformValue<bool> *uniform)
{
    glUniform1i(uniform->mLocation, uniform->GetValue());
}

template<>
inline void
PlatformUniform::Update<int>(UniformValue<int> *uniform)
{
    glUniform1i(uniform->mLocation, uniform->GetValue());
}

template<>
inline void
PlatformUniform::Update<Vector2i>(UniformValue<Vector2i> *uniform)
{
    auto& value = uniform->GetValue();
    glUniform2i(uniform->mLocation, value.x, value.y);
}

template<>
inline void
PlatformUniform::Update<Vector3i>(UniformValue<Vector3i> *uniform)
{
    auto& value = uniform->GetValue();
    glUniform3i(uniform->mLocation, value.x, value.y, value.z);
}

template<>
inline void
PlatformUniform::Update<Vector4i>(UniformValue<Vector4i> *uniform)
{
    auto& value = uniform->GetValue();
    glUniform4i(uniform->mLocation, value.x, value.y, value.z, value.w);
}

template<>
inline void
PlatformUniform::Update<float>(UniformValue<float> *uniform)
{
    glUniform1f(uniform->mLocation, uniform->GetValue());
}

template<>
inline void
PlatformUniform::Update<Vector2f>(UniformValue<Vector2f> *uniform)
{
    auto& value = uniform->GetValue();
    glUniform2f(uniform->mLocation, value.x, value.y);
}

template<>
inline void
PlatformUniform::Update<Vector3f>(UniformValue<Vector3f> *uniform)
{
    auto& value = uniform->GetValue();
    glUniform3f(uniform->mLocation, value.x, value.y, value.z);
}

template<>
inline void
PlatformUniform::Update<Vector4f>(UniformValue<Vector4f> *uniform)
{
    auto& value = uniform->GetValue();
    glUniform4f(uniform->mLocation, value.x, value.y, value.z, value.w);
}

template<>
inline void
PlatformUniform::Update<Matrix3f>(UniformValue<Matrix3f> *uniform)
{
    auto& value = uniform->GetValue();
    glUniformMatrix3fv(uniform->mLocation, 1, GL_FALSE, &value[0][0]);
}

template<>
inline void
PlatformUniform::Update<Matrix4f>(UniformValue<Matrix4f> *uniform)
{
    auto& value = uniform->GetValue();
    glUniformMatrix4fv(uniform->mLocation, 1, GL_FALSE, &value[0][0]);
}

template <typename T>
UniformValue<T> *
PlatformUniform::Cast(Uniform *uniform)
{
    return reinterpret_cast<UniformValue<T>*>(uniform);
}

}

#endif