#include <FalconEngine/Graphics/Renderer/Font/BitmapText.h>

#include <limits>

using namespace std;
using namespace FalconEngine;

namespace FalconEngine
{

BitmapText::BitmapText(float fontSize, const std::wstring& textString,
                       Vector2f textPosition, float textLineWidth) :
    mFontSize(fontSize),
    mTextBounds(textPosition.x, textPosition.y, textLineWidth,
                numeric_limits<float>::max()),
    mTextString(textString)
{
}

BitmapText::BitmapText(float fontSize, const std::wstring& textString, Vector4f textBounds) :
    mFontSize(fontSize),
    mTextBounds(textBounds),
    mTextString(textString)
{
}

}
