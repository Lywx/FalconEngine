#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BufferAdaptor::BufferAdaptor(std::shared_ptr<Buffer> buffer) :
    mBuffer(buffer),
    mBufferDataOffsetNext(0),
    mBufferDataOffsetEnd(0)
{
}

BufferAdaptor::~BufferAdaptor()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const unsigned char *
BufferAdaptor::GetData() const
{
    return mBuffer->GetData();
}

unsigned char *
BufferAdaptor::GetData()
{
    return mBuffer->GetData();
}

size_t
BufferAdaptor::GetDataByteNum() const
{
    return mBuffer->GetDataByteNum();
}

size_t
BufferAdaptor::GetCapacityByteNum() const
{
    return mBuffer->GetCapacityByteNum();
}

}
