#include <FalconEngine/Graphics/Renderer/States/OffsetState.h>

namespace FalconEngine
{

OffsetState::OffsetState() :
    mFillEnabled(false),
    mLineEnabled(false),
    mPointEnabled(false),
    mFactor(0.0f),
    mUnit(0.0f)
{
}

OffsetState::~OffsetState()
{
}

}
