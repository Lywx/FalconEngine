#include <FalconEngine/Graphics/Renderers/VisualEffect.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VisualEffect, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualEffect::VisualEffect()
{
}

VisualEffect::~VisualEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
VisualEffect::InsertPass(VisualPassHandle pass)
{
    mPassHandleVector.push_back(move(pass));
}

VisualPass *
VisualEffect::GetPass(int passIndex)
{
    return mPassHandleVector.at(passIndex).get();
}

int
VisualEffect::GetPassNum() const
{
    return int(mPassHandleVector.size());
}

Shader *
VisualEffect::GetShader(int passIndex)
{
    return mPassHandleVector.at(passIndex)->GetShader();
}

BlendState *
VisualEffect::GetBlendState(int passIndex)
{
    return mPassHandleVector.at(passIndex)->GetBlendState();
}

CullState *
VisualEffect::GetCullState(int passIndex)
{
    return mPassHandleVector.at(passIndex)->GetCullState();
}

DepthTestState *
VisualEffect::GetDepthTestState(int passIndex)
{
    return mPassHandleVector.at(passIndex)->GetDepthTestState();
}

OffsetState *
VisualEffect::GetOffsetState(int passIndex)
{
    return mPassHandleVector.at(passIndex)->GetOffsetState();
}

StencilTestState *
VisualEffect::GetStencilTestState(int passIndex)
{
    return mPassHandleVector.at(passIndex)->GetStencilTestState();
}

WireframeState *
VisualEffect::GetWireframeState(int passIndex)
{
    return mPassHandleVector.at(passIndex)->GetWireframeState();
}

VisualEffectSharedPtr
VisualEffect::GetSharedPtr()
{
    if (mEffect == nullptr)
    {
        mEffect = VisualEffectSharedPtr(this);
    }

    return mEffect;
}
}
