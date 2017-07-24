#include <FalconEngine/Graphics/Renderer/Resource/BufferCircular.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BufferCircular::BufferCircular(const std::shared_ptr<Buffer>& buffer, size_t bufferZoneSize) :
    BufferAdaptor(buffer),
    mBufferDataOffsetNext(0),
    mBufferZoneSize(bufferZoneSize)
{
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
void
BufferCircular::FillBegin()
{
    BufferAdaptor::FillBegin();

    // ALERT(Wuxiang): Conversion from unsigned to signed.
    mBuffer->SetDataOffset(int64_t(mBufferDataOffsetNext));
}

void
BufferCircular::FillEnd()
{
    BufferAdaptor::FillEnd();

    // NOTE(Wuxiang): =======+===+
    //                       1   2
    //                  ^      ^   ^
    //                  3      4   5
    //
    // 1: Safe offset boundary.
    // 2: Valid offset boundary.
    // 3: When offset is within safe zone.
    // 4: When offset is within buffer zone.
    // 5: When offset is overflowed.

    // When offset is overflowed.

    // NOTE(Wuxiang): Since the offset end is moved after filling data into next
    // write position. Suppose the last valid byte is just written, the offset is
    // moved to "byte count" or "byte number" position, which is one past valid offset.

    // ALERT(Wuxiang): unsigned to signed conversion here.
    size_t offset = size_t(mBuffer->GetDataOffset()) + mBufferDataRelativeOffsetEnd;
    if (mBuffer->GetCapacitySize() + 1 < offset)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Buffer is overflowed.");
    }

    // When offset is in safe zone.
    else if (offset < mBuffer->GetCapacitySize() - mBufferZoneSize)
    {
        // Start next offset in where it ends.
        mBufferDataOffsetNext = offset;
    }

    // When offset is in buffer zone.
    else
    {
        // Wrap next offset into origin.
        mBufferDataOffsetNext = 0;
    }
}

}
