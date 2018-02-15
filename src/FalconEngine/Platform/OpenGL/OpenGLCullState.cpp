#include <FalconEngine/Platform/OpenGL/OpenGLCullState.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/State/CullState.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformCullState::PlatformCullState():
    mCullEnabled(false), mCullCounterClockwise(false)
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformCullState::Initialize(const CullState *cullState)
{
    mCullEnabled = cullState->mEnabled;
    mCullCounterClockwise = cullState->mCounterClockwise;

    mCullEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(mCullCounterClockwise ? GL_FRONT : GL_BACK);
}

void
PlatformCullState::Set(const CullState *cullState)
{
    if (cullState->mEnabled)
    {
        if (!mCullEnabled)
        {
            mCullEnabled = true;
            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CCW);
            glCullFace(GL_BACK);
        }

        bool cullCounterClockwise = cullState->mCounterClockwise;
        if (cullCounterClockwise != mCullCounterClockwise)
        {
            mCullCounterClockwise = cullCounterClockwise;
            if (mCullCounterClockwise)
            {
                glCullFace(GL_FRONT);
            }
            else
            {
                glCullFace(GL_BACK);
            }
        }
    }
    else if (mCullEnabled)
    {
        mCullEnabled = false;
        glDisable(GL_CULL_FACE);
    }
}

}

#endif
