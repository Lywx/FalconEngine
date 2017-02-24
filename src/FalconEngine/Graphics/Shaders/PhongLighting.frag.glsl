#version 330 core

#fe_extension : enable
#include "fe_Texture.glsl"
#fe_extension : disable

in Vout
{
    noperspective vec3 EyePosition
    noperspective vec3 EyeNormal;
    vec2               TexCoord;
} fin;

layout(location = 0) out vec4 FragColor;

struct Light
{
    vec4 Ambient;
    vec4 Diffuse;
    vec4 Specular;
    vec3 Direction;
};

struct Material 
{
    float Shininess;
};

uniform Light    Light;
uniform Material Material;
uniform mat4     MVTransform;

void main() 
{ 
    vec4 eyeLightDirection = MVTransform * vec4(Light.Direction, 0);
    vec3 eyeLightDirectionNormalized = normalize(eyeLightDirection.xyz); 

    // dot(n, l)
    float dotNL = max(0, dot(fin.EyeNormal, eyeLightDirectionNormalized));     

    vec3 eyeReflectionDirectionNormalized = reflect(-eyeLightDirectionNormalized, fin.Normal);
    
    // dot(v, r)
    float dotVR = max(dot(-fin.EyePosition, eyeReflectionDirectionNormalized), 0.0);

    vec3 materialAmbient = vec3(texture(fe_TextureAmbient, fin.TexCoords));
    vec3 materialDiffuse = vec3(texture(fe_TextureDiffuse, fin.TexCoords));
    vec3 materialEmissive = vec3(texture((fe_TextureEmissive, fin.TexCoords));
    vec3 materialSpecular = vec3(texture((fe_TextureSpecular, fin.TexCoords));

    // Fletcher Dunn, Ian Parberry 3D Math Primer for Graphics and Game Development, 2nd, 2011, P407
    vec3 ambient = Light.Ambient * materialAmbient;
    vec3 diffuse = Light.Diffuse * materialDiffuse * dotNL;
    vec3 specular = Light.Specular * materialSpecular * pow(dotVR, Material.Shininess);
    vec3 emissive = materialEmissive;

    FragColor = vec4(ambient + diffuse + emissive + specular, 1.0f);
}