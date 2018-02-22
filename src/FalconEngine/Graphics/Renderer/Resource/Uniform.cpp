#include <FalconEngine/Graphics/Renderer/Resource/Uniform.h>

#include <FalconEngine/Core/Exception.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Uniform::Uniform(const std::string& name, UniformType type) :
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

Uniform::~Uniform()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
bool
Uniform::ShouldUpdate() const
{
    return !mValueIsCurrent;
}

void
Uniform::UpdateInternal(const Camera * /* camera */, const Visual * /* visual */)
{
    FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
}

}
