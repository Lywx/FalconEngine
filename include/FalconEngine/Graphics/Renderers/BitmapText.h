#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

namespace FalconEngine
{

// @summary The class the user would use to specify the all the information in
// text rendering. The design is implemented this way for avoiding user
// specifying shader related graphics pipeline information. The user should not
// do this. The user should be able to "select" from renderer API to render the
// text in specific way and that should be isolated from user-provided data.
//
// @design The user data should consists of:
//     1. font
//     2. font size
//     3. text string
//     4. text position and bounds
//
// The renderer API should process additional information, which consists of:
//     1. font color
//     2. font shader
//
// The font size has connection to the font shader uniform variables. The renderer
// should be able to extract font size from text group and streamline the shader
// variable processing.
//
// @note The structure of this class should be able to support different
// font type.
class BitmapText
{
public:
    BitmapText(float fontSize, std::string textString, Vector2f textPosition,
               float textLineWidth);

    BitmapText(float fontSize, std::string textString, Vector4f textBounds);

    float       mFontSize;

    Vector4f    mTextBounds;
    std::string mTextString;
};

}

