#version 420 core

in Vout
{
    vec2  TextureCoord;
    vec4  FontColor;
    float FontEdge;
    float FontWidth;
    flat int FontPage;
} fin;

// Texture array of different page of texture atlas
layout (binding = 0)  uniform sampler2DArray Texture;

layout (location = 0) out     vec4           FragColor;

void main(void)
{
    float fontDistance = 1.0 - texture(Texture, vec3(fin.TextureCoord, float(fin.FontPage))).a;
    float fontAlpha = 1.0 - smoothstep(fin.FontWidth, fin.FontWidth + fin.FontEdge, fontDistance);

    FragColor = vec4(fin.FontColor.xyz, fontAlpha);
}