#version 430 core

in Vout
{
    noperspective vec3 EyePosition;
    noperspective vec3 EyeNormal;
    vec2               TexCoord;
} fin;

layout(location = 0) out vec4 FragColor;

#fe_extension : enable
#include "fe_Material.glsl"
#fe_extension : disable

uniform MaterialColorData MaterialColor;

uniform bool TextureAmbientExist;
uniform bool TextureDiffuseExist;
uniform bool TextureEmissiveExist;
uniform bool TextureSpecularExist;
uniform bool TextureShininessExist;

#fe_extension : enable
#include "fe_Texture.glsl"
#include "fe_Lighting.glsl"
#fe_extension : disable

uniform DirectionalLightData DirectionalLight;

#define PointLightNumMax 6
uniform int PointLightNum;
uniform PointLightData[PointLightNumMax] PointLightArray;

#define SpotLightNumMax 6
uniform int SpotLightNum;
uniform SpotLightData[SpotLightNumMax] SpotLightArray;

uniform mat4 ModelViewTransform;

// @status Finished.
vec3 
CalcDirectionalLight(DirectionalLightData light, vec3 eyeN, vec3 eyeV)
{
    // Point to light source.
    vec3 eyeL = normalize(light.EyeDirection);

    vec3 cAmbient;
    vec3 cDiffuse;
    vec3 cEmissive;
    vec3 cSpecular; 

    CalcPhongLighting(
        fin.TexCoord, 

    // @parameter Transform.
        eyeN, 
        eyeV, 
        eyeL, 

    // @parameter Light Source.
        light.Ambient, 
        light.Diffuse, 
        light.Specular,

    // @return Standard Phong lighting contribution.
        cAmbient, 
        cDiffuse, 
        cEmissive,
        cSpecular);

    return cAmbient + cDiffuse + cEmissive + cSpecular;
}

// @status Finished.
vec3 
CalcPointLight(PointLightData light, vec3 eyeN, vec3 eyeV, vec3 eyePosition)
{
    // Point to light source.
    vec3 eyeL = normalize(light.EyePosition - eyePosition);

    vec3 cAmbient;
    vec3 cDiffuse;
    vec3 cEmissive;
    vec3 cSpecular;

    CalcPhongLighting(
        fin.TexCoord, 

    // @parameter Transform.
        eyeN, 
        eyeV, 
        eyeL, 

    // @parameter Light Source.
        light.Ambient, 
        light.Diffuse, 
        light.Specular,

    // @return Standard Phong lighting contribution.
        cAmbient, 
        cDiffuse, 
        cEmissive,
        cSpecular);

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
vec3 
CalcSpotLight(SpotLightData light, vec3 eyeN, vec3 eyeV, vec3 eyePosition)
{
    // Point to light source.
    vec3 eyeL = normalize(light.EyePosition - eyePosition);

    vec3 cAmbient;
    vec3 cDiffuse;
    vec3 cEmissive;
    vec3 cSpecular;

    CalcPhongLighting(
        fin.TexCoord, 

        // @parameter Transform.
        eyeN, 
        eyeV, 
        eyeL, 

        // @parameter Light Source.
        light.Ambient, 
        light.Diffuse, 
        light.Specular,

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

void 
main() 
{ 
    vec3 eyeN = normalize(fin.EyeNormal);

    // Point to camera.
    vec3 eyeV = normalize(-fin.EyePosition); 

    vec3 result = CalcDirectionalLight(DirectionalLight, eyeN, eyeV);
    for(int i = 0; i < PointLightNum; ++i) 
    {
        result += CalcPointLight(PointLightArray[i], eyeN, eyeV, fin.EyePosition);
    }

    // for(int i = 0; i < SpotLightNum; ++i) 
    // {
    //     result += CalcSpotLight(SpotLightArray[i], eyeN, eyeV, fin.EyePosition);
    // }

    FragColor = vec4(result, 1.0);
}

