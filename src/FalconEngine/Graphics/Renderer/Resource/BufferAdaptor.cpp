#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BufferAdaptor::BufferAdaptor(std::shared_ptr<Buffer> buffer) :
    mBuffer(buffer),
    mBufferDataOffsetEnd(0)
{
}

BufferAdaptor::~BufferAdaptor()
{
}

}
