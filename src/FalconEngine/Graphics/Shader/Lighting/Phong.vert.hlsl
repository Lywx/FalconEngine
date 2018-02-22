#include "Phong.incl.hlsl"

cbuffer TransformBuffer
{
   float4x4 ModelViewProjectionTransform;
   float4x4 ModelViewTransform;
   float3x3 NormalTransform;
};

Vout 
main(Vin vin)
{
    Vout vout;

    vout.EyeNormal = normalize(mul(NormalTransform, vin.Normal));
    vout.EyePosition = mul(ModelViewTransform, float4(vin.Position, 1.0)).xyz;
    vout.TexCoord = vin.TexCoord;
    vout.Position = mul(ModelViewProjectionTransform, float4(vin.Position, 1.0));

    return vout;
}