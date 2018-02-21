// 4 x float4
struct MaterialColorData
{
    vec3 Ambient;
    float Shininess;

    vec3 Diffuse;
    float Pad0;

    vec3 Emissive;
    float Pad1;

    vec3 Specular;
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
};