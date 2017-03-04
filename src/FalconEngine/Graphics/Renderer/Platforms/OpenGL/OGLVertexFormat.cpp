#include <FalconEngine/Graphics/Renderer/Platforms/OpenGL/OGLVertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexFormat.h>

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
        glVertexAttribFormat(vertexAttrib.mLocation, vertexAttrib.mChannel,
                             OpenGLShaderAttributeType[int(vertexAttrib.mType)],
                             vertexAttrib.mNormalized, vertexAttrib.mOffset);
        glVertexAttribBinding(vertexAttrib.mLocation, vertexAttrib.mBindingIndex);

        glEnableVertexAttribArray(vertexAttrib.mLocation);
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
