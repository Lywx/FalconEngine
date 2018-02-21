// 4 x float4.
struct DirectionalLightData
{
    // Color
    vec3 Ambient;
    float Pad0;

    vec3 Diffuse;
    float Pad1;

    vec3 Specular;
    float Pad2;

    // Transform
    vec3 EyeDirection;
    float Pad3;
};

// 4 x float4.
struct PointLightData
{
    vec3 Ambient;
    float Constant;

    vec3 Diffuse;
    float Linear;

    vec3 Specular;
    float Quadratic;

    vec3 EyePosition;
    float Pad0;
};

// The layout is not ideal. According to:
// https://msdn.microsoft.com/en-us/library/windows/desktop/bb509632(v=vs.85).aspx
//
// 5 x float4.
struct SpotLightData
{
    vec3 Ambient;
    float Constant;

    vec3 Diffuse;
    float CosAngleInner;

    vec3 Specular;
    float CosAngleOuter;

    vec3 EyeDirection;
    float Linear;

    vec3 EyePosition;
    float Quadratic;
};

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

// @parameter Material. 
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

    cAmbient  = sAmbient * mAmbient;
    cDiffuse  = sDiffuse * mDiffuse * dotNL;
    cEmissive = mEmissive;
    cSpecular = sSpecular * mSpecular * pow(dotVR, mShininess);
}

// @require 
//
// #include "fe_Material.glsl".
// #include "fe_Texture.glsl".
void
CalcPhongLighting(

// @parameter 
    in vec2 texCoord,

// @parameter Transform.
    in vec3 eyeN, 
    in vec3 eyeV,
    in vec3 eyeL,

// @parameter Light Source.
    in vec3 sAmbient, 
    in vec3 sDiffuse, 
    in vec3 sSpecular, 

// @parameter Material.
    in MaterialColorData mColor,
    in MaterialTextureData mTexture,

// @return Standard Phong lighting contribution.
    out vec3 cAmbient,
    out vec3 cDiffuse,
    out vec3 cEmissive,
    out vec3 cSpecular)
{
    vec3 mAmbient;
    if (mTexture.AmbientExist)
    {
        mAmbient = vec3(texture(fe_TextureAmbient, texCoord));
    }
    else
    {
        mAmbient = mColor.Ambient;
    }

    vec3 mDiffuse;
    if (mTexture.DiffuseExist)
    {
        mDiffuse = vec3(texture(fe_TextureDiffuse, texCoord));
    }
    else
    {
        mDiffuse = mColor.Diffuse;
    }

    vec3 mEmissive;
    if (mTexture.EmissiveExist)
    {
        mEmissive = vec3(texture(fe_TextureEmissive, texCoord));
    }
    else
    {
        mEmissive = mColor.Emissive;
    }

    float mShininess;
    if (mTexture.ShininessExist)
    {
        mShininess = texture(fe_TextureShininess, texCoord).a;
    }
    else
    {
        mShininess = mColor.Shininess;
    }

    vec3 mSpecular;
    if (mTexture.SpecularExist)
    {
        mSpecular = vec3(texture(fe_TextureSpecular, texCoord));
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
    vec3 eyeH = normalize(eyeL + eyeV);

    // dot(n, l)
    float dotNL = max(dot(eyeN, eyeL), 0.0);

    // dot(n, h)
    float dotNH = max(dot(eyeN, eyeH), 0.0);

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
    in vec2 texCoord,

// @parameter Transform.
    in vec3 eyeN, 
    in vec3 eyeV,
    in vec3 eyeL,

// @parameter Light Source.
    in vec3 sAmbient, 
    in vec3 sDiffuse, 
    in vec3 sSpecular, 

// @parameter Material Color.
    in MaterialColorData mColor,
    in MaterialTextureData mTexture,

// @return Standard Phong lighting contribution.
    out vec3 cAmbient,
    out vec3 cDiffuse,
    out vec3 cEmissive,
    out vec3 cSpecular)
{
    vec3 mAmbient;
    if (mTexture.AmbientExist)
    {
        mAmbient = vec3(texture(fe_TextureAmbient, texCoord));
    }
    else
    {
        mAmbient = mColor.Ambient;
    }

    vec3 mDiffuse;
    if (mTexture.DiffuseExist)
    {
        mDiffuse = vec3(texture(fe_TextureDiffuse, texCoord));
    }
    else
    {
        mDiffuse = mColor.Diffuse;
    }

    vec3 mEmissive;
    if (mTexture.EmissiveExist)
    {
        mEmissive = vec3(texture(fe_TextureEmissive, texCoord));
    }
    else
    {
        mEmissive = mColor.Emissive;
    }

    float mShininess;
    if (mTexture.ShininessExist)
    {
        mShininess = texture(fe_TextureShininess, texCoord).a;
    }
    else
    {
        mShininess = mColor.Shininess;
    }

    vec3 mSpecular;
    if (mTexture.SpecularExist)
    {
        mSpecular = vec3(texture(fe_TextureSpecular, texCoord));
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
