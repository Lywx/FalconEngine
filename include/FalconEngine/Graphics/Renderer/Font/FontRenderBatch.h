#pragma once

#include <FalconEngine/Graphics/Header.h>

namespace FalconEngine
{

class VertexBuffer;

class Visual;

#pragma warning(disable: 4251)
class FontRenderBatch
{
public:
    FontRenderBatch(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<Visual> glyphQuads) :
        mGlyphNum(0),
        mGlyphQuads(glyphQuads),
        mVertexBuffer(vertexBuffer),
        mVertexBufferDataIndex(0)
    {
    }

    ~FontRenderBatch() = default;

public:
    int                           mGlyphNum;
    std::shared_ptr<Visual>       mGlyphQuads;

    std::shared_ptr<VertexBuffer> mVertexBuffer;
    size_t                        mVertexBufferDataIndex;
};
#pragma warning(default: 4251)

}
