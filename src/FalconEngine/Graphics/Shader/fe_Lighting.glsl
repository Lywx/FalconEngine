struct DirectionalLightData
{
    // Color
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    // Transform
    vec3 EyeDirection;
};

struct PointLightData
{
    // Color
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    // Constant
    float Constant;
    float Linear;
    float Quadratic;

    // Transform
    vec3 EyePosition;
};

struct SpotLightData
{
    // Color
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    // Constant
    float CosAngleInner;
    float CosAngleOuter;

    float Constant;
    float Linear;
    float Quadratic;

    // Transform
    vec3 EyeDirection;
    vec3 EyePosition;
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

// @return Standard Phong lighting contribution.
    out vec3 cAmbient,
    out vec3 cDiffuse,
    out vec3 cEmissive,
    out vec3 cSpecular)
{
    vec3 mAmbient;
    if (fe_TextureAmbientExist)
    {
        mAmbient = vec3(texture(fe_TextureAmbient, texCoord));
    }
    else
    {
        mAmbient = fe_Material.Ambient;
    }

    vec3 mDiffuse;
    if (fe_TextureDiffuseExist)
    {
        mDiffuse = vec3(texture(fe_TextureDiffuse, texCoord));
    }
    else
    {
        mDiffuse = fe_Material.Diffuse;
    }

    vec3 mEmissive;
    if (fe_TextureEmissiveExist)
    {
        mEmissive = vec3(texture(fe_TextureEmissive, texCoord));
    }
    else
    {
        mEmissive = fe_Material.Emissive;
    }

    float mShininess;
    if (fe_TextureShininessExist)
    {
        mShininess = texture(fe_TextureShininess, texCoord).a;
    }
    else
    {
        mShininess = fe_Material.Shininess;
    }

    vec3 mSpecular;
    if (fe_TextureSpecularExist)
    {
        mSpecular = vec3(texture(fe_TextureSpecular, texCoord));
    }
    else
    {
        mSpecular = fe_Material.Specular;
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

// @return Standard Phong lighting contribution.
    out vec3 cAmbient,
    out vec3 cDiffuse,
    out vec3 cEmissive,
    out vec3 cSpecular)
{
    vec3 mAmbient;
    if (fe_TextureAmbientExist)
    {
        mAmbient = vec3(texture(fe_TextureAmbient, texCoord));
    }
    else
    {
        mAmbient = fe_Material.Ambient;
    }

    vec3 mDiffuse;
    if (fe_TextureDiffuseExist)
    {
        mDiffuse = vec3(texture(fe_TextureDiffuse, texCoord));
    }
    else
    {
        mDiffuse = fe_Material.Diffuse;
    }

    vec3 mEmissive;
    if (fe_TextureEmissiveExist)
    {
        mEmissive = vec3(texture(fe_TextureEmissive, texCoord));
    }
    else
    {
        mEmissive = fe_Material.Emissive;
    }

    float mShininess;
    if (fe_TextureShininessExist)
    {
        mShininess = texture(fe_TextureShininess, texCoord).a;
    }
    else
    {
        mShininess = fe_Material.Shininess;
    }

    vec3 mSpecular;
    if (fe_TextureSpecularExist)
    {
        mSpecular = vec3(texture(fe_TextureSpecular, texCoord));
    }
    else
    {
        mSpecular = fe_Material.Specular;
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
