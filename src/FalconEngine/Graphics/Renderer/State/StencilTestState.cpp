#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>

namespace FalconEngine
{

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
