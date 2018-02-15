#include <FalconEngine/Platform/OpenGL/OpenGLDepthTestState.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformDepthTestState::PlatformDepthTestState() :
    mDepthTestEnabled(false),
    mDepthWriteEnabled(false),
    mDepthCompareFunction(0)
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformDepthTestState::Initialize(const DepthTestState *depthTestState)
{
    mDepthTestEnabled = depthTestState->mEnabled;
    mDepthWriteEnabled = depthTestState->mWriteEnabled;
    mDepthCompareFunction = OpenGLDepthFunction[int(depthTestState->mCompareFunction)];

    mDepthTestEnabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

    // You still need to have to enable depth test to enable writing to depth buffer
    glDepthMask(mDepthWriteEnabled ? GL_TRUE : GL_FALSE);
    glDepthFunc(mDepthCompareFunction);
}

void
PlatformDepthTestState::Set(const DepthTestState *depthTestState)
{
    if (depthTestState->mEnabled)
    {
        if (!mDepthTestEnabled)
        {
            mDepthTestEnabled = true;
            glEnable(GL_DEPTH_TEST);
        }

        GLenum compareFunction = OpenGLDepthFunction[int(depthTestState->mCompareFunction)];
        if (compareFunction != mDepthCompareFunction)
        {
            mDepthCompareFunction = compareFunction;
            glDepthFunc(compareFunction);
        }
    }
    else if (mDepthTestEnabled)
    {
        mDepthTestEnabled = false;
        glDisable(GL_DEPTH_TEST);
    }

    if (depthTestState->mWriteEnabled)
    {
        if (!mDepthWriteEnabled)
        {
            mDepthWriteEnabled = true;
            glDepthMask(GL_TRUE);
        }
    }
    else if (mDepthWriteEnabled)
    {
        mDepthWriteEnabled = false;
        glDepthMask(GL_FALSE);
    }
}

}

#endif
