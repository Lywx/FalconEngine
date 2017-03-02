#pragma once

#include <FalconEngine/GraphicsInclude.h>

namespace FalconEngine
{

class VisualQuads;
using VisualQuadsSharedPtr = std::shared_ptr<VisualQuads>;

class VertexBuffer;
using VertexBufferSharedPtr = std::shared_ptr<VertexBuffer>;

class BitmapFontBatch
{
public:
    BitmapFontBatch(VertexBufferSharedPtr buffer, VisualQuadsSharedPtr quads) :
        mBuffer(buffer),
        mQuads(quads)
    {
    }

    ~BitmapFontBatch() = default;

public:
    VertexBufferSharedPtr         mBuffer;
    size_t                        mBufferDataIndex = 0;
    size_t                        mBufferGlyphNum = 0;

    VisualQuadsSharedPtr          mQuads;
};

}
