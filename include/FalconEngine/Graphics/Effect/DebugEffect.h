#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <functional>
#include <map>
#include <queue>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>
#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>

namespace FalconEngine
{

class Visual;
class Mesh;
class Node;

#pragma pack(push, 1)
class FALCON_ENGINE_API DebugVertex
{
public:
    Vector2f mPosition;
    Vector4f mColor;

    // This index is used to index into the uniform view projection transform
    // array to select correct camera transform.
    int mCamera;
};
#pragma pack(pop)

#pragma warning(disable: 4251)
class FALCON_ENGINE_API DebugEffectParams : public VisualEffectParams
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    DebugEffectParams();

public:
    void
    AddCamera(const Camera *camera);

    void
    RemoveCamera(const Camera *camera);

public:
    std::vector<bool>                           mCameraSlot;
    std::map<const Camera *, int>               mCameraSlotTable;
    std::vector<ShaderUniformValueSp<Matrix4f>> mCameraSlotUniform;
};

class FALCON_ENGINE_API DebugEffect : public VisualEffect
{
    FALCON_ENGINE_EFFECT_DECLARE(DebugEffect);

public:
    static const int CameraNumMax;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit DebugEffect(bool depthTestEnabled);
    virtual ~DebugEffect();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    CreateInstance(_IN_OUT_ Visual                                   *visual,
                   _IN_     const std::shared_ptr<DebugEffectParams>& params);

    virtual std::shared_ptr<VertexFormat>
    GetVertexFormat() const override;

    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
protected:
    virtual std::shared_ptr<VertexFormat>
    CreateVertexFormat() const override;

    void
    InitializeInstance(
        _IN_OUT_ VisualEffectInstance              *instance,
        _IN_     std::shared_ptr<DebugEffectParams> params) const;
};
#pragma warning(default: 4251)

}
