#version 430 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;

out Vout
{
    vec2 TexCoord;
} vout;
 
layout(std140) uniform SkyBuffer
{
    mat4 ViewProjectionTransform;
};

void 
main()
{      
    vout.TexCoord = TexCoord;
    
    gl_Position = ViewProjectionTransform * vec4(Position, 1); 
}
 