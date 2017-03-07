#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <functional>
#include <map>
#include <vector>
#include <unordered_map>

#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Vector4.h>
#include <FalconEngine/Math/Matrix3.h>
#include <FalconEngine/Math/Matrix4.h>

namespace FalconEngine
{

enum class ShaderUniformType
{
    None,

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
using ShaderUniformUpdatePrototype = T(const Visual *, const Camera *);

template <typename T>
using ShaderUniformUpdateFunction = std::function<ShaderUniformUpdatePrototype<T>>;

class ShaderUniform
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ShaderUniform(const std::string name, ShaderUniformType type);
    virtual ~ShaderUniform();

    virtual void
    Update(const Camera *camera, const Visual *visual);

public:
    std::string       mName;
    int               mLocation;
    ShaderUniformType mType;
    bool              mUpdated;
};

template<typename T>
class ShaderUniformValue : public ShaderUniform
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ShaderUniformValue(const std::string& name, const T& value);
    virtual ~ShaderUniformValue();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    const T&
    GetValue() const;

protected:
    T mValue;
};

template<typename T>
using ShaderUniformValueSharedPtr = std::shared_ptr<ShaderUniformValue<T>>;

template <typename T, typename U, typename ... Args>
ShaderUniformValueSharedPtr<T>
ShareUniform(Args&& ... args)
{
    return static_pointer_cast<ShaderUniformValue<T>>(std::make_shared<U>(args ...));
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
template <>
inline ShaderUniformValue<int>::ShaderUniformValue(const std::string& name, const int& value) :
    ShaderUniform(name, ShaderUniformType::Int),
    mValue(value)
{
}

template <>
inline ShaderUniformValue<Vector2i>::ShaderUniformValue(const std::string& name, const Vector2i& value) :
    ShaderUniform(name, ShaderUniformType::IntVec2),
    mValue(value)
{
}

template <>
inline ShaderUniformValue<Vector3i>::ShaderUniformValue(const std::string& name, const Vector3i& value) :
    ShaderUniform(name, ShaderUniformType::IntVec3),
    mValue(value)
{
}

template <>
inline ShaderUniformValue<Vector4i>::ShaderUniformValue(const std::string& name, const Vector4i& value) :
    ShaderUniform(name, ShaderUniformType::IntVec4),
    mValue(value)
{
}

template <>
inline ShaderUniformValue<float>::ShaderUniformValue(const std::string& name, const float& value) :
    ShaderUniform(name, ShaderUniformType::Float),
    mValue(value)
{
}

template <>
inline ShaderUniformValue<Vector2f>::ShaderUniformValue(const std::string& name, const Vector2f& value) :
    ShaderUniform(name, ShaderUniformType::FloatVec2),
    mValue(value)
{
}

template <>
inline ShaderUniformValue<Vector3f>::ShaderUniformValue(const std::string& name, const Vector3f& value) :
    ShaderUniform(name, ShaderUniformType::FloatVec3),
    mValue(value)
{
}

template <>
inline ShaderUniformValue<Vector4f>::ShaderUniformValue(const std::string& name, const Vector4f& value) :
    ShaderUniform(name, ShaderUniformType::FloatVec4),
    mValue(value)
{
}

template <>
inline ShaderUniformValue<Matrix3f>::ShaderUniformValue(const std::string& name, const Matrix3f& value) :
    ShaderUniform(name, ShaderUniformType::FloatMat3),
    mValue(value)
{
}

template <>
inline ShaderUniformValue<Matrix4f>::ShaderUniformValue(const std::string& name, const Matrix4f& value) :
    ShaderUniform(name, ShaderUniformType::FloatMat4),
    mValue(value)
{
}

template <typename T>
ShaderUniformValue<T>::~ShaderUniformValue()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
template <typename T>
const T& ShaderUniformValue<T>::GetValue() const
{
    return mValue;
}

}
