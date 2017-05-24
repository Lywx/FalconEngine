#version 430 core

in Gout
{
    vec3 EyePosition;
    vec3 EyeNormal;
    noperspective vec3 Distance;
} fin;

layout(location = 0) out vec4 FragColor;

#fe_extension : enable
#include "fe_Material.glsl"
#fe_extension : disable

struct DirectionalLightData
{
    // Color
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    // Transform
    vec3 EyeDirection;
};

uniform vec3 AmbientOffset;
uniform DirectionalLightData DirectionalLight;
uniform MaterialColorData MaterialColor;

// @require None.
void 
CalcPhongLighting(
// @parameter Transform.
    in vec3 eyeN, 
    in vec3 eyeV,
    in vec3 eyeL,

// @parameter Light Source.
    in vec3 sAmbient, 
    in vec3 sDiffuse, 
    in vec3 sSpecular, 

// @parameter Material Color. 
    in vec3 mAmbient,
    in vec3 mDiffuse,
    in vec3 mEmissive,
    in vec3 mSpecular,
    in float mShininess,

// @return Standard Phong lighting contribution.
    out vec3 cAmbient,
    out vec3 cDiffuse,
    out vec3 cEmissive,
    out vec3 cSpecular)
{
    vec3 eyeR = reflect(-eyeL, eyeN);

    // dot(n, l)
    float dotNL = max(dot(eyeN, eyeL), 0.0);

    // dot(v, r)
    float dotVR = max(dot(eyeV, eyeR), 0.0);

    cAmbient  = AmbientOffset + sAmbient * mAmbient;
    cDiffuse  = sDiffuse * mDiffuse * dotNL;
    cEmissive = mEmissive;
    cSpecular = sSpecular * mSpecular * pow(dotVR, mShininess);
}

// @require 
// #include "fe_Lighting.glsl".
// #include "fe_Material.glsl".
// uniform MaterialColorData MaterialColor;
void
CalcPhongLighting(

// @parameter Transform.
    in vec3 eyeN, 
    in vec3 eyeV,
    in vec3 eyeL,

// @parameter Light Source.
    in vec3 sAmbient, 
    in vec3 sDiffuse, 
    in vec3 sSpecular, 

// @return Standard Phong lighting contribution.
    out vec3 cAmbient,
    out vec3 cDiffuse,
    out vec3 cEmissive,
    out vec3 cSpecular)
{
    vec3 mAmbient;
    mAmbient = MaterialColor.Ambient;

    vec3 mDiffuse;
    mDiffuse = MaterialColor.Diffuse;

    vec3 mEmissive;
    mEmissive = MaterialColor.Emissive;

    float mShininess;
    mShininess = MaterialColor.Shininess;

    vec3 mSpecular;
    mSpecular = MaterialColor.Specular;

    CalcPhongLighting(
        // @parameter Transform.
        eyeN, 
        eyeV,
        eyeL,

        // @parameter Light Source.
        sAmbient, 
        sDiffuse, 
        sSpecular, 

        // @parameter Material Color. 
        mAmbient,
        mDiffuse,
        mEmissive,
        mSpecular,
        mShininess,

        // @return Standard Phong lighting contribution.
        cAmbient,
        cDiffuse,
        cEmissive,
        cSpecular);
}

// @status Finished.
vec3 
CalcDirectionalLight(DirectionalLightData light, vec3 eyeN, vec3 eyeV)
{
    // Point to light source.
    vec3 eyeL = normalize(light.EyeDirection);

    vec3 cAmbient;
    vec3 cDiffuse;
    vec3 cEmissive;
    vec3 cSpecular; 

    CalcPhongLighting(
    // @parameter Transform.
        eyeN, 
        eyeV, 
        eyeL, 

    // @parameter Light Source.
        light.Ambient, 
        light.Diffuse, 
        light.Specular,

    // @return Standard Phong lighting contribution.
        cAmbient, 
        cDiffuse, 
        cEmissive,
        cSpecular);

    return cAmbient + cDiffuse + cEmissive + cSpecular;
}

struct LineData
{
    vec4  Color;
    float Width;
};

uniform LineData Line;

void
main()
{
    vec3 eyeN = normalize(fin.EyeNormal);

    // Point to camera.
    vec3 eyeV = normalize(-fin.EyePosition); 

    vec4 color = vec4(CalcDirectionalLight(DirectionalLight, eyeN, eyeV), 1.0);

    // Find the smallest distance
    float d = min(fin.Distance.x, fin.Distance.y);
    d = min(d, fin.Distance.z);

    float mixFactor = smoothstep(Line.Width - 1, Line.Width + 1, d);
    FragColor = mix(Line.Color, color, mixFactor);
}
