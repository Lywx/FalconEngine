layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Color;
layout(location = 2) in int  Camera;

struct Vin
{
    float3 Position : POSITION0;
    float4 Color : COLOR1;
    int Camera : CAMERA2;
};

struct Vout
{
    float4 Position : SV_POSITION;
    noperspective float4 Color : COLOR;
};
 
#define CameraMaxNum 4
uniform mat4[CameraMaxNum] ViewProjectionTransformArray;

void
main(Vout vout) 
{
    vout.Color = Color;

    // Assume the position is in world space.
    gl_Position = ViewProjectionTransformArray[Camera] * vec4(Position, 1); 
}
