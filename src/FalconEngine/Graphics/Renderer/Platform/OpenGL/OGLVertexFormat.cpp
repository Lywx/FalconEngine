#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLVertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformVertexFormat::PlatformVertexFormat(const VertexFormat *vertexFormat)
{
    glCreateVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);

    for (auto& vertexAttrib : vertexFormat->mVertexAttributeList)
    {
        glEnableVertexAttribArray(vertexAttrib.mLocation);

        glVertexAttribBinding(vertexAttrib.mLocation, vertexAttrib.mBindingIndex);

        glVertexAttribFormat(vertexAttrib.mLocation,
                             vertexAttrib.mChannel,
                             OpenGLShaderAttributeType[int(vertexAttrib.mType)],
                             vertexAttrib.mNormalized,

                             // The distance between elements within the buffer.
                             // So that you only need to properly sum up offset
                             // for this specific binding index.
                             vertexAttrib.mOffset);

        if (vertexAttrib.mDivision != 0)
        {
            glVertexBindingDivisor(vertexAttrib.mBindingIndex, vertexAttrib.mDivision);
        }
    }

    glBindVertexArray(0);
}

PlatformVertexFormat::~PlatformVertexFormat()
{
    glDeleteVertexArrays(1, &mVertexArray);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformVertexFormat::Enable()
{
    glBindVertexArray(mVertexArray);
}

void
PlatformVertexFormat::Disable()
{
    glBindVertexArray(0);
}

}
