#pragma once

#include <FalconEngine/Graphics/Renderers/RendererExtensions.h>
#include <FalconEngine/Graphics/Resources/VertexFormat.h>

namespace FalconEngine {

class Renderer;

class FALCON_ENGINE_GRAPHICS_ITEM PlatformVertexFormat
{
public:
    PlatformVertexFormat(Renderer *, const VertexFormat *vertexFormat);
    ~PlatformVertexFormat();

    void Enable(Renderer *);
    void Disable(Renderer *);

private:
    int m_stride;

    GLuint m_hasPosition;
    GLuint m_positionChannels;
    GLuint m_positionType;
    GLuint m_positionOffset;

    GLuint m_hasNormal;
    GLuint m_normalChannels;
    GLuint m_normalType;
    GLuint m_normalOffset;

    GLuint m_hasTangent;
    GLuint m_tangentChannels;
    GLuint m_tangentType;
    GLuint m_tangentOffset;

    GLuint m_hasBinormal;
    GLuint m_binormalChannels;
    GLuint m_binormalType;
    GLuint m_binormalOffset;

    GLuint m_hasTexCoord[VertexFormat::MAX_TEXCOORD_NUM];
    GLuint m_texCoordChannels[VertexFormat::MAX_TEXCOORD_NUM];
    GLuint m_texCoordType[VertexFormat::MAX_TEXCOORD_NUM];
    GLuint m_texCoordOffset[VertexFormat::MAX_TEXCOORD_NUM];

    GLuint m_hasColor[VertexFormat::MAX_COLOR_NUM];
    GLuint m_colorChannels[VertexFormat::MAX_COLOR_NUM];
    GLuint m_colorType[VertexFormat::MAX_COLOR_NUM];
    GLuint m_colorOffset[VertexFormat::MAX_COLOR_NUM];

    GLuint m_hasBlendIndices;
    GLuint m_blendIndicesChannels;
    GLuint m_blendIndicesType;
    GLuint m_blendIndicesOffset;

    GLuint m_hasBlendWeight;
    GLuint m_blendWeightChannels;
    GLuint m_blendWeightType;
    GLuint m_blendWeightOffset;

    GLuint m_hasFogCoord;
    GLuint m_fogCoordChannels;
    GLuint m_fogCoordType;
    GLuint m_fogCoordOffset;

    GLuint m_hasPSize;
    GLuint m_pSizeChannels;
    GLuint m_pSizeType;
    GLuint m_pSizeOffset;
};

}
