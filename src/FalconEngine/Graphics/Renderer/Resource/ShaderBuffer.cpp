#include <FalconEngine/Graphics/Renderer/Resource/ShaderBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ShaderBuffer::ShaderBuffer(size_t storageSize, BufferStorageMode storageMode, BufferUsage usage) :
    Buffer(1, storageSize, storageMode, BufferType::ShaderBuffer, usage)
{
}

ShaderBuffer::~ShaderBuffer()
{
}

}
