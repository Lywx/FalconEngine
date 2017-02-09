#include <FalconEngine/Graphics/Renderers/BitmapFont.h>

namespace FalconEngine
{

const double BitmapFont::mSizeScale = 1.32;

BitmapFont::BitmapFont(std::string fileName, std::string filePath) :
    Asset(fileName, filePath),
    mTextureWidth(0),
    mTextureHeight(0),
    mTexturePages(0)
{
}

BitmapFont::~BitmapFont()
{
}

void BitmapFont::SetSize(double size)
{
    mSizePt = size / mSizeScale;
    mSizePx = mSizePt / 72 * 96;
}

}
