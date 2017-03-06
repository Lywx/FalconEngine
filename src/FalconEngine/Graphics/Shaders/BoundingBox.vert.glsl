#version 430 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Color;
layout(location = 2) in mat4 ModelViewProjectionTransform;

out Vout
{
    noperspective vec4 Color;
} vout;

void
main()
{
    vout.Color = Color;

    gl_Position = ModelViewProjectionTransform * vec4(Position, 1); 
}
