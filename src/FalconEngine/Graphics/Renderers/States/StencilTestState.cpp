#include <FalconEngine/Graphics/Renderers/States/StencilTestState.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(StencilTestState, Object);

StencilTestState::StencilTestState() :
    mTestEnabled(false),
    mCompareFunction(StencilFunction::NEVER),
    mCompareReference(0),
    mCompareMask(UINT_MAX),
    mWriteMask(UINT_MAX),
    OnStencilTestFail(StencilOperation::KEEP),
    OnDepthTestFail(StencilOperation::KEEP),
    OnDepthTestPass(StencilOperation::KEEP)
{
}

StencilTestState::~StencilTestState()
{
}


}