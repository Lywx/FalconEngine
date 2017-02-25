#version 330 core
  
layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;

out Vout
{
    noperspective vec3 WorldPosition;
    noperspective vec3 EyePosition;
    noperspective vec3 EyeNormal;
    vec2               TexCoord;
} vout;
 
uniform mat4 MVPTransform;
uniform mat4 MVTransform;
uniform mat4 ModelTransform;
uniform mat3 NormalTransform;

void main()
{      
    vout.WorldPosition = (ModelTransform * vec4(Position, 1.0f)).xyz;
    vout.EyePosition = (MVTransform * vec4(Position, 1.0f)).xyz;
    vout.EyeNormal = NormalTransform * Normal; 
    vout.TexCoord = TexCoord;

    gl_Position = MVPTransform * vec4(Position, 1); 
}
 