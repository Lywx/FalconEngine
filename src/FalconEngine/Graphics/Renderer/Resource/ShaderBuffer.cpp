#include <FalconEngine/Graphics/Renderer/Resource/ShaderBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ShaderBuffer::ShaderBuffer(size_t storageSize,
                           ResourceCreationAccessMode accessMode,
                           ResourceCreationAccessUsage accessUsage,
                           ResourceStorageMode storageMode) :
    Buffer(1, storageSize, BufferType::ShaderBuffer, accessMode, accessUsage, storageMode)
{
}

ShaderBuffer::~ShaderBuffer()
{
}

}
