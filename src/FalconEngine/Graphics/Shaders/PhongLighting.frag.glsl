#version 330 core

#fe_extension : enable
#include "fe_Texture.glsl"
#fe_extension : disable

in Vout
{
    noperspective vec3 WorldPosition;
    noperspective vec3 EyePosition
    noperspective vec3 EyeNormal;
    vec2               TexCoord;
} fin;

layout(location = 0) out vec4 FragColor;

struct DirectionalLight
{
    vec4 Ambient;
    vec4 Diffuse;
    vec4 Specular;

    vec3 Direction;
};

struct PointLight
{
    vec4 Ambient;
    vec4 Diffuse;
    vec4 Specular;

    vec3 Position;

    float Constant;
    float Linear;
    float Quadratic;
};

struct SpotLight
{
    vec4 Ambient;
    vec4 Diffuse;
    vec4 Specular;

    float CosAngleInner;
    float CosAngleOuter;
    vec3 Direction;
    vec3 Position;

    float Constant;
    float Linear;
    float Quadratic;
};

uniform DirectionalLight          DirectionalLight;
#define PointLightNum 6
uniform PointLight[PointLightNum] PointLightArray;

uniform mat4                      MVTransform;

void main() 
{ 
    vec3 eyeNormalNormalized = normalize(fin.EyeNormal);

    // Point to camera.
    vec3 viewDirection = normalize(-fin.EyePosition); 

    vec3 result = CalcDirectionalLight(DirectionalLight, eyeNormalNormalized, viewDirection);
    for(int i = 0; i < PointLightNum; ++i) 
    {
        result += CalcPointLight(PointLightArray[i], eyeNormalNormalized, viewDirection, fin.WorldPosition);
    }

    FragColor = vec4(result, 1.0);
}

// @status Finished.
vec3 CalcDirectionalLight(DirectionalLight light, vec3 eyeNormalNormalized, vec3 viewDirection)
{
    vec3 eyeLightDirectionNormalized = normalize(MVTransform * vec4(light.Direction, 0)).xyz;
    vec3 eyeReflectionDirectionNormalized = reflect(-eyeLightDirectionNormalized, eyeNormalNormalized);

    // dot(n, l)
    float dotNL = max(0, dot(eyeNormalNormalized, eyeLightDirectionNormalized));     

    // dot(v, r)
    float dotVR = max(dot(viewDirection, eyeReflectionDirectionNormalized), 0.0);

    vec3 materialAmbient   = vec3(texture(fe_TextureAmbient,   fin.TexCoords));
    vec3 materialDiffuse   = vec3(texture(fe_TextureDiffuse,   fin.TexCoords));
    vec3 materialEmissive  = vec3(texture(fe_TextureEmissive,  fin.TexCoords));
    vec3 materialShininess = vec3(texture(fe_TextureShininess, fin.TexCoords));
    vec3 materialSpecular  = vec3(texture(fe_TextureSpecular,  fin.TexCoords));

    vec3 ambient  = light.Ambient * materialAmbient;
    vec3 diffuse  = light.Diffuse * materialDiffuse * dotNL;
    vec3 specular = light.Specular * materialSpecular * pow(dotVR, materialShininess);
    vec3 emissive = materialEmissive;

    return ambient + diffuse + emissive + specular;
}

// @status TODO.
vec3 CalcSpotLight(SpotLight light, vec3 eyeNormalNormalized, vec3 viewDirection, vec3 worldPosition)
{
    // TODO
    vec3 worldLightDirection = normalize(worldPosition - light.Position);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return (ambient + diffuse + specular);
}