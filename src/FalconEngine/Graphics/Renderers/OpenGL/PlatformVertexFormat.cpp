#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformVertexFormat.h>
#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformExtensions.h>
#include <FalconEngine/Graphics.h>

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformVertexFormat::PlatformVertexFormat(Renderer *,
        const VertexFormat *vertexFormat)
{
    m_stride = vertexFormat->GetStride();

    VertexAttributeType type;

    int i = vertexFormat->GetAttributeIndex(VertexAttributeUsage::POSITION);
    if (i >= 0)
    {
        m_hasPosition = 1;
        type = vertexFormat->GetAttributeType(i);
        m_positionChannels = OpenGLAttributeChannels[int(type)];
        m_positionType = OpenGLAttributeType[int(type)];
        m_positionOffset = vertexFormat->GetAttributeOffset(i);
    }
    else
    {
        m_hasPosition = 0;
        m_positionChannels = 0;
        m_positionType = 0;
        m_positionOffset = 0;
    }

    i = vertexFormat->GetAttributeIndex(VertexAttributeUsage::NORMAL);
    if (i >= 0)
    {
        m_hasNormal = 1;
        type = vertexFormat->GetAttributeType(i);
        m_normalChannels = OpenGLAttributeChannels[int(type)];
        m_normalType = OpenGLAttributeType[int(vertexFormat->GetAttributeType(i))];
        m_normalOffset = vertexFormat->GetAttributeOffset(i);
    }
    else
    {
        m_hasNormal = 0;
        m_normalChannels = 0;
        m_normalType = 0;
        m_normalOffset = 0;
    }

    i = vertexFormat->GetAttributeIndex(VertexAttributeUsage::TANGENT);
    if (i >= 0)
    {
        m_hasTangent = 1;
        type = vertexFormat->GetAttributeType(i);
        m_tangentChannels = OpenGLAttributeChannels[int(type)];
        m_tangentType = OpenGLAttributeType[int(vertexFormat->GetAttributeType(i))];
        m_tangentOffset = vertexFormat->GetAttributeOffset(i);
    }
    else
    {
        m_hasTangent = 0;
        m_tangentChannels = 0;
        m_tangentType = 0;
        m_tangentOffset = 0;
    }

    i = vertexFormat->GetAttributeIndex(VertexAttributeUsage::BINORMAL);
    if (i >= 0)
    {
        m_hasBinormal = 1;
        type = vertexFormat->GetAttributeType(i);
        m_binormalChannels = OpenGLAttributeChannels[int(type)];
        m_binormalType = OpenGLAttributeType[int(vertexFormat->GetAttributeType(i))];
        m_binormalOffset = vertexFormat->GetAttributeOffset(i);
    }
    else
    {
        m_hasBinormal = 0;
        m_binormalChannels = 0;
        m_binormalType = 0;
        m_binormalOffset = 0;
    }

    size_t num;
    for (num = 0; num < VertexFormat::MAX_TEXCOORD_NUM; ++num)
    {
        i = vertexFormat->GetAttributeIndex(VertexAttributeUsage::TEXCOORD, num);
        if (i >= 0)
        {
            m_hasTexCoord[num] = 1;
            type = vertexFormat->GetAttributeType(i);
            m_texCoordChannels[num] = OpenGLAttributeChannels[int(type)];
            m_texCoordType[num] =
                OpenGLAttributeType[int(vertexFormat->GetAttributeType(i))];
            m_texCoordOffset[num] = vertexFormat->GetAttributeOffset(i);
        }
        else
        {
            m_hasTexCoord[num] = 0;
            m_texCoordChannels[num] = 0;
            m_texCoordType[num] = 0;
            m_texCoordOffset[num] = 0;
        }
    }

    for (num = 0; num < VertexFormat::MAX_COLOR_NUM; ++num)
    {
        i = vertexFormat->GetAttributeIndex(VertexAttributeUsage::COLOR, num);
        if (i >= 0)
        {
            m_hasColor[num] = 1;
            type = vertexFormat->GetAttributeType(i);
            m_colorChannels[num] = OpenGLAttributeChannels[int(type)];
            m_colorType[num] =
                OpenGLAttributeType[int(vertexFormat->GetAttributeType(i))];
            m_colorOffset[num] = vertexFormat->GetAttributeOffset(i);
        }
        else
        {
            m_hasColor[num] = 0;
            m_colorChannels[num] = 0;
            m_colorType[num] = 0;
            m_colorOffset[num] = 0;
        }
    }

    i = vertexFormat->GetAttributeIndex(VertexAttributeUsage::BLENDINDICES);
    if (i >= 0)
    {
        m_hasBlendIndices = 1;
        type = vertexFormat->GetAttributeType(i);
        m_blendIndicesChannels = OpenGLAttributeChannels[int(type)];
        m_blendIndicesType = OpenGLAttributeType[int(vertexFormat->GetAttributeType(i))];
        m_blendIndicesOffset = vertexFormat->GetAttributeOffset(i);
    }
    else
    {
        m_hasBlendIndices = 0;
        m_blendIndicesChannels = 0;
        m_blendIndicesType = 0;
        m_blendIndicesOffset = 0;
    }

    i = vertexFormat->GetAttributeIndex(VertexAttributeUsage::BLENDWEIGHT);
    if (i >= 0)
    {
        m_hasBlendWeight = 1;
        type = vertexFormat->GetAttributeType(i);
        m_blendWeightChannels = OpenGLAttributeChannels[int(type)];
        m_blendWeightType = OpenGLAttributeType[int(vertexFormat->GetAttributeType(i))];
        m_blendWeightOffset = vertexFormat->GetAttributeOffset(i);
    }
    else
    {
        m_hasBlendWeight = 0;
        m_blendWeightChannels = 0;
        m_blendWeightType = 0;
        m_blendWeightOffset = 0;
    }

    i = vertexFormat->GetAttributeIndex(VertexAttributeUsage::FOGCOORD);
    if (i >= 0)
    {
        m_hasFogCoord = 1;
        type = vertexFormat->GetAttributeType(i);
        m_fogCoordChannels = OpenGLAttributeChannels[int(type)];
        m_fogCoordType = OpenGLAttributeType[int(vertexFormat->GetAttributeType(i))];
        m_fogCoordOffset = vertexFormat->GetAttributeOffset(i);
    }
    else
    {
        m_hasFogCoord = 0;
        m_fogCoordChannels = 0;
        m_fogCoordType = 0;
        m_fogCoordOffset = 0;
    }

    i = vertexFormat->GetAttributeIndex(VertexAttributeUsage::PSIZE);
    if (i >= 0)
    {
        m_hasPSize = 1;
        type = vertexFormat->GetAttributeType(i);
        m_pSizeChannels = OpenGLAttributeChannels[int(type)];
        m_pSizeType = OpenGLAttributeType[int(vertexFormat->GetAttributeType(i))];
        m_pSizeOffset = vertexFormat->GetAttributeOffset(i);
    }
    else
    {
        m_hasPSize = 0;
        m_pSizeChannels = 0;
        m_pSizeType = 0;
        m_pSizeOffset = 0;
    }

}

