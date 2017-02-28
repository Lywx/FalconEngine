#version 430 core

#fe_extension : enable
#include "fe_Texture.glsl"
#fe_extension : disable

in Vout
{
    vec2  TexCoord;
    vec4  FontColor;
    float FontEdge;
    float FontWidth;
    flat int FontPage;
} fin;

layout (location = 0) out vec4 FragColor;

void main(void)
{
    float fontDistance = 1.0 - texture(fe_TextureFont, vec3(fin.TexCoord, float(fin.FontPage))).a;
    float fontAlpha = 1.0 - smoothstep(fin.FontWidth, fin.FontWidth + fin.FontEdge, fontDistance);

    FragColor = vec4(fin.FontColor.xyz, fontAlpha);
}