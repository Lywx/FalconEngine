#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Math/Handedness.h>
#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

class BitmapFont;

class VertexFormat;
using VertexFormatSharedPtr = std::shared_ptr<VertexFormat>;

#pragma pack(push, 1)
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
#pragma pack(pop)

class BitmapFontEffect : public VisualEffect
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit BitmapFontEffect(const Handedness *handedness);
    virtual ~BitmapFontEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Add required parameters to the existing visual effect instance.
    void
    CreateInstance(
        _IN_OUT_ VisualEffectInstance *instance,
        _IN_     const BitmapFont     *font, int width, int height) const;

    VertexFormatSharedPtr
    CreateVertexFormat();

private:
    const Handedness *mCameraHandedness;
    Matrix4f          mCameraProjection;
};

using BitmapFontEffectSharedPtr = std::shared_ptr<BitmapFontEffect>;
}
