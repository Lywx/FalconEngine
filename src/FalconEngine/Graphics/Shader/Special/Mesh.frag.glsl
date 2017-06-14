#version 430 core

in Gout
{
    noperspective vec3 Distance;
    vec3 EyePosition;
    vec3 EyeNormal;
    vec2 TexCoord;
} fin;

layout(location = 0) out vec4 FragColor;

#fe_extension : enable
#include "fe_Material.glsl"
#fe_extension : disable

uniform vec3 AmbientColor;
uniform bool TextureEnabled;

// @require #include "fe_Material.glsl".
vec3 
CalcMaterialColor()
{
    vec3 cAmbient  = AmbientColor + vec3(1.0) * fe_Material.Ambient;
    vec3 cDiffuse  = vec3(1.0) * fe_Material.Diffuse * 0.5;
    vec3 cEmissive = vec3(0.0);
    vec3 cSpecular = vec3(1.0) * fe_Material.Specular * pow(0.5, fe_Material.Shininess);

    return cAmbient + cDiffuse + cEmissive + cSpecular;
}

#fe_extension : enable
#include "fe_Texture.glsl"
#fe_extension : disable

// @require #include "fe_Texture.glsl".
vec3
CalcTextureColor(vec2 texCoord)
{
    vec3 cAmbient;
    if (fe_TextureAmbientExist)
    {
       cAmbient = AmbientColor + vec3(1.0) * vec3(texture(fe_TextureAmbient, texCoord));
    }

    vec3 cDiffuse;
    if (fe_TextureDiffuseExist)
    {
        cDiffuse = vec3(1.0) * vec3(texture(fe_TextureDiffuse, texCoord)) * 0.5;
    }

    vec3 cEmissive = vec3(0.0);

    float mShininess;
    if (fe_TextureShininessExist)
    {
        mShininess = texture(fe_TextureShininess, texCoord).a;
    }

    vec3 cSpecular;
    if (fe_TextureSpecularExist)
    {
        cSpecular = vec3(1.0) * vec3(texture(fe_TextureSpecular, texCoord)) * pow(0.5, mShininess);
    }

    return cAmbient + cDiffuse + cEmissive + cSpecular;
}

struct LineData
{
    vec4  Color;
    float Width;
};

uniform LineData Line;

void
main()
{
    vec4 color;
    
    if (TextureEnabled)
    {
        color = vec4(CalcMaterialColor(), 1.0);
    }
    else
    {
        color = vec4(CalcTextureColor(fin.TexCoord), 1.0);
    }

    // Find the smallest distance
    float lineDistance = min(fin.Distance.x, fin.Distance.y);
    lineDistance = min(lineDistance, fin.Distance.z);

    float mixFactor = smoothstep(Line.Width - 1, Line.Width + 1, lineDistance);
    FragColor = mix(Line.Color, color, mixFactor);
}
