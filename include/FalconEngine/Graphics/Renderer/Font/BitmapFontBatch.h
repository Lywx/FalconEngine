#pragma once

#include <FalconEngine/Graphics/Header.h>

namespace FalconEngine
{

class VertexBuffer;
using VertexBufferSharedPtr = std::shared_ptr<VertexBuffer>;

class Visual;
using VisualSharedPtr = std::shared_ptr<Visual>;

#pragma warning(disable: 4251)
class BitmapFontBatch
{
public:
    BitmapFontBatch(VertexBufferSharedPtr vertexBuffer, VisualSharedPtr vertexQuads) :
        mVertexBuffer(vertexBuffer),
        mVertexQuads(vertexQuads)
    {
    }

    ~BitmapFontBatch() = default;

public:
    size_t                mGlyphNum = 0;

    VertexBufferSharedPtr mVertexBuffer;
    size_t                mVertexBufferDataIndex = 0;

    VisualSharedPtr       mVertexQuads;
};
#pragma warning(default: 4251)

}
