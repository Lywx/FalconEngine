#pragma once

#include <memory>

#include <FalconEngine/Graphics/GraphicsInclude.h>

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

class StencilTestState : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    StencilTestState ();
    virtual ~StencilTestState ();

    bool            mTestEnabled      = false;
    StencilFunction mCompareFunction  = StencilFunction::NEVER;
    unsigned int    mCompareReference = 0;
    unsigned int    mCompareMask      = UINT_MAX; // 0xFFFFFFFF
    unsigned int    mWriteMask        = UINT_MAX; // 0xFFFFFFFF

    StencilOperation OnStencilTestFail = StencilOperation::KEEP;
    StencilOperation OnDepthTestFail   = StencilOperation::KEEP;
    StencilOperation OnDepthTestPass   = StencilOperation::KEEP;
};

using StencilTestStateUniquePtr = std::unique_ptr<StencilTestState>;

}