#pragma once

#include <FalconEngine/Graphics/Common.h>
#include <FalconEngine/Graphics/Renderer/Debug/DebugMessageManager.h>
#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderBatch.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

namespace FalconEngine
{

class Color;
class Vector3f;

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
    void
    AddAABB(const Vector3f& minCoords,
            const Vector3f& maxCoords,
            Color color,
            float lineWidth = 1.0f,
            float duration = 0.0f,
            bool  depthEnabled = true);

    void
    AddOBB(const Matrix4f& centerTransform,
           const Vector3f& scaleXYZ,
           Color color,
           float lineWidth = 1.0f,
           float duration = 0.0f,
           bool  depthEnabled = true);

    void
    AddCircle(const Vector3f& center,
              const Vector3f& normal,
              float radius,
              Color color,
              float duration = 0.0f,
              bool  depthEnabled = true);

    void
    AddCross(const Vector3f& position,
             Color color,
             float size,
             float duration = 0.0f,
             bool  depthEnabled = true);

    void
    AddLine(const Vector3f& from,
            const Vector3f& to,
            Color           color,
            float           lineWidth = 1.0f,
            float           duration = 0.0f,
            bool            depthEnabled = true);

    void
    AddSphere(const Vector3f& center,
              float           radius,
              Color           color,
              float           duration = 0.0f,
              bool            depthEnabled = true);

    void
    AddText(const Vector3f& pos,
            const char *text,
            Color color,
            float duration = 0.0f,
            bool  depthEnabled = true);

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
    std::shared_ptr<DebugRenderBatch> mDebugBatch;
    DebugMessageManager               mDebugMessageManager;
};
#pragma warning(default: 4251)

}
