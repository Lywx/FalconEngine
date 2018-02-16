#include <FalconEngine/Platform/OpenGL/OpenGLOffsetState.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformOffsetState::PlatformOffsetState() :
    mOffsetFillEnabled(false),
    mOffsetLineEnabled(false), mOffsetPointEnabled(false), mOffsetFactor(0),
    mOffsetUnit(0)

{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformOffsetState::Initialize(const OffsetState *offsetState)
{
    mOffsetFillEnabled = offsetState->mFillEnabled;
    mOffsetLineEnabled = offsetState->mLineEnabled;
    mOffsetPointEnabled = offsetState->mPointEnabled;
    mOffsetFactor = offsetState->mBiasFactor;
    mOffsetUnit = offsetState->mBiasUnit;

    mOffsetFillEnabled ? glEnable(GL_POLYGON_OFFSET_FILL) : glDisable(GL_POLYGON_OFFSET_FILL);
    mOffsetLineEnabled ? glEnable(GL_POLYGON_OFFSET_LINE) : glDisable(GL_POLYGON_OFFSET_LINE);
    mOffsetPointEnabled ? glEnable(GL_POLYGON_OFFSET_POINT) : glDisable(GL_POLYGON_OFFSET_POINT);
    glPolygonOffset(mOffsetFactor, mOffsetUnit);
}

void
PlatformOffsetState::Set(const OffsetState *offsetState)
{
    if (offsetState->mFillEnabled)
    {
        if (!mOffsetFillEnabled)
        {
            mOffsetFillEnabled = true;
            glEnable(GL_POLYGON_OFFSET_FILL);
        }
    }
    else if (mOffsetFillEnabled)
    {
        mOffsetFillEnabled = false;
        glDisable(GL_POLYGON_OFFSET_FILL);
    }

    if (offsetState->mLineEnabled)
    {
        if (!mOffsetLineEnabled)
        {
            mOffsetLineEnabled = true;
            glEnable(GL_POLYGON_OFFSET_LINE);
        }
    }
    else if (mOffsetLineEnabled)
    {
        mOffsetLineEnabled = false;
        glDisable(GL_POLYGON_OFFSET_LINE);
    }

    if (offsetState->mPointEnabled)
    {
        if (!mOffsetPointEnabled)
        {
            mOffsetPointEnabled = true;
            glEnable(GL_POLYGON_OFFSET_POINT);
        }
    }
    else if (mOffsetPointEnabled)
    {
        mOffsetPointEnabled = false;
        glDisable(GL_POLYGON_OFFSET_POINT);
    }

    if (offsetState->mBiasFactor != mOffsetFactor
            || offsetState->mBiasUnit != mOffsetUnit)
    {
        mOffsetFactor = offsetState->mBiasFactor;
        mOffsetUnit = offsetState->mBiasUnit;
        glPolygonOffset(offsetState->mBiasFactor, offsetState->mBiasUnit);
    }
}

}

#endif
