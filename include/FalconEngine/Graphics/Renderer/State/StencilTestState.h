#pragma once

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Math/Type.h>

namespace FalconEngine
{

enum class StencilFunction
{
    NEVER,
    ALWAYS,
    LESS,
    LESS_EQUAL,
    EQUAL,
    GREATER_EQUAL,
    GREATER,
    NOT_EQUAL,

    Count
};

inline int
StencilFunctionIndex(StencilFunction stencilFunction)
{
    return int(stencilFunction);
}

enum class StencilOperation
{
    KEEP,
    ZERO,
    REPLACE,
    INCREMENT,
    DECREMENT,
    INVERT,
    INCREMENT_WRAP,
    DECREMENT_WRAP,

    Count,
};

inline int
StencilOperationIndex(StencilOperation stencilOperation)
{
    return int(stencilOperation);
}

FALCON_ENGINE_CLASS_BEGIN
StencilTestFaceState
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    StencilTestFaceState() = default;
    ~StencilTestFaceState() = default;

public:
    // When stencil test passes, depth test fails.
    StencilOperation mDepthTestFailOperation = StencilOperation::KEEP;

    // When stencil test passes depth test passes.
    StencilOperation mDepthTestPassOperation = StencilOperation::KEEP;

    // When stencil test fails.
    StencilOperation mStencilTestFailOperation = StencilOperation::KEEP;

    StencilFunction mStencilCompareFunction = StencilFunction::NEVER;
};
FALCON_ENGINE_CLASS_END

FALCON_ENGINE_CLASS_BEGIN StencilTestState final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    StencilTestState();
    ~StencilTestState();

public:
    bool mEnabled = false;

    // NOTE(Wuxiang): OpenGL use 32 bit int but Direct3D 11 use 32 bit
    // unsigned int here. So we have to accommodate for both by using 31 bit
    // unsigned int, which is not possible so that you have to carefully use this
    // parameter.
    unsigned int mCompareReference = 0;

    // NOTE(Wuxiang): Although OpenGL support separate compare and write mask for
    // both face, Direct3D 11 doesn't support this. So we are taking GCD here.
    // OpenGL supports 32 bit mask, but Direct3D 11 only supports 8 bit mask.
    Uint8 mCompareMask = UINT8_MAX; // 0xFF
    Uint8 mWriteMask = UINT8_MAX; // 0xFF

    StencilTestFaceState mFrontFace;
    StencilTestFaceState mBackFace;
};
FALCON_ENGINE_CLASS_END

}