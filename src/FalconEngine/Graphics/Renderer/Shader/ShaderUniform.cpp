#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

#include <FalconEngine/Core/Exception.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ShaderUniform::ShaderUniform(const std::string& name, ShaderUniformType type) :
    mEnabled(true),
    mName(name),
    mInitialized(false),
    // NOTE(Wuxiang): Because 0 is a valid value for uniform in OpenGL. You got
    // to have a invalid value for initialization.
    mLocation(-1),
    mType(type),
    mValueIsCurrent(true)
{
}

ShaderUniform::~ShaderUniform()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
ShaderUniform::IsUpdateNeeded() const
{
    return !mValueIsCurrent;
}

void
ShaderUniform::Update(const Camera * /* camera */, const Visual * /* visual */)
{
    FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
}

}
