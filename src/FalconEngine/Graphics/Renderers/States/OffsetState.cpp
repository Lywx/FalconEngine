#include <FalconEngine/Graphics/Renderers/States/OffsetState.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(OffsetState, Object);

OffsetState::OffsetState () :
    mFillEnabled(false),
    mLineEnabled(false),
    mPointEnabled(false),
    mFactor(0.0f),
    mUnit(0.0f)
{
}

OffsetState::~OffsetState ()
{
}

}
