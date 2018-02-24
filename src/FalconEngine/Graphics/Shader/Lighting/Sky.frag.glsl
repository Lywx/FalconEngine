#version 430 core

#fe_extension : enable
#include "fe_Texture.glsl"
#fe_extension : disable

in Vout
{
    vec2 TexCoord;
} fin;
 
layout(location = 0) out vec4 FragColor;

void
main()
{
    FragColor = vec4(texture(fe_TextureDiffuse, fin.TexCoord).xyz, 1.0);
}
