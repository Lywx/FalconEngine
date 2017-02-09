#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <functional>
#include <map>
#include <vector>

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

typedef std::map<std::string, ShaderUniform *> ShaderUniformTable;
typedef std::map<std::string, std::unique_ptr<ShaderUniform>> ShaderUniformHandleTable;
typedef std::vector<ShaderUniform *> ShaderUniformVector;

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

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
template <>
inline ShaderUniformValue<float>::ShaderUniformValue(const std::string& name, const float& value) :
    ShaderUniform(name, ShaderUniformType::Float),
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
