struct Vout
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};
 
float4
main(Vout fin) : SV_TARGET
{
    return fin.Color;
}
