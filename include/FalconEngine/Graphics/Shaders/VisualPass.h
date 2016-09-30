#pragma once

#include <memory>

#include <FalconEngine/Core/Objects/Object.h>

#include <FalconEngine/Graphics/Shaders/Shader.h>

#include <FalconEngine/Graphics/States/BlendState.h>
#include <FalconEngine/Graphics/States/CullState.h>
#include <FalconEngine/Graphics/States/DepthState.h>
#include <FalconEngine/Graphics/States/OffsetState.h>
#include <FalconEngine/Graphics/States/StencilState.h>
#include <FalconEngine/Graphics/States/WireframeState.h>

namespace FalconEngine {

class VisualPass : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

public:
    VisualPass();
    virtual ~VisualPass();

    ShaderPtr Shader;

    BlendStatePtr     BlendState;
    CullStatePtr      CullState;
    DepthStatePtr     DepthState;
    OffsetStatePtr    OffsetState;
    StencilStatePtr   StencilState;
    WireframeStatePtr WireframeState;
};

typedef std::shared_ptr<VisualPass> VisualPassPtr;
#include "VisualPass.inl"

}
