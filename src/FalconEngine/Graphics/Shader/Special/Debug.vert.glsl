#version 430 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Color;

out Vout
{
    noperspective vec4 Color;
} vout;

layout(std140) uniform TransformBuffer
{
    mat4 ViewProjectionTransform;
};

void
main()
{
    vout.Color = Color;

    // Assume the position is in world space.
    gl_Position = ViewProjectionTransform * vec4(Position, 1); 
}
