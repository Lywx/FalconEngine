#pragma once

#include <FalconEngine/Core/Macro.h>

#include <functional>
#include <map>
#include <queue>

#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectParams.h>
#include <FalconEngine/Graphics/Renderer/Resource/Uniform.h>
#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

namespace Detail
{
#pragma pack(push, 1)
struct FALCON_ENGINE_API DebugVertex
{
    Vector2f mPosition;
    Vector4f mColor;

    // This index is used to index into the uniform view projection transform
    // array to select correct camera transform.
    int mCamera;
};
#pragma pack(pop)
}

class Visual;
class Mesh;
class Node;

FALCON_ENGINE_CLASS_BEGIN DebugEffectParams :
public VisualEffectParams
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    DebugEffectParams();

public:
    void
    AddCamera(const Camera * camera);

    void
    RemoveCamera(const Camera * camera);

public:
    // Store if the index slot is used by a camera.
    std::vector<bool> mCameraSlot;
    std::map<const Camera *, int> mCameraSlotTable;
    std::vector<UniformValueSp<Matrix4f>> mCameraSlotUniform;
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

protected:
    /************************************************************************/
    /* Protected Members                                                    */
    /************************************************************************/
    void
    InitializeInstance(
        _IN_OUT_ VisualEffectInstance              *instance,
        _IN_     std::shared_ptr<DebugEffectParams> params) const;
};
FALCON_ENGINE_CLASS_END
}
