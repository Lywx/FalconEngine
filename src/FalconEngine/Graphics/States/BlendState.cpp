#include <FalconEngine/Graphics/States/BlendState.h>

namespace FalconEngine {

FALCON_ENGINE_IMPLEMENT_RTTI(BlendState, Object);

BlendState::BlendState() :
    BlendEnabled(false),
    BlendSourceFactor(BlendFactorSource::SRC_ALPHA),
    BlendDestinationFactor(BlendFactorDestination::ONE_MINUS_SRC_ALPHA),
    BlendConstantFactor(0.0f, 0.0f, 0.0f, 0.0f)
{
}

BlendState::~BlendState ()
{
}

}
