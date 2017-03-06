#pragma once

namespace FalconEngine
{

class Camera;

class VertexBuffer;
using VertexBufferSharedPtr = std::shared_ptr<VertexBuffer>;

class Visual;
using VisualSharedPtr = std::shared_ptr<Visual>;

class BoundingBoxBatch
{
public:
    BoundingBoxBatch(
        const Camera *camera,
        VertexBufferSharedPtr vertexBuffer,
        VisualSharedPtr vertexTriangles,
        VertexBufferSharedPtr transformBuffer) :
        mCamera(camera),
        mTransformBuffer(transformBuffer),

        // NOTE(Wuxiang): Note that the vertex instancing number is stored in side the triangle visual.
        mVertexTriangles(vertexTriangles),
        mVertexBuffer(vertexBuffer)
    {
    }

    ~BoundingBoxBatch() = default;

public:
    const Camera         *mCamera;
    bool                  mCameraViewProjectionComputed = false;
    Matrix4f              mCameraViewProjectionTransform = Matrix4f::Identity;

    VertexBufferSharedPtr mTransformBuffer;
    size_t                mTransformBufferDataIndex = 0;

    VisualSharedPtr       mVertexTriangles;

    VertexBufferSharedPtr mVertexBuffer;
    size_t                mVertexBufferDataIndex = 0;
    size_t                mVertexNum = 0;
};

}
