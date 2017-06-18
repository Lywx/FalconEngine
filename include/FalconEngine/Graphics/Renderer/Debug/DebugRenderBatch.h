#pragma once

#include <FalconEngine/Graphics/Header.h>

namespace FalconEngine
{

class VertexBuffer;

class Visual;

#pragma warning(disable: 4251)
class DebugRenderBatch
{
public:
    DebugRenderBatch(std::shared_ptr<VertexBuffer> vertexBuffer,
                     std::shared_ptr<Visual>       vertexLines) :
        mLineNum(0),
        mLines(vertexLines),
        mVertexBuffer(vertexBuffer),
        mVertexBufferDataIndex(0)
    {
    }

    ~DebugRenderBatch() = default;

public:
    int                           mLineNum;
    std::shared_ptr<Visual>       mLines;

    std::shared_ptr<VertexBuffer> mVertexBuffer;
    int                           mVertexBufferDataIndex;
};
#pragma warning(default: 4251)

}
