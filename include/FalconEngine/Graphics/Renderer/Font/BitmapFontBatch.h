#pragma once

#include <FalconEngine/GraphicsInclude.h>

namespace FalconEngine
{

class VertexBuffer;
using VertexBufferSharedPtr = std::shared_ptr<VertexBuffer>;

class BitmapFontBatch
{
public:
    BitmapFontBatch()
    {
    }

    BitmapFontBatch(VertexBufferSharedPtr buffer) :
        mBuffer(buffer)
    {
    }

    ~BitmapFontBatch() = default;

public:
    VertexBufferSharedPtr mBuffer;
    size_t                mBufferDataIndex = 0;
    size_t                mBufferGlyphNum = 0;
};

}