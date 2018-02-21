#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Core/Object.h>
#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{
namespace Detail
{
#pragma pack(push, 4)
struct FALCON_ENGINE_API MaterialColorData
{
public:
    Vector3f Ambient;
    float Shininess;

    Vector3f Diffuse;
    float Pad0;

    Vector3f Emissive;
    float Pad1;

    Vector3f Specular;
    float Pad2;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct FALCON_ENGINE_API MaterialTextureData
{
    bool AmbientExist;
    bool DiffuseExist;
    bool EmissiveExist;
    bool SpecularExist;

    bool ShininessExist;
    bool Pad0;
    bool Pad1;
    bool Pad2;

    Vector2f Pad3;
};
#pragma pack(pop)
}

class Texture2d;
class Sampler;

FALCON_ENGINE_CLASS_BEGIN Material :
public Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Material();
    virtual ~Material() = default;

public:
    Color mAmbientColor = ColorPalette::Transparent;
    Color mDiffuseColor = ColorPalette::Transparent;
    Color mEmissiveColor = ColorPalette::Transparent;
    Color mSpecularColor = ColorPalette::Transparent;
    float mShininess = 0.0f;

    const Texture2d *mAmbientTexture = nullptr;
    const Texture2d *mDiffuseTexture = nullptr;
    const Texture2d *mEmissiveTexture = nullptr;
    const Texture2d *mSpecularTexture = nullptr;
    const Texture2d *mShininessTexture = nullptr;

    const Sampler *mAmbientSampler = nullptr;
    const Sampler *mDiffuseSampler = nullptr;
    const Sampler *mEmissiveSampler = nullptr;
    const Sampler *mSpecularSampler = nullptr;
    const Sampler *mShininessSampler = nullptr;
};
FALCON_ENGINE_CLASS_END

}
