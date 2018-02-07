#include <FalconEngine/Platform/OpenGL/OpenGLVertexFormat.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Platform/OpenGL/OpenGLMapping.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformVertexFormat::PlatformVertexFormat(Renderer *, const VertexFormat *vertexFormat) :
    mVertexArrayObj(),
    mVertexFormatPtr(vertexFormat)
{
    CreateVertexArray();
}

PlatformVertexFormat::~PlatformVertexFormat()
{
    glDeleteVertexArrays(1, &mVertexArrayObj);
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformVertexFormat::Enable(Renderer *)
{
    glBindVertexArray(mVertexArrayObj);
}

void
PlatformVertexFormat::Disable(Renderer *)
{
    glBindVertexArray(0);
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformVertexFormat::CreateVertexArray()
{
    // NOTE(Wuxiang): glCreateVertexArrays only available in OGL 4.5.
    glGenVertexArrays(1, &mVertexArrayObj);
    glBindVertexArray(mVertexArrayObj);

    for (auto& vertexAttrib : mVertexFormatPtr->mVertexAttributeList)
    {
        glEnableVertexAttribArray(vertexAttrib.mLocation);

        glVertexAttribBinding(vertexAttrib.mLocation,
                              vertexAttrib.mBindingIndex);

        glVertexAttribFormat(vertexAttrib.mLocation,
                             vertexAttrib.mChannel,
                             OpenGLShaderAttributeType[int(vertexAttrib.mType)],
                             vertexAttrib.mNormalized,

                             // The distance between elements within the buffer.
                             // So that you only need to properly sum up offset
                             // for all binding index.
                             vertexAttrib.mStride);

        if (vertexAttrib.mDivision != 0)
        {
            glVertexBindingDivisor(vertexAttrib.mBindingIndex,
                                   vertexAttrib.mDivision);
        }
    }

    glBindVertexArray(0);
}

}

#endif