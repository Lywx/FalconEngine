#include <FalconEngine/Graphics/Renderer/Font/FontText.h>

#include <limits>

using namespace std;
using namespace FalconEngine;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
FontText::FontText(float fontSize,
                   const std::wstring& textString,
                   const Vector2f&     textPosition,
                   float               textLineWidth) :
    mFontSize(fontSize),
    mTextBounds(textPosition.x, textPosition.y, textLineWidth,
                numeric_limits<float>::max()),
    mTextString(textString)
{
}

FontText::FontText(float fontSize,
                   const std::wstring& textString,
                   const Vector4f&     textBounds) :
    mFontSize(fontSize),
    mTextBounds(textBounds),
    mTextString(textString)
{
}

}
