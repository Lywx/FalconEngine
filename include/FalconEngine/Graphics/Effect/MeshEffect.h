#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <functional>
#include <memory>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

class Visual;
class Mesh;
class Node;

class FALCON_ENGINE_API MeshEffectParams : public VisualEffectParams
{
public:
    Color mAmbientColor;
    Color mLineColor;
    float mLineWidth;
    bool  mTextureEnabled;
};

// @summary Implements material coloring with mesh visualization.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API MeshEffect : public VisualEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(MeshEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    MeshEffect();
    virtual ~MeshEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    CreateInstance(_IN_ Node                             *node,
                   _IN_ std::shared_ptr<MeshEffectParams> params) const;
protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    virtual std::shared_ptr<VertexFormat>
    CreateVertexFormat() const override;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;

    void
    InitializeInstance(_IN_OUT_ VisualEffectInstance             *instance,
                       _IN_     std::shared_ptr<Material>         material,
                       _IN_     std::shared_ptr<MeshEffectParams> params) const;

};
#pragma warning(default: 4251)

}
