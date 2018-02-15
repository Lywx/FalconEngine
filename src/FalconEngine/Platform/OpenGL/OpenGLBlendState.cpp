#include <FalconEngine/Platform/OpenGL/OpenGLBlendState.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>

namespace FalconEngine
{
/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformBlendState::PlatformBlendState():
    mBlendEnabled(false), mBlendSourceFactor(0), mBlendSourceFactorAlpha(0),
    mBlendDestinationFactor(0), mBlendDestinationFactorAlpha(0), mBlendOperator(0),
    mBlendOperatorAlpha(0), mLogicEnabled(false), mLogicOperator(0)
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformBlendState::Initialize(const BlendState *blendState)
{
    mBlendEnabled = blendState->mEnabled;
    mBlendSourceFactorAlpha = OpenGLBlendFactor[BlendFactorIndex(blendState->mSourceFactorAlpha)];
    mBlendSourceFactor = OpenGLBlendFactor[BlendFactorIndex(blendState->mSourceFactor)];
    mBlendDestinationFactorAlpha = OpenGLBlendFactor[BlendFactorIndex(blendState->mDestinationFactorAlpha)];
    mBlendDestinationFactor = OpenGLBlendFactor[BlendFactorIndex(blendState->mDestinationFactor)];
    mBlendConstantFactor = blendState->mConstantFactor;
    mBlendOperator = OpenGLBlendOperator[BlendOperatorIndex(blendState->mOperator)];
    mLogicEnabled = blendState->mLogicEnabled;
    mLogicOperator = OpenGLLogicOperator[LogicOperatorIndex(blendState->mLogicOperator)];

    mBlendEnabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
    glBlendColor(mBlendConstantFactor[0], mBlendConstantFactor[1], mBlendConstantFactor[2],
                 mBlendConstantFactor[3]);
    glBlendFuncSeparate(mBlendSourceFactor, mBlendDestinationFactor,
                        mBlendSourceFactorAlpha, mBlendDestinationFactorAlpha);
    glBlendEquation(mBlendOperator);
    mLogicEnabled ? glEnable(GL_COLOR_LOGIC_OP) : glDisable(GL_COLOR_LOGIC_OP);
    glLogicOp(mLogicOperator);
}

void
PlatformBlendState::Set(const BlendState *blendState)
{
    if (blendState->mEnabled)
    {
        if (!mBlendEnabled)
        {
            mBlendEnabled = true;
            glEnable(GL_BLEND);
        }

        GLenum sourceFactorAlpha = OpenGLBlendFactor[BlendFactorIndex(blendState->mSourceFactorAlpha)];
        GLenum sourceFactor = OpenGLBlendFactor[BlendFactorIndex(blendState->mSourceFactor)];
        GLenum destinationFactor = OpenGLBlendFactor[BlendFactorIndex(blendState->mDestinationFactor)];
        GLenum destinationFactorAlpha = OpenGLBlendFactor[BlendFactorIndex(blendState->mDestinationFactorAlpha)];
        if (sourceFactor != mBlendSourceFactor
                || sourceFactorAlpha != mBlendSourceFactorAlpha
                || destinationFactor != mBlendDestinationFactor
                || destinationFactorAlpha != mBlendDestinationFactorAlpha)
        {
            mBlendSourceFactor = sourceFactor;
            mBlendSourceFactorAlpha = sourceFactorAlpha;
            mBlendDestinationFactor = destinationFactor;
            mBlendDestinationFactorAlpha = destinationFactorAlpha;
            glBlendFuncSeparate(sourceFactor, destinationFactor, sourceFactorAlpha, destinationFactorAlpha);
        }

        if (blendState->mConstantFactor != mBlendConstantFactor)
        {
            mBlendConstantFactor = blendState->mConstantFactor;
            glBlendColor(
                mBlendConstantFactor[0],
                mBlendConstantFactor[1],
                mBlendConstantFactor[2],
                mBlendConstantFactor[3]);
        }

        auto blendOperator = OpenGLBlendOperator[BlendOperatorIndex(blendState->mOperator)];
        auto blendOperatorAlpha = OpenGLBlendOperator[BlendOperatorIndex(blendState->mOperatorAlpha)];
        if (blendOperator != mBlendOperator
                || blendOperatorAlpha != mBlendOperatorAlpha)
        {
            mBlendOperator = blendOperator;
            mBlendOperatorAlpha = blendOperatorAlpha;
            glBlendEquationSeparate(blendOperator, blendOperatorAlpha);
        }

        if (blendState->mLogicEnabled)
        {
            if (!mLogicEnabled)
            {
                mLogicEnabled = true;
                glEnable(GL_COLOR_LOGIC_OP);
            }

            auto logicOperator = OpenGLLogicOperator[LogicOperatorIndex(blendState->mLogicOperator)];
            if (logicOperator != mLogicOperator)
            {
                mLogicOperator = logicOperator;
                glLogicOp(logicOperator);
            }
        }
        else if (mLogicEnabled)
        {
            mLogicEnabled = false;
            glDisable(GL_COLOR_LOGIC_OP);
        }
    }
    else if (mBlendEnabled)
    {
        mBlendEnabled = false;
        glDisable(GL_BLEND);
    }
}

}

#endif