PlatformVertexFormat::~PlatformVertexFormat()
{
}

/************************************************************************/
/* Public m_embers                                                       */
/************************************************************************/

void PlatformVertexFormat::Enable(Renderer *)
{
    // Use the enabled vertex buffer for data pointers.
    if (m_hasPosition)
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(m_positionChannels, m_positionType, m_stride,
                        (char *)0 + m_positionOffset);
    }

    if (m_hasNormal)
    {
#ifdef FALCON_ENGINE_USE_OPENGL2_NORMAL_ATTRIBUTES
        glEnableVertexAttribArrayARB(2);
        glVertexAttribPointerARB(2, m_normalChannels, m_normalType, GL_FALSE,
                                 m_stride, (char *)0 + m_normalOffset);
#else
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(m_normalType, m_stride, (char *)0 + m_normalOffset);
#endif
    }

    if (m_hasTangent)
    {
        glEnableVertexAttribArrayARB(14);
        glVertexAttribPointerARB(14, m_tangentChannels, m_tangentType, GL_FALSE,
                                 m_stride, (char *)0 + m_tangentOffset);
    }

    if (m_hasBinormal)
    {
        glEnableVertexAttribArrayARB(15);
        glVertexAttribPointerARB(15, m_binormalChannels, m_binormalType,
                                 GL_FALSE, m_stride, (char *)0 + m_binormalOffset);
    }

    unsigned int num;
    for (num = 0; num < VertexFormat::MAX_TEXCOORD_NUM; ++num)
    {
        if (m_hasTexCoord[num])
        {
            glClientActiveTexture(GL_TEXTURE0 + num);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(m_texCoordChannels[num], m_texCoordType[num],
                              m_stride, (char *)0 + m_texCoordOffset[num]);
        }
    }

    if (m_hasColor[0])
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(m_colorChannels[0], m_colorType[0], m_stride,
                       (char *)0 + m_colorOffset[0]);
    }

    if (m_hasColor[1])
    {
        glEnableClientState(GL_SECONDARY_COLOR_ARRAY);
        glSecondaryColorPointer(m_colorChannels[1], m_colorType[1], m_stride,
                                (char *)0 + m_colorOffset[1]);
    }

    if (m_hasBlendIndices)
    {
        glEnableClientState(GL_MATRIX_INDEX_ARRAY_ARB);
        glMatrixIndexPointerARB(m_blendIndicesChannels, m_blendIndicesType,
                                m_stride, (char *)0 + m_blendIndicesOffset);
    }

    if (m_hasBlendWeight)
    {
        glEnableClientState(GL_WEIGHT_ARRAY_ARB);
        glWeightPointerARB(m_blendWeightChannels, m_blendWeightType, m_stride,
                           (char *)0 + m_blendWeightOffset);
    }

    if (m_hasFogCoord)
    {
        glEnableVertexAttribArrayARB(5);
        glVertexAttribPointerARB(5, m_fogCoordChannels, m_fogCoordType,
                                 GL_FALSE, m_stride, (char *)0 + m_fogCoordOffset);

        // Pre-OpenGL2 call, but there is no ability to specify the number
        // of channels.
        //
        // glEnableClientState(GL_FOG_COORDINATE_ARRAY_EXT);
        // glFogCoordPointerEXT(m_fogCoordType, m_stride,
        //     (char*)0 + m_fogCoordOffset);
    }

    if (m_hasPSize)
    {
        glEnableVertexAttribArrayARB(6);
        glVertexAttribPointerARB(6, m_pSizeChannels, m_pSizeType, GL_FALSE,
                                 m_stride, (char *)0 + m_pSizeOffset);
    }
}

