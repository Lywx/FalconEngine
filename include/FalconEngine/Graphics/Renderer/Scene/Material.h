#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>

#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

class Texture2d;

class Material : public Object
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
    Color            mDiffuseColor = ColorPalette::Transparent;;
    Color            mEmissiveColor = ColorPalette::Transparent;;
    Color            mSpecularColor = ColorPalette::Transparent;;
    Color            mShininessColor = ColorPalette::Transparent;;

    const Texture2d *mAmbientTexture = nullptr;
    const Texture2d *mDiffuseTexture = nullptr;
    const Texture2d *mEmissiveTexture = nullptr;
    const Texture2d *mSpecularTexture = nullptr;
    const Texture2d *mShininessTexture = nullptr;
};

}
