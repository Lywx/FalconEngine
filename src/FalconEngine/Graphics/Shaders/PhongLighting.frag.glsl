#version 430 core

#fe_extension : enable
#include "fe_Texture.glsl"
#include "fe_Function.glsl"
#fe_extension : disable

in Vout
{
    noperspective vec3 EyePosition;
    noperspective vec3 EyeNormal;
    vec2               TexCoord;
} fin;

layout(location = 0) out vec4 FragColor;

struct DirectionalLightData
{
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    vec3 EyeDirection;
};

struct PointLightData
{
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    vec3 EyePosition;

    float Constant;
    float Linear;
    float Quadratic;
};

struct SpotLightData
{
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    float CosAngleInner;
    float CosAngleOuter;
    vec3 EyeDirection;
    vec3 EyePosition;

    float Constant;
    float Linear;
    float Quadratic;
};

uniform DirectionalLightData DirectionalLight;
// #define PointLightNum 6
// uniform PointLight[PointLightNum] PointLightArray;

uniform mat4 ModelViewTransform;

// @status Finished.
vec3 CalcDirectionalLight(DirectionalLightData light, vec3 eyeN, vec3 eyeV)
{
    // Point to light source.
    vec3 eyeL = normalize(light.EyeDirection);

    vec3 cAmbient;
    vec3 cDiffuse;
    vec3 cSpecular; 

    CalcPhongLighting(fin.TexCoord, eyeN, eyeV, eyeL, light.Ambient, light.Diffuse, light.Specular,
    cAmbient, cDiffuse, cSpecular);

    return cAmbient + cDiffuse + cSpecular;
}

// @status Finished.
vec3 CalcPointLight(PointLightData light, vec3 eyeN, vec3 eyeV, vec3 eyePosition)
{
    // Point to light source.
    vec3 eyeL = normalize(light.EyePosition - eyePosition);

    vec3 cAmbient;
    vec3 cDiffuse;
    vec3 cSpecular;

    CalcPhongLighting(fin.TexCoord, eyeN, eyeV, eyeL, light.Ambient, light.Diffuse, light.Specular,
    cAmbient, cDiffuse, cSpecular);

    // Attenuation
    float distance = length(light.EyePosition - eyePosition);
    float attenuation = 1.0f / (light.Constant + light.Linear * distance + 
                 light.Quadratic * (distance * distance));    

    cAmbient  *= attenuation;
    cDiffuse  *= attenuation;
    cSpecular *= attenuation;

    return cAmbient + cDiffuse + cSpecular;
} 

// @status Finished.
vec3 CalcSpotLight(SpotLightData light, vec3 eyeN, vec3 eyeV, vec3 eyePosition)
{
    // Point to light source.
    vec3 eyeL = normalize(light.EyePosition - eyePosition);

    vec3 cAmbient;
    vec3 cDiffuse;
    vec3 cSpecular;

    CalcPhongLighting(fin.TexCoord, eyeN, eyeV, eyeL, light.Ambient, light.Diffuse, light.Specular,
    cAmbient, cDiffuse, cSpecular);

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
    
    return cAmbient + cDiffuse + cSpecular;
}

void main() 
{ 
    vec3 eyeN = normalize(fin.EyeNormal);

    // Point to camera.
    vec3 eyeV = normalize(-fin.EyePosition); 

    vec3 result = CalcDirectionalLight(DirectionalLight, eyeN, eyeV);
    // for(int i = 0; i < PointLightNum; ++i) 
    // {
    //     result += CalcPointLight(PointLightArray[i], eyeN, eyeV, fin.EyePosition);
    // }

    // result += CalcSpotLight(Spotlight, eyeN, eyeV, fin.EyePosition);

    result += vec3(0.5, 0.5, 0.5);
    FragColor = vec4(result, 1.0);
}

