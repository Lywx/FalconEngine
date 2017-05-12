#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Math/Matrix4.h>

namespace FalconEngine
{

class Camera;

class VertexBuffer;
using VertexBufferSharedPtr = std::shared_ptr<VertexBuffer>;

class Visual;
using VisualSharedPtr = std::shared_ptr<Visual>;

#pragma warning(disable: 4251)
class BoundingBoxBatch
{
public:
    BoundingBoxBatch(
        const Camera *camera,
        VertexBufferSharedPtr vertexBuffer,
        VisualSharedPtr vertexTriangles,
        VertexBufferSharedPtr instanceBuffer) :
        mCamera(camera),
        mInstanceBuffer(instanceBuffer),

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

    VertexBufferSharedPtr mInstanceBuffer;
    size_t                mInstanceBufferDataIndex = 0;
    size_t                mInstanceNum = 0;

    VisualSharedPtr       mVertexTriangles;

    VertexBufferSharedPtr mVertexBuffer;
};
#pragma warning(default: 4251)

}
