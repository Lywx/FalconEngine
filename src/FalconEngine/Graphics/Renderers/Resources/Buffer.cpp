#include <FalconEngine/Graphics/Renderers/Resources/Buffer.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Buffer, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
// @param elementNum - the element number
// @param elementByteNum - the element size in total.
Buffer::Buffer(int elementNum, int elementByteNum, BufferUsage usage) :
    mDataByteNum(elementNum * elementByteNum),
    mElementNum(elementNum),
    mUsage(usage)
{
    mData = new unsigned char[mDataByteNum];
}

Buffer::~Buffer()
{
    delete [] mData;
}


}
