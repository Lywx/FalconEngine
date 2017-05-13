#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

class Texture2d;

class FALCON_ENGINE_API Material : public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Material();
    virtual ~Material() = default;

public:
    Color            mAmbientColor = ColorPalette::Transparent;
    Color            mDiffuseColor = ColorPalette::Transparent;
    Color            mEmissiveColor = ColorPalette::Transparent;
    Color            mSpecularColor = ColorPalette::Transparent;
    float            mShininess = 0.0f;

    const Texture2d *mAmbientTexture = nullptr;
    const Texture2d *mDiffuseTexture = nullptr;
    const Texture2d *mEmissiveTexture = nullptr;
    const Texture2d *mSpecularTexture = nullptr;
    const Texture2d *mShininessTexture = nullptr;
};

}
