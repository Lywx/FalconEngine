#pragma once

#include <memory>

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Math/Vector4f.h>

namespace FalconEngine
{

enum class BlendFactorSource
{
    ZERO,
    ONE,
    SRC_COLOR,
    ONE_MINUS_SRC_COLOR,
    DST_COLOR,
    ONE_MINUS_DST_COLOR,
    SRC_ALPHA,
    ONE_MINUS_SRC_ALPHA,
    DST_ALPHA,
    ONE_MINUS_DST_ALPHA,
    CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA,
    SRC_ALPHA_SATURATE,
    SRC1_COLOR,
    ONE_MINUS_SRC1_COLOR,
    SRC1_ALPHA,
    ONE_MINUS_SRC1_ALPHA,

    Count
};

enum class BlendFactorDestination
{
    ZERO,
    ONE,
    SRC_COLOR,
    ONE_MINUS_SRC_COLOR,
    DST_COLOR,
    ONE_MINUS_DST_COLOR,
    SRC_ALPHA,
    ONE_MINUS_SRC_ALPHA,
    DST_ALPHA,
    ONE_MINUS_DST_ALPHA,
    CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA,
    SRC_ALPHA_SATURATE,
    SRC1_COLOR,
    ONE_MINUS_SRC1_COLOR,
    SRC1_ALPHA,
    ONE_MINUS_SRC1_ALPHA,

    Count
};

class BlendState : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

public:
    BlendState ();
    virtual ~BlendState ();

    bool                   BlendEnabled           = false;
    BlendFactorSource      BlendSourceFactor      = BlendFactorSource::SRC_ALPHA;
    BlendFactorDestination BlendDestinationFactor = BlendFactorDestination::ONE_MINUS_CONSTANT_ALPHA;  // default: DBM_ONE_MINUS_SRC_ALPHA
    Vector4f               BlendConstantFactor    = Vector4f::Zero;
};

typedef std::shared_ptr<BlendState> BlendStatePtr;

}
