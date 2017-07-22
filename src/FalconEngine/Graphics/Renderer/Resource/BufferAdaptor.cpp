#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BufferAdaptor::BufferAdaptor(const std::shared_ptr<Buffer>& buffer) :
    mBuffer(buffer),
    mBufferDataRelativeOffsetEnd(0)
{
}

BufferAdaptor::~BufferAdaptor()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
BufferAdaptor::FillBegin()
{
    mBufferDataRelativeOffsetEnd = 0;
}

void
BufferAdaptor::FillEnd()
{
}

std::shared_ptr<Buffer>
BufferAdaptor::GetBuffer()
{
    return mBuffer;
}

}
