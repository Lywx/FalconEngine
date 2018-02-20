#version 430 core

#fe_extension : enable
#include "fe_Texture.glsl"
#fe_extension : disable

layout (location = 0) in vec2  Position;
layout (location = 1) in vec2  TexCoord;
layout (location = 2) in vec4  FontColor;
layout (location = 3) in float FontWidth;
layout (location = 4) in float FontEdge;

// NOTE(Wuxiang): You better not use integer here. The OpenGL conversion of 
// integer vertex attribute is so not lossless. The result would be unexpected.
layout (location = 5) in float FontPage;

layout(std140) uniform TransformBuffer
{
    mat4 ProjectionTransform;
};

out Vout
{
    vec2  TexCoord;
    vec4  FontColor;
    float FontEdge;
    float FontWidth;
    flat int FontPage;
} vout;

void main(void)
{
    gl_Position = ProjectionTransform * vec4(Position, 0.0, 1.0);

    vout.TexCoord  = TexCoord;
    vout.FontColor = FontColor;
    vout.FontEdge  = FontEdge;
    vout.FontWidth = FontWidth;
    vout.FontPage  = int(FontPage);
}
