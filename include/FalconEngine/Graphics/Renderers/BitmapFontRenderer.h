#pragma once

#include <string>
#include <vector>
#include <limits>

#include <FalconEngine/Graphics/Effects/BitmapFontEffect.h>
#include <FalconEngine/Graphics/Renderers/BitmapFont.h>
#include <FalconEngine/Graphics/Renderers/BitmapText.h>
#include <FalconEngine/Graphics/Renderers/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>
#include "VisualQuads.h"

// TODO(Wuxiang 2016-12-29 22:27): Integrate the font renderer with current renderer.
namespace FalconEngine
{

class BitmapFontRenderItem
{
public:
    VertexBufferSharedPtr mTextBuffer;
    size_t                mTextBufferDataIndex = 0;
};

class BitmapFontEffect;

// @summary The font renderer is the class you would call to draw a string on
// the screen.
#if defined(EMBTI_QT_EMBEDDING)
#include <QtGui/QOpenGLFunctions>
class BitmapFontRenderer : QOpenGLFunctions
#else
class BitmapFontRenderer
#endif
{
public:
    BitmapFontRenderer();
    ~BitmapFontRenderer();

    void
    Initialize(int width, int height);

    void
    BatchTextDynamic(const BitmapFont *font,
                     float             fontSize,
                     std::string textString,
                     Vector2f    textPosition,
                     float       textLineWidth = std::numeric_limits<float>().max(),
                     Color       textColor = ColorPalette::White);

    void
    BatchTextStatic(const BitmapFont *font,
                    float             fontSize,
                    std::string textString,
                    Vector2f    textPosition,
                    float       textLineWidth = std::numeric_limits<float>().max(),
                    Color       textColor = ColorPalette::White);

    void RenderBegin();
    void Render(Renderer *renderer, double percent);
    void RenderEnd();

protected:
    void
    PrepareText(BitmapFontRenderItem& item,
                const BitmapFont *font,
                const BitmapText *text,
                Color             textColor = ColorPalette::White);


private:
    VertexBufferSharedPtr              mDynamicTextBuffer;
    BitmapFontRenderItem               mDynamicTextItem;
    VisualSharedPtr                    mDynamicTextQuads;

    VertexBufferSharedPtr              mStaticTextBuffer;
    BitmapFontRenderItem               mStaticTextItem;
    VisualSharedPtr                    mStaticTextQuads;

    BitmapFontEffectSharedPtr          mTextEffect;
    VisualEffectInstanceSharedPtr      mTextEffectInstance;
    HandednessRight                    mTextHandedness;
};

}
