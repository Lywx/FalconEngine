#include <FalconEngine/Platform/OpenGL/OpenGLWireframeState.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformWireframeState::PlatformWireframeState() :
    mWireframeEnabled(false)
{

}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformWireframeState::Initialize(const WireframeState *wireframeState)
{
    mWireframeEnabled = wireframeState->mEnabled;

    glPolygonMode(GL_FRONT_AND_BACK, mWireframeEnabled ? GL_LINE : GL_FILL);
}

void
PlatformWireframeState::Set(const WireframeState *wireframeState)
{
    if (wireframeState->mEnabled)
    {
        if (!mWireframeEnabled)
        {
            mWireframeEnabled = true;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
    }
    else if (mWireframeEnabled)
    {
        mWireframeEnabled = false;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
}

#endif
