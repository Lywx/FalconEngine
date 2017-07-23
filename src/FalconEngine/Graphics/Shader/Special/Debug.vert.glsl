#version 430 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Color;

out Vout
{
    noperspective vec4 Color;
} vout;

void
main()
{
    vout.Color = Color;

    gl_Position = vec4(Position, 1); 
}
