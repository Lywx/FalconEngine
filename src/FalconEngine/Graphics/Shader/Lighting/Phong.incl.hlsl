#ifndef PHONG_INCL_HLSL
#define PHONG_INCL_HLSL

struct Vin
{
    float3 Position : POSITION0;
    float3 Normal : NORMAL1;
    float2 TexCoord : TEXCOORD2;
};

struct Vout
{
    float4 Position : SV_POSITION;
    noperspective float3 EyePosition : POSITION;
    noperspective float3 EyeNormal : NORMAL;
    float2 TexCoord : TEXCOORD0;
};
 
#endif