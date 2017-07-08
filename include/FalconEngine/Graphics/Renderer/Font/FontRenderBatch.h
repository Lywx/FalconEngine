#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <FalconEngine/Graphics/Renderer/Font/FontText.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferCircular.h>
#include <FalconEngine/Math/Color.h>
#include "FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h"
#include "FalconEngine/Graphics/Renderer/PrimitiveQuads.h"

namespace FalconEngine
{

class VertexBuffer;
class VertexGroup;

class Visual;

#pragma warning(disable: 4251)
class FontRenderItem
{
public:
    FontRenderItem(const FontText& text, const Color& textColor) :
        mText(text),
        mTextColor(textColor)
    {
    }

public:
    FontText mText;
    Color    mTextColor;
};

class FontRenderBatch
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    FontRenderBatch(std::shared_ptr<VertexBuffer>   glyphVertexBuffer,
                    std::shared_ptr<PrimitiveQuads> glyphQuadPrimitive,
                    std::shared_ptr<Visual>         glyphQuadVisual) :
        mPendingGlyphNum(0),
        mPendingGlyphNumPredict(0),
        mFrameGlyphNum(0),
        mGlyphQuadPrimitive(glyphQuadPrimitive),
        mGlyphQuadVisual(glyphQuadVisual),
        mGlyphVertexBuffer(glyphVertexBuffer)
    {
        using namespace std;

        mGlyphVertexBufferAdaptor = make_shared<BufferCircular>(
                                        mGlyphVertexBuffer,
                                        mGlyphVertexBuffer->GetCapacitySize() / 4);
    }

    ~FontRenderBatch() = default;

public:
    // NOTE(Wuxiang): Only valid during one frame.
    std::vector<FontRenderItem>     mBatchedItemList;

    int                             mPendingGlyphNum;        // Number of all displayable glyph in single instance of filling.
    int                             mPendingGlyphNumPredict; // Number of estimated displayable glyph (without configuring out which one is displayable, like \n).

    int                             mFrameGlyphNum;          // Number of glyph cross multiple instance of filling.

    // NOTE(Wuxiang): Persistent cross frames.
    std::shared_ptr<PrimitiveQuads> mGlyphQuadPrimitive;
    std::shared_ptr<Visual>         mGlyphQuadVisual;

    std::shared_ptr<VertexBuffer>   mGlyphVertexBuffer;
    std::shared_ptr<BufferAdaptor>  mGlyphVertexBufferAdaptor;
};
#pragma warning(default: 4251)

}
