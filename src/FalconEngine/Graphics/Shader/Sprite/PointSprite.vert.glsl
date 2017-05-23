#version 430

layout (location = 0) in vec3 Position;

uniform mat4 ModelViewTransform;
uniform mat4 ProjectionTransform;
uniform mat3 NormalTransform;

void main()
{
    gl_Position = ModelViewTransform * vec4(Position, 1.0);
}