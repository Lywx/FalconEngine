#pragma once

#include <vector>

#include <FalconEngine/Core/Objects/Object.h>
#include <FalconEngine/Graphics/Shaders/VisualPass.h>

namespace FalconEngine {

class VisualTechnique : public Object
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    VisualTechnique();
    virtual ~VisualTechnique();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
//    // Support for deferred creation. The function appends the new pass to
//    // the end of the array.
//    void InsertPass(VisualPass *pass);
//
//    // Member access.
//    inline int GetNumPasses() const;
//    VisualPass *GetPass(int passIndex) const;
//
//    // Access to components of the pass.
//    VertexShader *GetVertexShader(int passIndex) const;
//    PixelShader *GetPixelShader(int passIndex) const;
//    AlphaState *GetAlphaState(int passIndex) const;
//    CullState *GetCullState(int passIndex) const;
//    DepthState *GetDepthState(int passIndex) const;
//    OffsetState *GetOffsetState(int passIndex) const;
//    StencilState *GetStencilState(int passIndex) const;
//    WireState *GetWireState(int passIndex) const;
    // TODO
//
//protected:
//    std::vector<VisualPassPtr> mPasses;
};

//typedef std::shared_ptr<VisualTechnique> VisualTechniquePtr;
//#include "Wm5VisualTechnique.inl"

}
