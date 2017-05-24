#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>

#include <FalconEngine/Math/Handedness.h>
#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

class BitmapFont;

class VertexFormat;

#pragma pack(push, 1)
class SignedDistancedFieldFontVertex
{
public:
    Vector2f mPosition;
    Vector2f mTexCoord;
    Vector4f mFontColor;
    float    mFontWidth;
    float    mFontEdge;
    float    mFontPage;
};
#pragma pack(pop)

// @summary Implements a signed distanced field based bitmap font rendering effect.
class FALCON_ENGINE_API BitmapFontEffect : public VisualEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(BitmapFontEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit BitmapFontEffect();
    virtual ~BitmapFontEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    std::shared_ptr<VisualEffectInstance>
    CreateInstance(_IN_OUT_ Visual           *visual,
                   _IN_     const BitmapFont *font,
                   _IN_     const Handedness *handedness,
                   _IN_     int               viewportWidth,
                   _IN_     int               viewportHeight) const;

protected:
    virtual std::shared_ptr<VisualEffectInstance>
    CreateSetInstance(Visual *visual) const override;

    // @summary Add required parameters to the existing visual effect instance.
    void
    InitializeInstance(
        _IN_OUT_ VisualEffectInstance *visualEffectInstance,
        _IN_     const BitmapFont     *font,
        _IN_     const Handedness     *handedness,
        _IN_     int                   viewportWidth,
        _IN_     int                   viewportHeight) const;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;
};

}
