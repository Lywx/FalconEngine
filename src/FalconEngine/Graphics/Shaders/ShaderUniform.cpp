#include <FalconEngine/Graphics/Shaders/ShaderUniform.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(ShaderUniform, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ShaderUniform::ShaderUniform(const std::string name, ShaderUniformType type) :
    mName(name),
    mLocation(0),
    mType(type),
    mUpdated(true)
{
}

ShaderUniform::~ShaderUniform()
{
}
}
