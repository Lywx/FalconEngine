#version 430 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vout
{
    vec3 EyeNormal;
    vec3 EyePosition;
} gin[];

out Gout
{
    vec3 EyePosition;
    vec3 EyeNormal;
    noperspective vec3 Distance;
} gout;

uniform mat4 ScreenTransform;  

void 
main()
{
    // Transform each vertex into screen space
    vec2 p0 = vec2(ScreenTransform * (gl_in[0].gl_Position / gl_in[0].gl_Position.w));
    vec2 p1 = vec2(ScreenTransform * (gl_in[1].gl_Position / gl_in[1].gl_Position.w));
    vec2 p2 = vec2(ScreenTransform * (gl_in[2].gl_Position / gl_in[2].gl_Position.w));

    // Compute each vertex's distance vector
    float a = length(p1 - p2);
    float b = length(p2 - p0);
    float c = length(p1 - p0);

    float alpha = acos((b * b + c * c - a * a) / (2.0 * b * c));
    float beta = acos((a * a + c * c - b * b) / (2.0 * a * c));

    float ha = abs(c * sin(beta));
    float hb = abs(c * sin(alpha));
    float hc = abs(b * sin(alpha));

    gout.EyePosition = gin[0].EyePosition;
    gout.EyeNormal = gin[0].EyeNormal;
    gout.Distance = vec3(ha, 0, 0);
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gout.EyePosition = gin[1].EyePosition;
    gout.EyeNormal = gin[1].EyeNormal;
    gout.Distance = vec3(0, hb, 0 );
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gout.EyePosition = gin[2].EyePosition;
    gout.EyeNormal = gin[2].EyeNormal;
    gout.Distance = vec3(0, 0, hc);
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}

