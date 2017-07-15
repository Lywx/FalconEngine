#pragma once

#include <FalconEngine/Graphics/Common.h>
#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderBatch.h>
#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderMessageManager.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

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
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    DebugRenderer();
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
    std::shared_ptr<DebugRenderLineBatch>      mDebugLineBatch[2];
    std::shared_ptr<DebugRenderTriangleBatch>  mDebugTriangleBatch[2];
    std::shared_ptr<DebugRenderMessageManager> mDebugMessageManager;
};
#pragma warning(default: 4251)

}
