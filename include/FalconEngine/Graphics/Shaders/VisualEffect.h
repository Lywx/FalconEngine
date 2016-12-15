#pragma once

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Graphics/Shaders/VisualTechnique.h>

namespace FalconEngine {

class VisualEffect : public Object
{
public:
    VisualEffect();
    virtual ~VisualEffect();

    // TODO
    //// Support for deferred construction.  The function appends the new
    //// technique to the end of the array.
    //void InsertTechnique(VisualTechnique *technique);

    //// Member access.
    //inline int GetNumTechniques() const;
    //VisualTechnique *GetTechnique(int techniqueIndex) const;

    //// Access to components of the effect.
    //int GetNumPasses(int techniqueIndex) const;
    //VisualPass *GetPass(int techniqueIndex, int passIndex) const;
    //VertexShader *GetVertexShader(int techniqueIndex, int passIndex) const;
    //PixelShader *GetPixelShader(int techniqueIndex, int passIndex) const;
    //AlphaState *GetAlphaState(int techniqueIndex, int passIndex) const;
    //CullState *GetCullState(int techniqueIndex, int passIndex) const;
    //DepthState *GetDepthState(int techniqueIndex, int passIndex) const;
    //OffsetState *GetOffsetState(int techniqueIndex, int passIndex) const;
    //StencilState *GetStencilState(int techniqueIndex, int passIndex) const;
    //WireState *GetWireState(int techniqueIndex, int passIndex) const;

protected:
    //std::vector<VisualTechniquePtr> mTechniques;
};

typedef std::shared_ptr<VisualEffect> VisualEffectPtr;
#include "VisualEffect.inl"

}
