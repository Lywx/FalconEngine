struct Vin
{
    float3 Position : POSITION0;
    float3 Normal : NORMAL1;
    float3 TexCoord : TEXCOORD2;
};

struct Vout
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};
 
cbuffer PaintBuffer
{
    float4x4 ModelViewProjectionTransform;
    float4 Color;
};

Vout
main(Vin vin) 
{      
    Vout vout;

    vout.Color = Color;
    vout.Position = mul(float4(vin.Position, 1.0), ModelViewProjectionTransform); 

    return vout;
}
 