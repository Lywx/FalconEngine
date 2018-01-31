#pragma once

#include <FalconEngine/Core/Macro.h>

namespace FalconEngine
{

enum class StencilCompareFunctoin
{
    NEVER,
    LESS,
    EQUAL,
    LEQUAL,
    GREATER,
    NOTEQUAL,
    GEQUAL,
    ALWAYS,

    Count
};

enum class StencilFunction
{
    NEVER,
    ALWAYS,
    LESS,
    LEQUAL,

    EQUAL,
    GEQUAL,

    GREATER,
    NOTEQUAL,

    Count
};

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

class FALCON_ENGINE_API StencilTestState final
{
public:
    StencilTestState ();
    ~StencilTestState ();

public:
    bool            mTestEnabled      = false;
    StencilFunction mCompareFunction  = StencilFunction::NEVER;
    unsigned int    mCompareReference = 0;
    unsigned int    mCompareMask      = UINT_MAX; // 0xFFFFFFFF
    unsigned int    mWriteMask        = UINT_MAX; // 0xFFFFFFFF

    StencilOperation OnStencilTestFail = StencilOperation::KEEP;
    StencilOperation OnDepthTestFail   = StencilOperation::KEEP;
    StencilOperation OnDepthTestPass   = StencilOperation::KEEP;
};

}