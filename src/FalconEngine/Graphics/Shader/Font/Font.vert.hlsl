cbuffer TransformBuffer
{
    float4x4 ProjectionTransform;
};

struct Vin
{
    float2 Position  : POSITION0;
    float2 TexCoord  : TEXCOORD1;
    float4 FontColor : FONTCOLOR2;
    float  FontWidth : FONTWIDTH3;
    float  FontEdge  : FONTEDGE4;
    float  FontPage  : FONTPAGE5;
};

struct Vout
{
    float4 Position  : SV_POSITION;
    float2 TexCoord  : TEXCOORD0;
    float4 FontColor : COLOR0;
    float  FontEdge  : BLENDWEIGHT0;
    nointerpolation int FontPage : BLENDINDICES0;
    float  FontWidth : BLENDWEIGHT1;
};

Vout 
main(Vin vin)
{
    Vout vout;

    vout.Position  = mul(ProjectionTransform, float4(vin.Position, 0.0, 1.0));
    vout.TexCoord  = vin.TexCoord;
    vout.FontColor = vin.FontColor;
    vout.FontEdge  = vin.FontEdge;
    vout.FontWidth = vin.FontWidth;
    vout.FontPage  = int(vin.FontPage);

    return vout;
}