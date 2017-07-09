#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLVertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformVertexFormat::PlatformVertexFormat(const VertexFormat *vertexFormat) :
    mVertexArrayObj(),
    mVertexFormatPtr(vertexFormat)
{
    Create();
}

PlatformVertexFormat::~PlatformVertexFormat()
{
    glDeleteVertexArrays(1, &mVertexArrayObj);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformVertexFormat::Enable()
{
    glBindVertexArray(mVertexArrayObj);
}

void
PlatformVertexFormat::Disable()
{
    glBindVertexArray(0);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformVertexFormat::Create()
{
    // NOTE(Wuxiang): glCreateVertexArrays only available in OGL 4.5.
    glGenVertexArrays(1, &mVertexArrayObj);
    glBindVertexArray(mVertexArrayObj);

    for (auto& vertexAttrib : mVertexFormatPtr->mVertexAttributeList)
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

}
