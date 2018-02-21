#pragma once

#include <FalconEngine/Core/Macro.h>

#include <memory>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Scene/Light.h>
#include <FalconEngine/Graphics/Renderer/Scene/Material.h>
#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>
#include <FalconEngine/Math/Matrix3.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

class Light;
class Material;
class Mesh;
class Node;

class Visual;
class VisualEffectInstance;

FALCON_ENGINE_CLASS_BEGIN PhongEffectParams :
public VisualEffectParams
{
public:
    PhongEffectParams() = default;

public:
    std::shared_ptr<Light>              mDirectionalLight;
    std::vector<std::shared_ptr<Light>> mPointLightList;
    std::vector<std::shared_ptr<Light>> mSpotLightList;
};
FALCON_ENGINE_CLASS_END

FALCON_ENGINE_CLASS_BEGIN PhongEffect :
public VisualEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(PhongEffect);

public:
    const static int PointLightNumMax = 6;
    const static int SpotLightNumMax = 6;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit PhongEffect(bool initializer = true);
    virtual ~PhongEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    CreateInstance(_IN_OUT_ Node                                     * node,
                   _IN_     const std::shared_ptr<PhongEffectParams>& params);

protected:
    // @summary Add required parameters to the existing visual effect instance.
    void
    InitializeInstance(_IN_OUT_ VisualEffectInstance                     * instance,
                       _IN_     const std::shared_ptr<Material>&          material,
                       _IN_     const std::shared_ptr<PhongEffectParams>& params) const;
};
FALCON_ENGINE_CLASS_END

namespace Detail
{

#pragma pack(push, 4)
struct PhongTrasnformBufferData
{
    Matrix4f mModelViewProjectionTransform;
    Matrix4f mModelViewTransform;
    Matrix3f mNormalTransform;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct PhongMaterialBufferData
{
    MaterialColorData mMaterialColor;
    MaterialTextureData mMaterialTexture;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct LightBuffer
{
    // 4 x float4.
    DirectionalLightData DirectionalLight;

    // 4 x float4 x PointLightNumMax
    PointLightData PointLightArray[PhongEffect::PointLightNumMax];

    // SpotLightData SpotLightArray[PhongEffect::SpotLightNumMax];

    int PointLightNum;
    int SpotLightNum;
    int Pad0;
    int Pad1;
};
#pragma pack(pop)

}

}
