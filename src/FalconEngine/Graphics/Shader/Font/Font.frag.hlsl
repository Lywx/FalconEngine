#include "fe_Texture.hlsl"

struct Vout
{
    float4 Position  : SV_POSITION;
    float2 TexCoord  : TEXCOORD0;
    float4 FontColor : COLOR0;
    float  FontEdge  : BLENDWEIGHT0;
    nointerpolation int FontPage : BLENDINDICES0;
    float  FontWidth : BLENDWEIGHT1;
};

float4 
main(Vout fin) : SV_TARGET 
{
    float fontDistance = 1.0 - fe_TextureFont.Sample(fe_TextureFontSampler, 
        float3(fin.TexCoord, float(fin.FontPage))).a;
    float fontAlpha = 1.0 - smoothstep(fin.FontWidth, fin.FontWidth + fin.FontEdge, fontDistance);

    return float4(fin.FontColor.xyz, fontAlpha);
}