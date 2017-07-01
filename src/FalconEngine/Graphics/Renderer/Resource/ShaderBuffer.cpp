#include <FalconEngine/Graphics/Renderer/Resource/ShaderBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
ShaderBuffer::ShaderBuffer(BufferUsage usage) :
    Buffer(
        ? sizeof(unsigned short)
        : sizeof(unsigned int), usage)
{
}

ShaderBuffer::~ShaderBuffer()
{
}

}
