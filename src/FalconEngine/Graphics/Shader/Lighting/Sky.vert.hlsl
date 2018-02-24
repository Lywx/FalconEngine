cbuffer SkyBuffer : register(b0)
{
   float4x4 ViewProjectionTransform;
};

struct Vin
{
    float3 Position : POSITION0;
    float3 Normal : NORMAL1;
    float2 TexCoord : TEXCOORD2;
};

struct Vout
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD0;
};

Vout 
main(Vin vin)
{
    Vout vout;

    vout.TexCoord = vin.TexCoord;
    vout.Position = mul(ViewProjectionTransform, float4(vin.Position, 1.0));

    return vout;
}