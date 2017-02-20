#version 330 core
  
// Per-vertex position
layout(location = 0) in vec3 vVertex;
// Per-vertex normal
layout(location = 1) in vec3 vNormal;
 
// Combined model-view projection matrix
uniform mat4 MVP;

// Normal matrix
uniform mat3 N;

// Eye space normal
smooth out vec3 vEyeSpaceNormal;

void main()
{      
    // Multiply the object space normal with the normal matrix 
    // to get the eye space normal
    vEyeSpaceNormal = N * vNormal; 

    // Multiply the combined model-view projection matrix with the object space vertex
    // position to get the clip space position
    gl_Position = MVP * vec4(vVertex, 1); 
}
 