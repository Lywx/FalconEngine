#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <FalconEngine/Graphics/Renderers/VisualEffect.h>
#include <FalconEngine/Graphics/Renderers/VisualEffectInstance.h>

namespace FalconEngine
{

class BitmapFont;

class BitmapFontVertex
{
public:
    Vector2f mPosition;
    Vector2f mTexCoord;
    Vector4f mFontColor;
    float    mFontWidth;
    float    mFontEdge;
    float    mFontPage;
};

class BitmapFontEffect : public VisualEffect
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    BitmapFontEffect(const Handedness *handedness);
    virtual ~BitmapFontEffect();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Add required parameters to the existing visual effect instance.
    VisualEffectInstance *
    CreateInstance(VisualEffectInstance *instance, const BitmapFont *font, int width, int height) const;

    // @summary Create a new visual effect instance.
    VisualEffectInstance *
    CreateInstance(const BitmapFont *font, int width, int height);

private:
    const Handedness *mCameraHandedness;
    Matrix4f          mCameraProjection;
};

}
