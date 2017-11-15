#pragma once

#include <FalconEngine/Core/Common.h>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>

#include <FalconEngine/Math/Handedness.h>
#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

class Font;

#pragma pack(push, 1)
class FontVertex
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

class FALCON_ENGINE_API FontEffectParams : public VisualEffectParams
{
public:
    FontEffectParams(const Font *font, const Handedness *handedness) :
        mFont(font),
        mHandedness(handedness)
    {
    }

public:
    const Font       *mFont;
    const Handedness *mHandedness;
};

// @summary Implements a signed distanced field based bitmap font rendering effect.
class FALCON_ENGINE_API FontEffect : public VisualEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(FontEffect);

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit FontEffect();
    virtual ~FontEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    CreateInstance(_IN_OUT_ Visual                                  *visual,
                   _IN_     const std::shared_ptr<FontEffectParams>& params);

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormatSp() const override;

protected:
    virtual std::shared_ptr<VertexFormat>
    CreateVertexFormat() const override;

    // @summary Add required parameters to the existing visual effect instance.
    void
    InitializeInstance(_IN_OUT_ VisualEffectInstance             *instance,
                       _IN_     std::shared_ptr<FontEffectParams> params) const;
};

}
