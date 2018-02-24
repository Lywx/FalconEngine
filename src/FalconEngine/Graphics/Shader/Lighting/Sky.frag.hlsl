#include "fe_Texture.hlsl"

struct Vout
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD0;
};

float4
main(Vout fin) : SV_TARGET
{
    return float4(fe_TextureDiffuse.Sample(fe_TextureDiffuseSampler, fin.TexCoord).xyz, 1.0);
}