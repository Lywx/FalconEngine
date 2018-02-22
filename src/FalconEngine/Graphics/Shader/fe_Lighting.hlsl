#ifndef FE_LIGHTING_HLSL
#define FE_LIGHTING_HLSL

#include "fe_Material.hlsl"
#include "fe_Texture.hlsl"

// 4 x float4.
struct DirectionalLightData
{
    // Color
    float3 Ambient;
    float Pad0;

    float3 Diffuse;
    float Pad1;

    float3 Specular;
    float Pad2;

    // Transform
    float3 EyeDirection;
    float Pad3;
};

// 4 x float4.
struct PointLightData
{
    float3 Ambient;
    float Constant;

    float3 Diffuse;
    float Linear;

    float3 Specular;
    float Quadratic;

    float3 EyePosition;
    float Pad0;
};

// The layout is not ideal. According to:
// https://msdn.microsoft.com/en-us/library/windows/desktop/bb509632(v=vs.85).aspx
//
// 5 x float4.
struct SpotLightData
{
    float3 Ambient;
    float Constant;

    float3 Diffuse;
    float CosAngleInner;

    float3 Specular;
    float CosAngleOuter;

    float3 EyeDirection;
    float Linear;

    float3 EyePosition;
    float Quadratic;
};

// @require None.
void 
CalcPhongLighting(
// @parameter Transform.
    in float3 eyeN, 
    in float3 eyeV,
    in float3 eyeL,

// @parameter Light Source.
    in float3 sAmbient, 
    in float3 sDiffuse, 
    in float3 sSpecular, 

// @parameter Material Color. 
    in float3 mAmbient,
    in float3 mDiffuse,
    in float3 mEmissive,
    in float3 mSpecular,
    in float mShininess,

// @return Standard Phong lighting contribution.
    out float3 cAmbient,
    out float3 cDiffuse,
    out float3 cEmissive,
    out float3 cSpecular)
{
    float3 eyeR = reflect(-eyeL, eyeN);

    // dot(n, l)
    float dotNL = saturate(dot(eyeN, eyeL));

    // dot(v, r)
    float dotVR = saturate(dot(eyeV, eyeR));

    cAmbient  = sAmbient * mAmbient;
    cDiffuse  = sDiffuse * mDiffuse * dotNL;
    cEmissive = mEmissive;
    cSpecular = sSpecular * mSpecular * pow(dotVR, mShininess);
}

// @require 
//
// #include "fe_Material.hlsl".
// #include "fe_Texture.hlsl".
void
CalcPhongLighting(

// @parameter 
    in float2 texCoord,

// @parameter Transform.
    in float3 eyeN, 
    in float3 eyeV,
    in float3 eyeL,

// @parameter Light Source.
    in float3 sAmbient, 
    in float3 sDiffuse, 
    in float3 sSpecular, 

// @parameter Material.
    in MaterialColorData mColor,
    in MaterialTextureData mTexture,

// @return Standard Phong Lighting contribution.
    out float3 cAmbient,
    out float3 cDiffuse,
    out float3 cEmissive,
    out float3 cSpecular)
{
    float3 mAmbient;
    if (mTexture.AmbientExist)
    {
        mAmbient = fe_TextureAmbient.Sample(fe_TextureAmbientSampler, texCoord).xyz;
    }
    else
    {
        mAmbient = mColor.Ambient;
    }

    float3 mDiffuse;
    if (mTexture.DiffuseExist)
    {
        mDiffuse = fe_TextureDiffuse.Sample(fe_TextureDiffuseSampler, texCoord).xyz;
    }
    else
    {
        mDiffuse = mColor.Diffuse;
    }

    float3 mEmissive;
    if (mTexture.EmissiveExist)
    {
        mEmissive = fe_TextureEmissive.Sample(fe_TextureEmissiveSampler, texCoord).xyz;
    }
    else
    {
        mEmissive = mColor.Emissive;
    }

    float mShininess;
    if (mTexture.ShininessExist)
    {
        mShininess = fe_TextureShininess.Sample(fe_TextureShininessSampler, texCoord).a;
    }
    else
    {
        mShininess = mColor.Shininess;
    }

    float3 mSpecular;
    if (mTexture.SpecularExist)
    {
        mSpecular = fe_TextureSpecular.Sample(fe_TextureSpecularSampler, texCoord).xyz;
    }
    else
    {
        mSpecular = mColor.Specular;
    }

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

// @require None.
void 
CalcBlinnPhongLighting(
// @parameter Transform.
    in float3 eyeN, 
    in float3 eyeV,
    in float3 eyeL,

// @parameter Light Source.
    in float3 sAmbient, 
    in float3 sDiffuse, 
    in float3 sSpecular, 

// @parameter Material Color. 
    in float3 mAmbient,
    in float3 mDiffuse,
    in float3 mEmissive,
    in float3 mSpecular,
    in float mShininess,

// @return Standard Phong lighting contribution.
    out float3 cAmbient,
    out float3 cDiffuse,
    out float3 cEmissive,
    out float3 cSpecular)
{
    float3 eyeH = normalize(eyeL + eyeV);

    // dot(n, l)
    float dotNL = saturate(dot(eyeN, eyeL));

    // dot(n, h)
    float dotNH = saturate(dot(eyeN, eyeH));

    cAmbient  = sAmbient * mAmbient;
    cDiffuse  = sDiffuse * mDiffuse * dotNL;
    cEmissive = mEmissive;
    cSpecular = sSpecular * mSpecular * pow(dotNH, mShininess);
}

// @require 
//
// #include "fe_Material.glsl".
// #include "fe_Texture.glsl".
void
CalcBlinnPhongLighting(

// @parameter 
    in float2 texCoord,

// @parameter Transform.
    in float3 eyeN, 
    in float3 eyeV,
    in float3 eyeL,

// @parameter Light Source.
    in float3 sAmbient, 
    in float3 sDiffuse, 
    in float3 sSpecular,

// @parameter Material Color.
    in MaterialColorData mColor,
    in MaterialTextureData mTexture, 

// @return Standard Phong lighting contribution.
    out float3 cAmbient,
    out float3 cDiffuse,
    out float3 cEmissive,
    out float3 cSpecular)
{
    float3 mAmbient;
    if (mTexture.AmbientExist)
    {
        mAmbient = fe_TextureAmbient.Sample(fe_TextureAmbientSampler, texCoord).xyz;
    }
    else
    {
        mAmbient = mColor.Ambient;
    }

    float3 mDiffuse;
    if (mTexture.DiffuseExist)
    {
        mDiffuse = fe_TextureDiffuse.Sample(fe_TextureDiffuseSampler, texCoord).xyz;
    }
    else
    {
        mDiffuse = mColor.Diffuse;
    }

    float3 mEmissive;
    if (mTexture.EmissiveExist)
    {
        mEmissive = fe_TextureEmissive.Sample(fe_TextureEmissiveSampler, texCoord).xyz;
    }
    else
    {
        mEmissive = mColor.Emissive;
    }

    float mShininess;
    if (mTexture.ShininessExist)
    {
        mShininess = fe_TextureShininess.Sample(fe_TextureShininessSampler, texCoord).a;
    }
    else
    {
        mShininess = mColor.Shininess;
    }

    float3 mSpecular;
    if (mTexture.SpecularExist)
    {
        mSpecular = fe_TextureSpecular.Sample(fe_TextureSpecularSampler, texCoord).xyz;
    }
    else
    {
        mSpecular = mColor.Specular;
    }

    CalcBlinnPhongLighting(
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

#endif