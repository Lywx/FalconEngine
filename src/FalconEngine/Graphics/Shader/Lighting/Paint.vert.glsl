#version 430 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Color;

out Vout
{
    vec4 Color;
} vout;
 
uniform mat4 ModelViewProjectionTransform;

void 
main()
{      
    vout.Color = Color;
    
    gl_Position = ModelViewProjectionTransform * vec4(Position, 1); 
}
 