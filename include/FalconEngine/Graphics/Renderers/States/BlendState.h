#pragma once

#include <memory>

#include <FalconEngine/Graphics/GraphicsInclude.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

enum class BlendSourceFactor
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

enum class BlendDestinationFactor
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
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    BlendState();
    virtual ~BlendState ();

public:
    bool                   mEnabled           = false;
    BlendSourceFactor      mSourceFactor      = BlendSourceFactor::SRC_ALPHA;
    BlendDestinationFactor mDestinationFactor = BlendDestinationFactor::ONE_MINUS_CONSTANT_ALPHA;
    Vector4f               mConstantFactor    = Vector4f::Zero;
};

typedef std::unique_ptr<BlendState> BlendStateHandle;

}
