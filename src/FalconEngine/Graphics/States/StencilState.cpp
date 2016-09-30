#include <FalconEngine/Graphics/States/StencilState.h>

namespace FalconEngine {

FALCON_ENGINE_IMPLEMENT_RTTI(StencilState, Object);

StencilState::StencilState() :
    StencilTestEnabled(false),
    StencilFunction(StencilFunction::NEVER),
    StencilReference(0),
    StencilMask(UINT_MAX),
    StencilWriteMask(UINT_MAX),
    OnStencilTestFail(StencilOperation::KEEP),
    OnDepthTestFail(StencilOperation::KEEP),
    OnDepthTestPass(StencilOperation::KEEP)
{
}

StencilState::~StencilState()
{
}


}
