#pragma once

#include <FalconEngine/Core/Macro.h>

#include <functional>
#include <memory>

#include <FalconEngine/Graphics/Renderer/Scene/Material.h>
#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>
#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

class Visual;
class Mesh;
class Node;

class FALCON_ENGINE_API MeshEffectParams : public VisualEffectParams
{
public:
    MeshEffectParams(Color ambientColor,
                     Color lineColor,
                     float lineWidth,
                     bool  textureEnabled) :
        mAmbientColor(ambientColor),
        mLineColor(lineColor),
        mLineWidth(lineWidth),
        mTextureEnabled(textureEnabled)
    {
    }

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
    CreateInstance(_IN_ Node                                    *node,
                   _IN_ const std::shared_ptr<MeshEffectParams>& params);
protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    virtual std::shared_ptr<VertexFormat>
    CreateVertexFormat() const override;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormatSp() const override;

    void
    InitializeInstance(_IN_OUT_ VisualEffectInstance                    *instance,
                       _IN_     const std::shared_ptr<Material>&         material,
                       _IN_     const std::shared_ptr<MeshEffectParams>& params) const;

};
#pragma warning(default: 4251)

}
