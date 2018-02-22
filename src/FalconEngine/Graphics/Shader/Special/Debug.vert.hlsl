struct Vin
{
    float3 Position : POSITION0;
    float4 Color : COLOR1;
};

struct Vout
{
    float4 Position : SV_POSITION;
    noperspective float4 Color : COLOR;
};
 
cbuffer TransformBuffer
{
    float4x4 ViewProjectionTransform;
};

Vout
main(Vin vin) 
{
    Vout vout;
    vout.Color = vin.Color;

    // Assume the position is in world space.
    vout.Position = mul(ViewProjectionTransform, float4(vin.Position, 1.0));
    
    return vout;
}
