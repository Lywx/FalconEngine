#pragma once

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Core/Memory.h>

// NOTE(Wuxiang): Necessary for template parameter checking.
#include <FalconEngine/Graphics/Renderer/PrimitivePoints.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveLines.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveQuads.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderMessageManager.h>
#include <FalconEngine/Graphics/Renderer/Debug/DebugRendererHelper.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferCircular.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferGroup.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Math/Color.h>

namespace FalconEngine
{

class Camera;
class Color;

class Entity;
class Node;

class Renderer;

FALCON_ENGINE_CLASS_BEGIN DebugRenderer final
{
    FALCON_ENGINE_SINGLETON_SAFE_DECLARE(DebugRenderer);

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
    // @summary Recursively draw AABB for the entity.
    void
    AddAabb(const Entity * entity,
            const Color & color,
            float duration = 0.0f,
            bool depthEnabled = true);

    // @summary Recursively draw AABB for the node.
    void
    AddAabb(const Node   * node,
            const Color &  color,
            float         duration = 0.0f,
            bool          depthEnabled = true);

    void
    AddAabb(const Visual * visual,
            const Color &  color,
            float         duration = 0.0f,
            bool          depthEnabled = true);

    void
    AddAabb(const Vector3f & min,
            const Vector3f & max,

            const Color &    color,
            float           duration = 0.0f,
            bool            depthEnabled = true);

    void
    AddCircle(const Vector3f & center,
              const Vector3f & normal,
              float           radius,

              const Color &    color,
              float           duration = 0.0f,
              bool            depthEnabled = true);

    void
    AddCross(const Vector3f & center,
             float           radius,

             const Color &    color,
             float           duration = 0.0f,
             bool            depthEnabled = true);

    void
    AddLine(const Vector3f & from,
            const Vector3f & to,

            const Color &    color,
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
    AddSphere(const Vector3f & center,
              float           radius,

              const Color &    color,
              float           duration = 0.0f,
              bool            depthEnabled = true);

    // NEW(Wuxiang): Add 3d text rendering support.

    // @summary Render 2d text on screen space.
    void
    AddText(const std::string & text,
            const Vector2f &    textPosition,
            float              fontSize = 16.0f,
            const Color&       color = ColorPalette::White,
            float              duration = 0.0f,
            bool               depthEnabled = true,
            float              textLineWidth = std::numeric_limits<float>().max());

    /************************************************************************/
    /* Camera API                                                           */
    /************************************************************************/
    void
    SetCamera(const Camera * camera);

    /************************************************************************/
    /* Rendering Engine API                                                 */
    /************************************************************************/
    void
    Initialize();

    void
    RenderBegin();

    void
    Render(double percent);

    void
    RenderEnd();

    void
    UpdateFrame(double elapsed);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    template <typename T>
    void
    CreateChannel(int channel,
                  int channelElementNum,
                  std::shared_ptr<DebugEffect> visualEffect)
    {
        using namespace std;

        static_assert(is_base_of<Primitive, T>::value, "Template parameter "
                      "must be primitive type.");

        auto vertexBuffer = make_shared<VertexBuffer>(
            channelElementNum,
            sizeof(Detail::DebugVertexData),
            ResourceCreationAccessMode::GpuReadCpuWrite,
            ResourceCreationAccessUsage::Stream,
            ResourceStorageMode::Device);

        auto vertexBufferAdaptor = make_shared<BufferCircular>(vertexBuffer, vertexBuffer->GetCapacitySize() / 4);

        // NOTE(Wuxiang): Even two effect have different depth test state, they
        // can still share vertex format.
        auto vertexFormat = visualEffect->GetPass(0)->GetShaderVertexFormatSp();
        auto vertexGroup = make_shared<VertexGroup>();
        vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, vertexFormat->GetVertexBufferStride(0));

        auto primitive = make_shared<T>(vertexFormat, vertexGroup, nullptr);

        auto visual = make_shared<Visual>(make_shared<Mesh>(primitive, nullptr));
        visualEffect->CreateInstance(visual.get(), mDebugEffectParams);

        mDebugBufferGroup->CreateChannel(channel, vertexBufferAdaptor, visual);
    }

private:
    std::shared_ptr<BufferGroup<BufferChannel>> mDebugBufferGroup;
    const Font *mDebugFont;
    std::shared_ptr<DebugEffectParams> mDebugEffectParams;
    std::shared_ptr<DebugRenderMessageManager> mDebugMessageManager;
};
FALCON_ENGINE_CLASS_END

}
