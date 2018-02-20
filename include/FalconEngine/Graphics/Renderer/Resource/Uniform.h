#pragma once

#include <FalconEngine/Core/Macro.h>

#include <functional>
#include <map>
#include <memory>
#include <vector>
#include <unordered_map>

#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Vector4.h>
#include <FalconEngine/Math/Matrix3.h>
#include <FalconEngine/Math/Matrix4.h>

namespace FalconEngine
{

enum class UniformType
{
    None,

    Bool,

    Float,
    FloatVec2,
    FloatVec3,
    FloatVec4,
    FloatMat2,
    FloatMat3,
    FloatMat4,

    Int,
    IntVec2,
    IntVec3,
    IntVec4,

    Count,
};

class Camera;
class Visual;

template <typename T>
using UniformUpdatePrototype = T(const Visual *, const Camera *);

template <typename T>
using UniformUpdateFunction = std::function<UniformUpdatePrototype<T>>;

FALCON_ENGINE_CLASS_BEGIN UniformMetadata final
{
public:
    UniformMetadata(const std::string & name) : mEnabled(true),
        mName(name), mLocation(-1)
    {
    }

public:
    bool mEnabled;
    std::string mName;
    int mLocation;
};
FALCON_ENGINE_CLASS_END

// NTOE(Wuxiang): Shader uniform is only supported in OpenGL. Direct3D can only
// use Uniform Buffer, or in another name, Constant Buffer.
FALCON_ENGINE_CLASS_BEGIN Uniform
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Uniform(const std::string & name, UniformType type);
    virtual ~Uniform();

public:
    // @remark If the value is not current, renderer would call Update member
    // function for this instance of uniform.
    bool
    IsUpdateNeeded() const;

    virtual void
    Update(const Camera * camera, const Visual * visual);

public:
    bool mEnabled;
    std::string mName;
    bool mInitialized;
    int mLocation;
    UniformType mType;

protected:
    bool mValueIsCurrent;
};
FALCON_ENGINE_CLASS_END

template<typename T>
class UniformValue : public Uniform
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    UniformValue(const std::string& name, const T& value);
    virtual ~UniformValue();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    const T&
    GetValue() const;

    virtual void
    SetValue(const T& value);

protected:
    T mValue;
};

template <typename T, typename U, typename ... Args>
std::shared_ptr<UniformValue<T>>
                              ShareUniform(Args&& ... args)
{
    return std::static_pointer_cast<UniformValue<T>>(
               std::make_shared<U>(args ...));
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
template <>
inline UniformValue<bool>::UniformValue(const std::string& name, const bool& value) :
    Uniform(name, UniformType::Bool),
    mValue(value)
{
}

template <>
inline UniformValue<int>::UniformValue(const std::string& name, const int& value) :
    Uniform(name, UniformType::Int),
    mValue(value)
{
}

template <>
inline UniformValue<Vector2i>::UniformValue(const std::string& name, const Vector2i& value) :
    Uniform(name, UniformType::IntVec2),
    mValue(value)
{
}

template <>
inline UniformValue<Vector3i>::UniformValue(const std::string& name, const Vector3i& value) :
    Uniform(name, UniformType::IntVec3),
    mValue(value)
{
}

template <>
inline UniformValue<Vector4i>::UniformValue(const std::string& name, const Vector4i& value) :
    Uniform(name, UniformType::IntVec4),
    mValue(value)
{
}

template <>
inline UniformValue<float>::UniformValue(const std::string& name, const float& value) :
    Uniform(name, UniformType::Float),
    mValue(value)
{
}

template <>
inline UniformValue<Vector2f>::UniformValue(const std::string& name, const Vector2f& value) :
    Uniform(name, UniformType::FloatVec2),
    mValue(value)
{
}

template <>
inline UniformValue<Vector3f>::UniformValue(const std::string& name, const Vector3f& value) :
    Uniform(name, UniformType::FloatVec3),
    mValue(value)
{
}

template <>
inline UniformValue<Vector4f>::UniformValue(const std::string& name, const Vector4f& value) :
    Uniform(name, UniformType::FloatVec4),
    mValue(value)
{
}

template <>
inline UniformValue<Matrix3f>::UniformValue(const std::string& name, const Matrix3f& value) :
    Uniform(name, UniformType::FloatMat3),
    mValue(value)
{
}

template <>
inline UniformValue<Matrix4f>::UniformValue(const std::string& name, const Matrix4f& value) :
    Uniform(name, UniformType::FloatMat4),
    mValue(value)
{
}

template <typename T>
UniformValue<T>::~UniformValue()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
template <typename T>
const T&
UniformValue<T>::GetValue() const
{
    return mValue;
}

template <typename T>
void
UniformValue<T>::SetValue(const T& value)
{
    mValue = value;
}

template <typename T>
using UniformValueSp = std::shared_ptr<UniformValue<T>>;

}

#define FALCON_ENGINE_UNIFORM_FUNC_BEGIN(captureList) \
    std::bind([captureList](const FalconEngine::Visual * visual, const FalconEngine::Camera *camera)

#define FALCON_ENGINE_UNIFORM_FUNC_END , std::placeholders::_1, std::placeholders::_2)
