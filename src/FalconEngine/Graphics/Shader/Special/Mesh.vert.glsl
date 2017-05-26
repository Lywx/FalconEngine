#version 430

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

out Vout
{
    vec3 EyeNormal;
    vec3 EyePosition;
    vec2 TexCoord;
} vout;

uniform mat3 NormalTransform;
uniform mat4 ModelViewTransform;
uniform mat4 ModelViewProjectionTransform;

void main()
{
    vout.EyeNormal = normalize(NormalTransform * Normal);
    vout.EyePosition = vec3(ModelViewTransform * vec4(Position, 1.0));
    vout.TexCoord = TexCoord;

    gl_Position = ModelViewProjectionTransform * vec4(Position, 1.0);
}
