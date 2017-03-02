#version 430 core

#fe_extension : enable
#include "fe_Texture.glsl"
#include "fe_Function.glsl"
#fe_extension : disable

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;

out Vout
{
    noperspective vec3 EyePosition;
    noperspective vec3 EyeNormal;
    vec2               TexCoord;
} vout;
 
uniform mat4 MVPTransform;
uniform mat4 MVTransform;
uniform mat3 NormalTransform;

void main()
{      
    CalcEyeSpace(Position, Normal, vout.EyePosition, vout.EyeNormal);
    vout.TexCoord = TexCoord;

    gl_Position = MVPTransform * vec4(Position, 1); 
}
 