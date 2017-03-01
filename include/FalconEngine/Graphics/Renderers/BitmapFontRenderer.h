#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <string>
#include <vector>
#include <limits>

namespace FalconEngine
{

class BitmapText;

class BitmapFont;

class BitmapFontEffect;
using BitmapFontEffectSharedPtr = std::shared_ptr<BitmapFontEffect>;

class Renderer;

class VertexBuffer;
using VertexBufferSharedPtr = std::shared_ptr<VertexBuffer>;

class Visual;
using VisualSharedPtr = std::shared_ptr<Visual>;

class VisualEffectInstance;
using VisualEffectInstanceSharedPtr = std::shared_ptr<VisualEffectInstance>;

class BitmapFontRenderItem
{
public:
    VertexBufferSharedPtr mTextBuffer;
    size_t                mTextBufferDataIndex = 0;
};

// @summary The font renderer is the class you would call to draw a string on
// the screen.
#if defined(FALCON_ENGINE_PLATFORM_QT)
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
                     Color       textColor = ColorPalette::White,
                     float       textLineWidth = std::numeric_limits<float>().max());

    void
    BatchTextStatic(const BitmapFont *font,
                    float             fontSize,
                    std::string textString,
                    Vector2f    textPosition,
                    Color       textColor = ColorPalette::White,
                    float       textLineWidth = std::numeric_limits<float>().max());

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
