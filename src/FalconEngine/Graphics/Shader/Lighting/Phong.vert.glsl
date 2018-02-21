#version 430 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;

out Vout
{
    noperspective vec3 EyePosition;
    noperspective vec3 EyeNormal;
    vec2               TexCoord;
} vout;
 
layout(std140) uniform TransformBuffer
{
   mat4 ModelViewProjectionTransform;
   mat4 ModelViewTransform;
   mat3 NormalTransform;
};

void 
main()
{      
    // vout.EyeNormal = mat3(transpose(inverse(ModelViewTransform))) * Normal;
    vout.EyeNormal = normalize(NormalTransform * Normal);
    vout.EyePosition = (ModelViewTransform * vec4(Position, 1.0)).xyz;
    vout.TexCoord = TexCoord;

    gl_Position = ModelViewProjectionTransform * vec4(Position, 1.0); 
}
 