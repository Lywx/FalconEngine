#include <FalconEngine/Graphics/Renderer/BitmapFont.h>

namespace FalconEngine
{

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const double BitmapFont::mSizeScale = 1.32;

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BitmapFont::BitmapFont(const std::string& fileName, const std::string& filePath) :
    Asset(fileName, filePath),
    mTextureWidth(0),
    mTextureHeight(0),
    mTexturePages(0)
{
}

BitmapFont::~BitmapFont()
{
}

}
