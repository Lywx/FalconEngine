#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <functional>
#include <map>
#include <vector>
#include <unordered_map>

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

using ShaderUniformUpdatePrototype = void(const Visual *, const Camera *);
using ShaderUniformUpdateFunction = std::function<ShaderUniformUpdatePrototype>;
class ShaderUniform : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ShaderUniform(const std::string name, ShaderUniformType type);
    virtual ~ShaderUniform();

public:
    std::string       mName;
    int               mLocation;
    ShaderUniformType mType;
    bool              mUpdated;
};

using ShaderUniformTable = std::unordered_map<std::string, ShaderUniform>;
using ShaderUniformSharedPtr = std::shared_ptr<ShaderUniform>;
using ShaderUniformPtrVector = std::vector<ShaderUniformSharedPtr>;

template<typename T>
class ShaderUniformValue : public ShaderUniform
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    ShaderUniformValue(const std::string& name, const T& value);
    virtual ~ShaderUniformValue();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    const T& GetValue() const;

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
