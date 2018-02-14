#pragma once

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

enum class BlendFactor
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

    // NOTE(Wuxiang): Not supported in Direct3D.
    // CONSTANT_ALPHA,
    // ONE_MINUS_CONSTANT_ALPHA,

    SRC_ALPHA_SATURATE,
    SRC1_COLOR,
    ONE_MINUS_SRC1_COLOR,
    SRC1_ALPHA,
    ONE_MINUS_SRC1_ALPHA,

    Count
};

inline int
BlendFactorIndex(BlendFactor blendFactor)
{
    return int(blendFactor);
}

enum class BlendOperator
{
    Add,
    Subtract,
    ReverseSubtract,
    Min,
    Max,

    Count,
};

inline int
BlendOperatorIndex(BlendOperator blendOperator)
{
    return int(blendOperator);
}

enum class LogicOperator
{
    Clear,
    Set,
    Copy,
    CopyInverted,
    Noop,
    Invert,
    And,
    Nand,
    Or,
    Nor,
    Xor,
    Equiv,
    AndReverse,
    AndInverted,
    OrReverse,
    OrInverted,

    Count
};

inline int
LogicOperatorIndex(LogicOperator logicOperator)
{
    return int(logicOperator);
}

FALCON_ENGINE_CLASS_BEGIN BlendState final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    BlendState();
    ~BlendState();

public:
    bool mEnabled = false;
    BlendOperator mOperator = BlendOperator::Add;
    BlendOperator mOperatorAlpha = BlendOperator::Add;
    BlendFactor mSourceFactor = BlendFactor::ONE;
    BlendFactor mSourceFactorAlpha = BlendFactor::ONE;
    BlendFactor mDestinationFactor = BlendFactor::ZERO;
    BlendFactor mDestinationFactorAlpha = BlendFactor::ZERO;
    Vector4f mConstantFactor = Vector4f::Zero;

    bool mLogicEnabled = false;
    LogicOperator mLogicOperator = LogicOperator::Copy;
};
FALCON_ENGINE_CLASS_END

}
