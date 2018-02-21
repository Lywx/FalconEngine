#ifndef FE_MATERIAL_HLSL
#define FE_MATERIAL_HLSL

// 4 x float4
struct MaterialColorData
{
    float3 Ambient;
    float Shininess;

    float3 Diffuse;
    float Pad0;

    float3 Emissive;
    float Pad1;

    float3 Specular;
    float Pad2;
};

// 2 x float4
struct MaterialTextureData
{
    bool AmbientExist;
    bool DiffuseExist;
    bool EmissiveExist;
    bool SpecularExist;

    bool ShininessExist;
    bool Pad0;
    bool Pad1;
    bool Pad2;

    float2 Pad3;
};

#endif