#pragma once

#include <FalconEngine/Core/Common.h>

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

enum class ShaderUniformType
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
using ShaderUniformUpdatePrototype = T(const Visual *, const Camera *);

template <typename T>
using ShaderUniformUpdateFunction = std::function<ShaderUniformUpdatePrototype<T>>;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API ShaderUniform
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ShaderUniform(const std::string& name, ShaderUniformType type);
    virtual ~ShaderUniform();

public:
    // @remark If the value is not current, renderer would call Update member
    // function for this instance of uniform.
    bool
    IsUpdateNeeded() const;

    virtual void
    Update(const Camera *camera, const Visual *visual);

public:
    std::string       mName;
    bool              mEnabled;
    bool              mInitialized;
    int               mLocation;
    ShaderUniformType mType;

protected:
    bool              mValueIsCurrent;
};
#pragma warning(default: 4251)

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

    virtual void
    SetValue(const T& value);

protected:
    T mValue;
};

template <typename T, typename U, typename ... Args>
std::shared_ptr<ShaderUniformValue<T>>
                                    ShareUniform(Args&& ... args)
{
    return std::static_pointer_cast<ShaderUniformValue<T>>(
               std::make_shared<U>(args ...));
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
template <>
inline ShaderUniformValue<bool>::ShaderUniformValue(const std::string& name, const bool& value) :
    ShaderUniform(name, ShaderUniformType::Bool),
    mValue(value)
{
}

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
const T&
ShaderUniformValue<T>::GetValue() const
{
    return mValue;
}

template <typename T>
void
ShaderUniformValue<T>::SetValue(const T& value)
{
    mValue = value;
}

template <typename T>
using ShaderUniformValueSp = std::shared_ptr<ShaderUniformValue<T>>;
}
