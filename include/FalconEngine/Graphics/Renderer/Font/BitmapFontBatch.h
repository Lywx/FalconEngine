#pragma once

#include <FalconEngine/GraphicsInclude.h>

namespace FalconEngine
{

class VertexBuffer;
using VertexBufferSharedPtr = std::shared_ptr<VertexBuffer>;

class Visual;
using VisualSharedPtr = std::shared_ptr<Visual>;

class BitmapFontBatch
{
public:
    BitmapFontBatch(VertexBufferSharedPtr buffer, VisualSharedPtr quads) :
        mBuffer(buffer),
        mQuads(quads)
    {
    }

    ~BitmapFontBatch() = default;

public:
    VertexBufferSharedPtr         mBuffer;
    size_t                        mBufferDataIndex = 0;
    size_t                        mBufferGlyphNum = 0;

    VisualSharedPtr               mQuads;
};

}
