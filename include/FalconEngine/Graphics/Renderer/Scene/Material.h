#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>

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
    Vector3f mAmbient;
    float mShininess;

    Vector3f mDiffuse;
    float _Pad0;

    Vector3f mEmissive;
    float _Pad1;

    Vector3f mSpecular;
    float _Pad2;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct FALCON_ENGINE_API MaterialTextureData
{
    int mAmbientExist;
    int mDiffuseExist;
    int mEmissiveExist;
    int mSpecularExist;
    int ShininessExist;

    int _Pad0;
    int _Pad1;
    int _Pad2;
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

    std::shared_ptr<Texture2d> mAmbientTexture;
    std::shared_ptr<Texture2d> mDiffuseTexture;
    std::shared_ptr<Texture2d> mEmissiveTexture;
    std::shared_ptr<Texture2d> mSpecularTexture;
    std::shared_ptr<Texture2d> mShininessTexture;

    std::shared_ptr<Sampler> mAmbientSampler;
    std::shared_ptr<Sampler> mDiffuseSampler;
    std::shared_ptr<Sampler> mEmissiveSampler;
    std::shared_ptr<Sampler> mSpecularSampler;
    std::shared_ptr<Sampler> mShininessSampler;
};
FALCON_ENGINE_CLASS_END

}
