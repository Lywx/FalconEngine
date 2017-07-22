#pragma once

#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Graphics/Common.h>
#include <FalconEngine/Graphics/Effect/DebugEffect.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveLines.h>
#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderMessageManager.h>
#include <FalconEngine/Graphics/Renderer/Debug/DebugRendererHelper.h>
#include <FalconEngine/Graphics/Renderer/Entity/Entity.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferCircular.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexResource.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Math/Color.h>
#include "FalconEngine/Context/GameEngineGraphics.h"

namespace FalconEngine
{

class Camera;
class Color;

class Entity;
class Node;

class Renderer;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API DebugRenderer final
{
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
public:
    static DebugRenderer *
    GetInstance()
    {
        static DebugRenderer sInstance;
        return &sInstance;
    }

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
private:
    DebugRenderer();
public:
    ~DebugRenderer();

public:
    /************************************************************************/
    /* Rendering API                                                        */
    /************************************************************************/
    // @summary Recursively draw aabb for the entity.
    void
    AddAABB(const Camera *camera,
            const Entity *entity,

            const Color&  color,
            float         duration = 0.0f,
            bool          depthEnabled = true);

    // @summary Recursively draw aabb for the node.
    void
    AddAABB(const Camera *camera,
            const Node   *node,

            const Color&  color,
            float         duration = 0.0f,
            bool          depthEnabled = true);

    void
    AddAABB(const Camera *camera,
            const Visual *visual,

            const Color&  color,
            float         duration = 0.0f,
            bool          depthEnabled = true);

    void
    AddAABB(const Vector3f& min,
            const Vector3f& max,

            const Color&    color,
            float           duration = 0.0f,
            bool            depthEnabled = true);

    // NEW(Wuxiang): Add OBB support.
    // void
    // AddOBB(const Matrix4f& centerTransform,
    //        const Vector3f& scale,
    //        const Color&    color,
    //        float           duration = 0.0f,
    //        bool            depthEnabled = true);

    void
    AddCircle(const Vector3f& center,
              const Vector3f& normal,
              float           radius,

              const Color&    color,
              float           duration = 0.0f,
              bool            depthEnabled = true);

    void
    AddCross(const Vector3f& center,
             float           radius,

             const Color&    color,
             float           duration = 0.0f,
             bool            depthEnabled = true);

    void
    AddLine(const Vector3f& from,
            const Vector3f& to,

            const Color&    color,
            float           duration = 0.0f,
            bool            depthEnabled = true);

    void
    AddSphere(const Vector3f& center,
              float           radius,

              const Color&    color,
              float           duration = 0.0f,
              bool            depthEnabled = true);

    // NEW(Wuxiang): Add 3d text rendering support.
    // void
    // AddText(const Vector3f& position,
    //         const char     *text,
    //         const Color&    color,
    //         float           fontSize = 16.0f,
    //         float           duration = 0.0f,
    //         bool            depthEnabled = true);

    /************************************************************************/
    /* Rendering Engine API                                                 */
    /************************************************************************/
    void
    Initialize();

    void
    RenderBegin();

    void
    Render(Renderer *renderer, double percent);

    void
    RenderEnd();

    void
    Update(double elapsed);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    template <typename T>
    void
    CreateChannel(int                          channel,
                  int                          channelElementNum,
                  std::shared_ptr<DebugEffect> visualEffect)
    {
        using namespace std;

        static_assert(is_base_of<Primitive, T>::value, "Template parameter"
                      "must be primitive type.");

        auto vertexBuffer = make_shared<VertexBuffer>(
                                channelElementNum, sizeof(DebugVertex),
                                BufferStorageMode::Device, BufferUsage::Stream);

        auto vertexBufferAdaptor = make_shared<BufferCircular>(vertexBuffer, vertexBuffer->GetCapacitySize() / 4);

        // NOTE(Wuxiang): Even two effect have different depth test state, they
        // can still share vertex format.
        auto vertexFormat = visualEffect->GetVertexFormat();
        auto vertexGroup = make_shared<VertexGroup>();
        vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, vertexFormat->GetVertexBufferStride(0));

        auto primitive = make_shared<T>(vertexFormat, vertexGroup, nullptr, false);

        auto visual = make_shared<Visual>(make_shared<Mesh>(primitive, nullptr));
        auto visualEffectParams = make_shared<DebugEffectParams>();
        visualEffect->CreateInstance(visual.get(), visualEffectParams);

        mVertexResource->CreateChannel(channel, vertexBufferAdaptor, visual);
    }

private:
    std::shared_ptr<DebugRenderMessageManager> mMessageManager;
    std::shared_ptr<VertexResource>            mVertexResource;
};
#pragma warning(default: 4251)

}
