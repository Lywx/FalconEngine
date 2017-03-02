#pragma once

#include <FalconEngine/GraphicsInclude.h>

#include <string>
#include <vector>
#include <limits>

#include <FalconEngine/Graphics/Renderer/Font/BitmapFontBatch.h>

namespace FalconEngine
{

class BitmapFont;
class BitmapFontEffect;
using BitmapFontEffectSharedPtr = std::shared_ptr<BitmapFontEffect>;
class BitmapText;

class Renderer;

class Visual;
using VisualSharedPtr = std::shared_ptr<Visual>;
class VisualEffectInstance;
using VisualEffectInstanceSharedPtr = std::shared_ptr<VisualEffectInstance>;

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
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    BitmapFontRenderer();
    ~BitmapFontRenderer();

public:
    /************************************************************************/
    /* Rendering API                                                        */
    /************************************************************************/
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

    /************************************************************************/
    /* Rendering Engine API                                                 */
    /************************************************************************/
    void
    Initialize(int width, int height);

    void
    RenderBegin();

    void
    Render(Renderer *renderer, double percent);

    void
    RenderEnd();

protected:
    void
    PrepareText(_IN_OUT_ BitmapFontBatch& item,
                _IN_     const BitmapFont     *font,
                _IN_     const BitmapText     *text,
                _IN_     Color                 textColor = ColorPalette::White);

private:
    BitmapFontBatch               mDynamicTextBatch;
    VertexBufferSharedPtr         mDynamicTextBuffer;
    VisualSharedPtr               mDynamicTextQuads;

    BitmapFontBatch               mStaticTextBatch;
    VertexBufferSharedPtr         mStaticTextBuffer;
    VisualSharedPtr               mStaticTextQuads;

    BitmapFontEffectSharedPtr     mDebugTextEffect;
    VisualEffectInstanceSharedPtr mDebugTextEffectInstance;

    HandednessRight               mHandedness;
};

}
