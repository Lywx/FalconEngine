#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <FalconEngine/Graphics/Renderer/Resource/BufferCircular.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Math/Matrix4.h>

namespace FalconEngine
{

class Camera;

class BufferAdaptor;
class VertexBuffer;

class Visual;
class VisualEffectInstance;

#pragma warning(disable: 4251)
class EntityAABBBatch
{
public:
    EntityAABBBatch(const Camera                         *camera,
                    std::shared_ptr<VertexBuffer>         vertexBuffer,
                    std::shared_ptr<VertexBuffer>         instanceBuffer,
                    std::shared_ptr<Visual>               visual,
                    std::shared_ptr<VisualEffectInstance> visualEffectInstance) :
        mCamera(camera),
        mInstanceBuffer(instanceBuffer),

        // NOTE(Wuxiang): Note that the vertex instancing number is stored in side the triangle visual.
        mVertexBuffer(vertexBuffer),
        mVisual(visual),
        mVisualEffectInstance(visualEffectInstance)
    {
        using namespace std;

        mInstanceBufferCirculer = make_shared<BufferCircular>(
                                      dynamic_pointer_cast<Buffer>(instanceBuffer),
                                      instanceBuffer->GetCapacitySize() / 4);
    }

    ~EntityAABBBatch() = default;

public:
    const Camera                         *mCamera;

    std::shared_ptr<VertexBuffer>         mInstanceBuffer;
    std::shared_ptr<BufferAdaptor>        mInstanceBufferCirculer;
    int                                   mInstanceNum = 0;

    std::shared_ptr<VertexBuffer>         mVertexBuffer;

    std::shared_ptr<Visual>               mVisual;
    std::shared_ptr<VisualEffectInstance> mVisualEffectInstance;
};
#pragma warning(default: 4251)

}
