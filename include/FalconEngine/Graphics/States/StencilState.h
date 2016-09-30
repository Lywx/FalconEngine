#pragma once

#include <memory>

#include <FalconEngine/Core/Objects/Object.h>

namespace FalconEngine {

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

    ENUM_COUNT
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

    ENUM_COUNT,
};

class StencilState : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

public:
    StencilState ();
    virtual ~StencilState ();

    bool            StencilTestEnabled = false;
    StencilFunction StencilFunction    = StencilFunction::NEVER;
    unsigned int    StencilReference   = 0;
    unsigned int    StencilMask        = UINT_MAX; // 0xFFFFFFFF
    unsigned int    StencilWriteMask   = UINT_MAX; // 0xFFFFFFFF

    StencilOperation OnStencilTestFail = StencilOperation::KEEP;
    StencilOperation OnDepthTestFail   = StencilOperation::KEEP;
    StencilOperation OnDepthTestPass   = StencilOperation::KEEP;
};

typedef std::shared_ptr<StencilState> StencilStatePtr;

}