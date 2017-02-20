#version 330 // core

// Fragment shader output
layout(location = 0) out vec4 vFragColor;
 
//input from the vertex shader
smooth in vec3 vEyeSpaceNormal;    //interpolated eye space normal      

// Model-view matrix
uniform mat4 MV;

// Light direction is in object space
uniform vec3 light_direction;    

// Diffuse colour for surface
uniform vec3 diffuse_color;

void main() 
{ 
    //get light direction in eye space by multiplying with the modelview matrix
    vec4 vEyeSpaceLightDirection = MV*vec4(light_direction,0);
    //normalize the light direction to get the light vector
    vec3 L = normalize(vEyeSpaceLightDirection.xyz); 
    //calculate the diffuse component
    float diffuse = max(0, dot(vEyeSpaceNormal, L));     
    //return the product of the diffuse component with the diffuse color as the 
    //fragment output
    vFragColor =  diffuse*vec4(diffuse_color,1);     
}