void PlatformVertexFormat::Disable(Renderer *)
{
    if (m_hasPosition)
    {
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    if (m_hasNormal)
    {
#ifdef FALCON_ENGINE_USE_OPENGL2_NORMAL_ATTRIBUTES
        glDisableVertexAttribArrayARB(2);
#else
        glDisableClientState(GL_NORMAL_ARRAY);
#endif
    }

    if (m_hasTangent)
    {
        glDisableVertexAttribArrayARB(14);
    }

    if (m_hasBinormal)
    {
        glDisableVertexAttribArrayARB(15);
    }

    unsigned int num;
    for (num = 0; num < VertexFormat::MAX_TEXCOORD_NUM; ++num)
    {
        if (m_hasTexCoord[num])
        {
            glClientActiveTexture(GL_TEXTURE0 + num);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
    }

    if (m_hasColor[0])
    {
        glDisableClientState(GL_COLOR_ARRAY);
    }

    if (m_hasColor[1])
    {
        glDisableClientState(GL_SECONDARY_COLOR_ARRAY);
    }

    if (m_hasBlendIndices)
    {
        glDisableClientState(GL_MATRIX_INDEX_ARRAY_ARB);
    }

    if (m_hasBlendWeight)
    {
        glDisableClientState(GL_WEIGHT_ARRAY_ARB);
    }

    if (m_hasFogCoord)
    {
        glDisableVertexAttribArrayARB(5);

        // Pre-OpenGL2 call, but there is no ability to specify the number
        // of channels.
        //
        // glDisableClientState(GL_FOG_COORDINATE_ARRAY_EXT);
    }

    if (m_hasPSize)
    {
        glDisableVertexAttribArrayARB(6);
    }
}

}
