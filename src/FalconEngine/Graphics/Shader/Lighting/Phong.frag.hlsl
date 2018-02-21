#include "fe_Material.hlsl"
#include "fe_Texture.hlsl"
#include "fe_Lighting.hlsl"

#include "Phong.incl.hlsl"

#define PointLightNumMax 6
#define SpotLightNumMax 6

cbuffer LightBuffer
{
    // 4 x float4.
    DirectionalLightData DirectionalLight;

    // 4 x float4 x PointLightNumMax
    PointLightData PointLightArray[PointLightNumMax];

//  SpotLightData SpotLightArray[SpotLightNumMax];

    int PointLightNum;
    int SpotLightNum;
    int Pad0;
    int Pad1;
};

cbuffer MaterialBuffer
{
    // 4 x float4
    MaterialColorData MaterialColor;
    
    // 2 x float4
    MaterialTextureData MaterialTexture;
};

// @status Finished.
float3 
CalcDirectionalLight(DirectionalLightData light, float3 eyeN, float3 eyeV, float2 texCoord)
{
    // Point to light source.
    float3 eyeL = normalize(light.EyeDirection);

    float3 cAmbient;
    float3 cDiffuse;
    float3 cEmissive;
    float3 cSpecular; 

    CalcPhongLighting(
        texCoord, 

    // @parameter Transform.
        eyeN, 
        eyeV, 
        eyeL, 

    // @parameter Light Source.
        light.Ambient, 
        light.Diffuse, 
        light.Specular,

    // @parameter Material Color.
        MaterialColor,
        MaterialTexture,

    // @return Standard Phong lighting contribution.
        cAmbient, 
        cDiffuse, 
        cEmissive,
        cSpecular);

    return cAmbient + cDiffuse + cEmissive + cSpecular;
}

// @status Finished.
float3 
CalcPointLight(PointLightData light, float3 eyeN, float3 eyeV, float3 eyePosition, float2 texCoord)
{
    // Point to light source.
    float3 eyeL = normalize(light.EyePosition - eyePosition);

    float3 cAmbient;
    float3 cDiffuse;
    float3 cEmissive;
    float3 cSpecular;

    CalcPhongLighting(
        texCoord, 

    // @parameter Transform.
        eyeN, 
        eyeV, 
        eyeL, 

    // @parameter Light Source.
        light.Ambient, 
        light.Diffuse, 
        light.Specular,

    // @parameter Material Color.
        MaterialColor,
        MaterialTexture,

    // @return Standard Phong lighting contribution.
        cAmbient, 
        cDiffuse, 
        cEmissive,
        cSpecular);

    // TODO(Wuxiang): ???

    // Attenuation
    float distance = length(light.EyePosition - eyePosition);
    float attenuation = 1.0f / (light.Constant + light.Linear * distance + 
                 light.Quadratic * (distance * distance));    

    cAmbient  *= attenuation;
    cDiffuse  *= attenuation;
    cSpecular *= attenuation;

    return cAmbient + cDiffuse + cEmissive + cSpecular;
} 

// @status Finished.
float3 
CalcSpotLight(SpotLightData light, float3 eyeN, float3 eyeV, float3 eyePosition, float2 texCoord)
{
    // Point to light source.
    float3 eyeL = normalize(light.EyePosition - eyePosition);

    float3 cAmbient;
    float3 cDiffuse;
    float3 cEmissive;
    float3 cSpecular;

    CalcPhongLighting(
        texCoord, 

        // @parameter Transform.
        eyeN, 
        eyeV, 
        eyeL, 

        // @parameter Light Source.
        light.Ambient, 
        light.Diffuse, 
        light.Specular,

        // @parameter Material Color.
        MaterialColor,
        MaterialTexture,

        // @return Standard Phong lighting contribution.
        cAmbient, 
        cDiffuse, 
        cEmissive,
        cSpecular);

    // Attenuation
    float distance = length(light.EyePosition - eyePosition);
    float attenuation = 1.0f / (light.Constant + light.Linear * distance + light.Quadratic * (distance * distance));

    // Spotlight intensity
    float cosAngleDifference = dot(eyeL, normalize(light.EyeDirection)); 
    float cosMaxDifference = light.CosAngleInner - light.CosAngleOuter;
    float intensity = clamp((cosAngleDifference - light.CosAngleOuter) / cosMaxDifference, 0.0, 1.0);

    cAmbient *= attenuation * intensity;
    cDiffuse *= attenuation * intensity;
    cSpecular *= attenuation * intensity;
    
    return cAmbient + cDiffuse + cEmissive + cSpecular;
}

float4 
main(Vout fin, bool frontFacing : SV_IsFrontFace) : SV_TARGET
{
    float3 eyeN = normalize(fin.EyeNormal);

    // Point to camera.
    float3 eyeV = normalize(-fin.EyePosition); 

    float3 frontColor = CalcDirectionalLight(DirectionalLight, eyeN, eyeV, fin.TexCoord);
    for (int i = 0; i < PointLightNum; ++i) 
    {
        frontColor += CalcPointLight(PointLightArray[i], eyeN, eyeV, fin.EyePosition, fin.TexCoord);
    }

    float3 backColor = CalcDirectionalLight(DirectionalLight, -eyeN, eyeV, fin.TexCoord);
    for (int i = 0; i < PointLightNum; ++i) 
    {
        backColor += CalcPointLight(PointLightArray[i], -eyeN, eyeV, fin.EyePosition, fin.TexCoord);
    }

    // for (int i = 0; i < SpotLightNum; ++i) 
    // {
    //     result += CalcSpotLight(SpotLightArray[i], eyeN, eyeV, fin.EyePosition, fin.TexCoord);
    // }

    float4 fragColor;
    if (frontFacing) 
    {
        fragColor = float4(frontColor, 1.0);
    } 
    else 
    {
        fragColor = float4(backColor, 1.0);
    }

    return fragColor;
}