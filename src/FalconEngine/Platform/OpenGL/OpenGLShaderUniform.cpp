#include <FalconEngine/Platform/OpenGL/OpenGLUniform.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Core/Exception.h>

namespace FalconEngine
{

void
PlatformUniform::UpdateContext(Uniform *uniform)
{
    switch (uniform->mType)
    {
    case UniformType::Bool:
        Update(Cast<bool>(uniform));
        break;
    case UniformType::Float:
        Update(Cast<float>(uniform));
        break;
    case UniformType::FloatVec2:
        Update(Cast<Vector2f>(uniform));
        break;
    case UniformType::FloatVec3:
        Update(Cast<Vector3f>(uniform));
        break;
    case UniformType::FloatVec4:
        Update(Cast<Vector4f>(uniform));
        break;
    case UniformType::FloatMat2:
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        break;
    case UniformType::FloatMat3:
        Update(Cast<Matrix3f>(uniform));
        break;
    case UniformType::FloatMat4:
        Update(Cast<Matrix4f>(uniform));
        break;
    case UniformType::Int:
        Update(Cast<int>(uniform));
        break;
    case UniformType::IntVec2:
        Update(Cast<Vector2i>(uniform));
        break;
    case UniformType::IntVec3:
        Update(Cast<Vector3i>(uniform));
        break;
    case UniformType::IntVec4:
        Update(Cast<Vector4i>(uniform));
        break;
    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
}

}

#endif