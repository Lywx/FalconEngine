#include <FalconEngine/Graphics/Renderer/Resource/ShaderBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ShaderBuffer::ShaderBuffer(size_t storageSize,
                           BufferStorageMode storageMode,
                           ResourceCreationAccessMode accessMode,
                           ResourceCreationAccessUsage accessUsage) :
    Buffer(1, storageSize, storageMode, BufferType::ShaderBuffer, accessMode, accessUsage)
{
}

ShaderBuffer::~ShaderBuffer()
{
}

}
