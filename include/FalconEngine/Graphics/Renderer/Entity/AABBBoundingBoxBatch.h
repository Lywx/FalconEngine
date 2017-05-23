#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Math/Matrix4.h>

namespace FalconEngine
{

class Camera;

class VertexBuffer;

class Visual;
class VisualEffectInstance;

#pragma warning(disable: 4251)
class AABBBoundingBoxBatch
{
public:
    AABBBoundingBoxBatch(const Camera *camera,
                         std::shared_ptr<VertexBuffer> vertexBuffer,
                         std::shared_ptr<VertexBuffer> instanceBuffer,
                         std::shared_ptr<Visual> visual,
                         std::shared_ptr<VisualEffectInstance> visualEffectInstance) :
        mCamera(camera),
        mInstanceBuffer(instanceBuffer),

        // NOTE(Wuxiang): Note that the vertex instancing number is stored in side the triangle visual.
        mVertexBuffer(vertexBuffer),
        mVisual(visual),
        mVisualEffectInstance(visualEffectInstance)
    {
    }

    ~AABBBoundingBoxBatch() = default;

public:
    const Camera                         *mCamera;
    bool                                  mCameraViewProjectionComputed = false;
    Matrix4f                              mCameraViewProjectionTransform = Matrix4f::Identity;

    std::shared_ptr<VertexBuffer>         mInstanceBuffer;
    size_t                                mInstanceBufferDataIndex = 0;
    int                                   mInstanceNum = 0;

    std::shared_ptr<VertexBuffer>         mVertexBuffer;

    std::shared_ptr<Visual>               mVisual;
    std::shared_ptr<VisualEffectInstance> mVisualEffectInstance;
};
#pragma warning(default: 4251)

}
