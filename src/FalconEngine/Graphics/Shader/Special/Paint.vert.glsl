#version 430 core

layout(location = 0) in vec3 Position;
layout(location = 0) in vec3 Normal;
layout(location = 0) in vec3 TexCoord;

out Vout
{
    vec4 Color;
} vout;
 
uniform mat4 ModelViewProjectionTransform;
uniform vec4 Color;

void 
main()
{      
    vout.Color = Color;
    
    gl_Position = ModelViewProjectionTransform * vec4(Position, 1); 
}
 