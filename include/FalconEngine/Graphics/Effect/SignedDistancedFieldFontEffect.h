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

class FALCON_ENGINE_API SignedDistancedFieldFontEffect : public VisualEffect
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit SignedDistancedFieldFontEffect(const Handedness *handedness);
    virtual ~SignedDistancedFieldFontEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    // @summary Add required parameters to the existing visual effect instance.
    void
    CreateInstance(
        _IN_OUT_ VisualEffectInstance *instance,
        _IN_     const BitmapFont     *font, int width, int height) const;

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;

private:
    const Handedness *mCameraHandedness;
    Matrix4f          mCameraProjection;
};

}
