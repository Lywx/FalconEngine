#include <FalconEngine/Platform/OpenGL/OpenGLStencilTestState.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformStencilTestFaceState::PlatformStencilTestFaceState() :
    mDepthTestFailOperation(0), mDepthTestPassOperation(0),
    mStencilTestFailOperation(0), mStencilCompareFunction(0)
{
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformStencilTestState::PlatformStencilTestState() :
    mStencilTestEnabled(false),
    mStencilCompareReference(0),
    mStencilCompareMask(0),
    mStencilWriteMask(0),
    mStencilFrontFace(),
    mStencilBackFace()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformStencilTestState::InitializeFaceState(
    _IN_ GLenum face,
    _IN_ const StencilTestFaceState &faceState,
    _OUT_ PlatformStencilTestFaceState& faceStatePlatform)
{
    faceStatePlatform.mStencilCompareFunction = OpenGLStencilFunction[
             StencilFunctionIndex(faceState.mStencilCompareFunction)];
    faceStatePlatform.mStencilTestFailOperation = OpenGLStencilOperation[
             StencilOperationIndex(faceState.mStencilTestFailOperation)];
    faceStatePlatform.mDepthTestFailOperation = OpenGLStencilOperation[
             StencilOperationIndex(faceState.mDepthTestFailOperation)];
    faceStatePlatform.mDepthTestPassOperation = OpenGLStencilOperation[
             StencilOperationIndex(faceState.mDepthTestPassOperation)];

    glStencilFuncSeparate(face,
                          faceStatePlatform.mStencilCompareFunction,
                          mStencilCompareReference,
                          mStencilCompareMask);
    glStencilOpSeparate(face,
                        faceStatePlatform.mStencilTestFailOperation,
                        faceStatePlatform.mDepthTestFailOperation,
                        faceStatePlatform.mDepthTestPassOperation);
}

void
PlatformStencilTestState::Initialize(const StencilTestState *stencilTestState)
{
    mStencilTestEnabled = stencilTestState->mEnabled;
    mStencilCompareReference = stencilTestState->mCompareReference;
    mStencilCompareMask = stencilTestState->mCompareMask;
    mStencilWriteMask = stencilTestState->mWriteMask;

    InitializeFaceState(GL_FRONT, stencilTestState->mFrontFace, mStencilFrontFace);
    InitializeFaceState(GL_BACK, stencilTestState->mBackFace, mStencilBackFace);

    mStencilTestEnabled ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
    glStencilMask(mStencilWriteMask);
}

void
PlatformStencilTestState::Set(const StencilTestState *stencilTestState)
{
    if (stencilTestState->mEnabled)
    {
        if (!mStencilTestEnabled)
        {
            mStencilTestEnabled = true;
            glEnable(GL_STENCIL_TEST);
        }

        if (unsigned int(stencilTestState->mWriteMask) != mStencilWriteMask)
        {
            mStencilWriteMask = unsigned int(stencilTestState->mWriteMask);
            glStencilMask(stencilTestState->mWriteMask);
        }

        bool compareMaskChanged = false;
        if (unsigned int(stencilTestState->mCompareMask) != mStencilCompareMask)
        {
            mStencilCompareMask = unsigned int(stencilTestState->mCompareMask);
            compareMaskChanged = true;
        }

        bool compareReferenceChanged = false;
        if (stencilTestState->mCompareReference != mStencilCompareReference)
        {
            mStencilCompareReference = stencilTestState->mCompareReference;
            compareReferenceChanged = true;
        }

        SetFaceState(GL_FRONT,
                     stencilTestState->mFrontFace,
                     mStencilFrontFace,
                     compareMaskChanged,
                     compareReferenceChanged);

        SetFaceState(GL_BACK,
                     stencilTestState->mBackFace,
                     mStencilBackFace,
                     compareMaskChanged,
                     compareReferenceChanged);
    }
    else if (mStencilTestEnabled)
    {
        mStencilTestEnabled = false;
        glDisable(GL_STENCIL_TEST);
    }
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformStencilTestState::SetFaceState(
    _IN_ GLenum face,
    _IN_ const StencilTestFaceState& faceStateCurrent,
    _IN_OUT_ PlatformStencilTestFaceState& faceStatePlatform,
    _IN_ bool compareMaskChanged,
    _IN_ bool compareReferenceChanged)
{
    GLenum compareFunction = OpenGLStencilFunction[StencilFunctionIndex(
                                 faceStateCurrent.mStencilCompareFunction)];
    if (compareFunction != faceStatePlatform.mStencilCompareFunction
            || compareMaskChanged
            || compareReferenceChanged)
    {
        faceStatePlatform.mStencilCompareFunction = compareFunction;
        glStencilFuncSeparate(face,
                              compareFunction,
                              mStencilCompareReference,
                              mStencilCompareMask);
    }

    GLenum stencilTestFailOperation = OpenGLStencilOperation[StencilOperationIndex(
                                          faceStateCurrent.mStencilTestFailOperation)];
    GLenum depthTestFailOperation = OpenGLStencilOperation[StencilOperationIndex(
                                        faceStateCurrent.mDepthTestFailOperation)];
    GLenum depthTestPassOperation = OpenGLStencilOperation[StencilOperationIndex(
                                        faceStateCurrent.mDepthTestPassOperation)];
    if (stencilTestFailOperation != faceStatePlatform.mStencilTestFailOperation
            || depthTestFailOperation != faceStatePlatform.mDepthTestFailOperation
            || depthTestPassOperation != faceStatePlatform.mDepthTestPassOperation)
    {
        faceStatePlatform.mStencilTestFailOperation = stencilTestFailOperation;
        faceStatePlatform.mDepthTestFailOperation = depthTestFailOperation;
        faceStatePlatform.mDepthTestPassOperation = depthTestPassOperation;
        glStencilOpSeparate(face,
                            stencilTestFailOperation,
                            depthTestFailOperation,
                            depthTestPassOperation);
    }
}

}

#endif
