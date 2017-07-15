#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <FalconEngine/Graphics/Renderer/Resource/BufferCircular.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>

namespace FalconEngine
{

class VertexBuffer;

class Visual;

#pragma warning(disable: 4251)
class DebugRenderTriangleBatch
{
public:
    DebugRenderTriangleBatch(std::shared_ptr<VertexBuffer> triangleVertexBuffer,
                             std::shared_ptr<Visual>       triangleVisual) :
        mTriangleNum(0),
        mTriangleVisual(triangleVisual),
        mTriangleVertexBuffer(triangleVertexBuffer)
    {
        using namespace std;

        mTriangleVertexBufferAdapter = make_shared<BufferCircular>(
                                           mTriangleVertexBuffer,
                                           mTriangleVertexBuffer->GetCapacitySize() / 4);
    }
    ~DebugRenderTriangleBatch() = default;

public:
    int                            mTriangleNum;
    std::shared_ptr<Visual>        mTriangleVisual;

    std::shared_ptr<VertexBuffer>  mTriangleVertexBuffer;
    std::shared_ptr<BufferAdaptor> mTriangleVertexBufferAdapter;
};

class DebugRenderLineBatch
{
public:
    DebugRenderLineBatch(std::shared_ptr<VertexBuffer> lineVertexBuffer,
                         std::shared_ptr<Visual>       lineVisual) :
        mLineNum(0),
        mLineVisual(lineVisual),
        mLineVertexBuffer(lineVertexBuffer)
    {
        mLineVertexBufferAdaptor = std::make_shared<BufferCircular>(
                                       mLineVertexBuffer,
                                       mLineVertexBuffer->GetCapacitySize() / 4);
    }

    ~DebugRenderLineBatch() = default;

public:
    int                             mLineNum;
    std::shared_ptr<Visual>         mLineVisual;

    std::shared_ptr<VertexBuffer>   mLineVertexBuffer;
    std::shared_ptr<BufferAdaptor>  mLineVertexBufferAdaptor;
};

#pragma warning(default: 4251)

}
