#include <FalconEngine/Graphics/Renderer/Font/FontRenderer.h>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Graphics/Effect/FontEffect.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveQuads.h>
#include <FalconEngine/Graphics/Renderer/Font/Font.h>
#include <FalconEngine/Graphics/Renderer/Font/FontLine.h>
#include <FalconEngine/Graphics/Renderer/Font/FontRendererHelper.h>
#include <FalconEngine/Graphics/Renderer/Font/FontText.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferResource.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferCircular.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

using namespace std;
using namespace FalconEngine;

namespace FalconEngine
{
/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const int
FontRenderer::FrameGlyphNumMax = int(Kilobytes(10));

const int
FontRenderer::BatchItemNumMax = 1024;

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
FontRenderer::FontRenderer()
{
    mTextBufferResource = make_shared<BufferResource<FontResourceChannel>>();
}

FontRenderer::~FontRenderer()
{
}

/************************************************************************/
/* Rendering API                                                        */
/************************************************************************/
void
FontRenderer::AddText(const Font *font,
                      float       fontSize,
                      const Vector2f&    textPosition,
                      const std::string& text,
                      Color              textColor,
                      float              textLineWidth)
{
    FALCON_ENGINE_CHECK_NULLPTR(font);

    BatchText(font, fontSize, GetWString(text), textPosition, textColor, textLineWidth);
}

void
FontRenderer::AddText(const Font *font,
                      float       fontSize,
                      const Vector2f&     textPosition,
                      const std::wstring& text,
                      Color               textColor,
                      float               textLineWidth)
{
    FALCON_ENGINE_CHECK_NULLPTR(font);

    BatchText(font, fontSize, text, textPosition, textColor, textLineWidth);
}

/************************************************************************/
/* Rendering Engine API                                                 */
/************************************************************************/
void
FontRenderer::Initialize()
{
}

void
FontRenderer::RenderBegin()
{
}

void
FontRenderer::Render(double /* percent */)
{
    mTextBufferResource->Draw(nullptr);

    for (auto fontChannelIter = mTextBufferResource->GetChannelBegin();
            fontChannelIter != mTextBufferResource->GetChannelEnd();
            ++fontChannelIter)
    {
        auto fontChannel = fontChannelIter->first;
        auto& fontChannelInfo = fontChannelIter->second;

        if (mTextBufferResource->GetChannel(fontChannel)->mRenderItemList.size() > 0)
        {
            FillText(reinterpret_cast<const Font *>(fontChannel),
                     fontChannelInfo.get());
        }

        mTextBufferResource->DrawChannel(fontChannel, nullptr);
    }
}

void
FontRenderer::RenderEnd()
{
    // NOTE(Wuxiang): Only need to reset persistent data because after Render
    // method gets called, all the non-persistent data is cleared already.
    mTextBufferResource->ResetPersistent();
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
FontRenderer::BatchText(
    const Font     *font,
    float           fontSize,

    const wstring&  textString,
    const Vector2f& textPosition,
    Color           textColor,
    float           textLineWidth)
{
    FALCON_ENGINE_CHECK_NULLPTR(font);

    auto& fontChannelInfo = FindChannel(font);
    auto fontChannel = intptr_t(font);

    // Add the text into the batch
    auto fontVertexNumMapped = int(textString.size()) * 6;
    mTextBufferResource->AddChannelElementMapped(fontChannel, fontVertexNumMapped);
    mTextBufferResource->AddChannelItem(fontChannel, FontRenderItem(
                                            FontText(fontSize,
                                                    textString,
                                                    textPosition,
                                                    textLineWidth),
                                            textColor));

    // Fill the text VRAM buffer when the batch item number reach the item limit.
    int itemNum = int(fontChannelInfo->mRenderItemList.size());
    if (itemNum >= BatchItemNumMax)
    {
        FillText(font, fontChannelInfo.get());
    }
}

const std::shared_ptr<FontResourceChannel>&
FontRenderer::FindChannel(const Font *font)
{
    auto fontChannel = intptr_t(font);

    // When the font is prepared before.
    auto fontChannelExist = mTextBufferResource->ContainChannel(fontChannel);
    if (fontChannelExist)
    {
        return mTextBufferResource->GetChannel(fontChannel);
    }

    // Initialize new batch for given font.
    static auto sVisualEffect = make_shared<FontEffect>();

    // Take account for the buffer zone.
    int vertexBufferVertexNum = int(FrameGlyphNumMax * 6 * 1.25);
    auto vertexBuffer = make_shared<VertexBuffer>(
                            vertexBufferVertexNum, sizeof(FontVertex),
                            BufferStorageMode::Device, BufferUsage::Stream);

    auto vertexBufferAdaptor = make_shared<BufferCircular>(
                                   vertexBuffer,
                                   vertexBuffer->GetCapacitySize() / 4);

    auto vertexFormat = sVisualEffect->GetVertexFormat();
    auto vertexGroup = make_shared<VertexGroup>();
    vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, vertexFormat->GetVertexBufferStride(0));

    auto primitive = make_shared<PrimitiveQuads>(vertexFormat, vertexGroup, nullptr);

    auto visual = make_shared<Visual>(make_shared<Mesh>(primitive, nullptr));
    auto visualEffectParams = make_shared<FontEffectParams>(font, HandednessRight::GetInstance());
    sVisualEffect->CreateInstance(visual.get(), visualEffectParams);

    return mTextBufferResource->CreateChannel(fontChannel, vertexBufferAdaptor, visual);
}

void
FontRenderer::FillText(
    _IN_     const Font          *font,
    _IN_OUT_ FontResourceChannel *fontChannelInfo)
{
    FALCON_ENGINE_CHECK_NULLPTR(font);

    auto fontChannel = intptr_t(font);

    mTextBufferResource->FillChannelDataBegin(
        fontChannel,
        BufferAccessMode::WriteRange,
        BufferFlushMode::Explicit,
        BufferSynchronizationMode::Unsynchronized);

    {
        BufferAdaptor *bufferAdaptor;
        unsigned char *bufferData;
        std::tie(bufferAdaptor, bufferData)
            = mTextBufferResource->GetChannelData(fontChannel);

        int fontPendingGlyphNum = 0;

        // Created text vertex on the fly and fill them into the buffer.
        static auto sTextLineList = vector<FontLine>();
        for (auto& textItem : fontChannelInfo->mRenderItemList)
        {
            sTextLineList.clear();

            auto& text = textItem.mText;
            auto& textColor = textItem.mTextColor;

            // Construct lines with glyph information.
            fontPendingGlyphNum +=
                FontRendererHelper::CreateTextLineList(font, text, sTextLineList);

            // Fill the vertex attribute into the buffer
            FontRendererHelper::FillTextLineList(
                bufferAdaptor,
                bufferData,
                font,
                text.mFontSize,
                Vector2f(text.mTextBounds.x, text.mTextBounds.y),
                textColor,
                sTextLineList);
        }

        auto fontPendingVertexNum = fontPendingGlyphNum * 6;
        mTextBufferResource->AddChannelElementPersistent(fontChannel, fontPendingVertexNum);
        mTextBufferResource->FlushChannelData(fontChannel, fontPendingVertexNum);
    }

    mTextBufferResource->FillChannelDataEnd(fontChannel);
    mTextBufferResource->ResetChannel(fontChannel);
}

}
