#version 430 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Color;
layout(location = 2) in int  Camera;

out Vout
{
    noperspective vec4 Color;
} vout;

#define CameraMaxNum 4
uniform mat4[CameraMaxNum] ViewProjectionTransformArray;

void
main()
{
    vout.Color = Color;

    // Assume the position is in world space.
    gl_Position = ViewProjectionTransformArray[Camera] * vec4(Position, 1); 
}
