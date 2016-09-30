#include <FalconEngine/Graphics/States/OffsetState.h>

namespace FalconEngine {

FALCON_ENGINE_IMPLEMENT_RTTI(OffsetState, Object);

OffsetState::OffsetState () :
    OffsetFillEnabled(false),
    OffsetLineEnabled(false),
    OffsetPointEnabled(false),
    OffsetFactor(0.0f),
    OffsetUnit(0.0f)
{
}

OffsetState::~OffsetState ()
{
}

}
