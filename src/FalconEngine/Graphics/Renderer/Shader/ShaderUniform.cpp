#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ShaderUniform::ShaderUniform(const std::string name, ShaderUniformType type) :
    mName(name),
    mEnabled(true),
    mLocation(0),
    mType(type),
    mUpdated(true)
{
}

ShaderUniform::~ShaderUniform()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
ShaderUniform::Update(const Camera * /* camera */, const Visual * /* visual */)
{
}

}
