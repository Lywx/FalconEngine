#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Graphics/Renderer/Font/FontText.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferGroup.h>
#include <FalconEngine/Math/Color.h>

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

    FontRenderItem(FontText&& text, const Color& textColor) :
        mText(std::move(text)),
        mTextColor(textColor)
    {
    }

public:
    FontText mText;
    Color    mTextColor;
};

class FontBufferChannel : public BufferChannel
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    using BufferChannel::BufferChannel;
    ~FontBufferChannel() = default;

public:
    void
    AddItem(const FontRenderItem& renderItem)
    {
        mRenderItemList.push_back(renderItem);
    }

    void
    AddItem(FontRenderItem&& renderItem)
    {
        mRenderItemList.push_back(std::move(renderItem));
    }

    virtual void
    Reset() override
    {
        BufferChannel::Reset();
        mRenderItemList.clear();
    }

public:
    const Font                 *mFont;
    std::vector<FontRenderItem> mRenderItemList;
};

#pragma warning(default: 4251)

}
