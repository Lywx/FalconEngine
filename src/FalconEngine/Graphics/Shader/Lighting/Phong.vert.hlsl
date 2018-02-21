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

    vout.EyeNormal = normalize(mul(vin.Normal, NormalTransform));
    vout.EyePosition = mul(float4(vin.Position, 1.0), ModelViewTransform).xyz;
    vout.TexCoord = vin.TexCoord;
    vout.Position = mul(float4(vin.Position, 1.0), ModelViewProjectionTransform);

    return vout;
}