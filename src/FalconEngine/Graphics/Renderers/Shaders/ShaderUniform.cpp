#include <FalconEngine/Graphics/Renderers/Shaders/ShaderUniform.h>

namespace FalconEngine
{

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

void
ShaderUniform::Update(const Visual *visual, const Camera *camera)
{
}

}
