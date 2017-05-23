#pragma once

#include <FalconEngine/Graphics/Header.h>

namespace FalconEngine
{

class VertexBuffer;

class Visual;

#pragma warning(disable: 4251)
class BitmapFontBatch
{
public:
    BitmapFontBatch(std::shared_ptr<VertexBuffer> vertexBuffer, std::shared_ptr<Visual> vertexQuads) :
        mVertexBuffer(vertexBuffer),
        mVertexQuads(vertexQuads)
    {
    }

    ~BitmapFontBatch() = default;

public:
    int                           mGlyphNum = 0;

    std::shared_ptr<VertexBuffer> mVertexBuffer;
    size_t                        mVertexBufferDataIndex = 0;

    std::shared_ptr<Visual>       mVertexQuads;
};
#pragma warning(default: 4251)

}
