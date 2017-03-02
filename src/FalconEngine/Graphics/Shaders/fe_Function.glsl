void CalcEyeSpace(
    in vec3 modelPosition, 
    in vec3 modelNormal,
    out vec4 eyePosition,
    out vec3 eyeNormal) 
{
    eyeNormal = normalize(NormalTransform * modelNormal);
    eyePosition = (MVTransform * vec4(modelPosition, 1.0)).xyz;
}

void CalcPhongLighting(
    in vec3 eyeN, 
    in vec3 eyeV,
    in vec3 eyeL,
    in vec3 sAmbient, 
    in vec3 sDiffuse, 
    in vec3 sSpecular, 
    out vec3 cAmbient,
    out vec3 cDiffuse,
    out vec3 cSpecular)
{
    vec3 eyeR = reflect(-eyeL, eyeN);

    // dot(n, l)
    float dotNL = max(0, dot(eyeN, eyeL));

    // dot(v, r)
    float dotVR = max(dot(eyeV, eyeR), 0.0);

    // vec3 materialAmbient   = vec3(texture(fe_TextureAmbient,   fin.TexCoords));
    vec3 materialDiffuse   = vec3(texture(fe_TextureDiffuse,   fin.TexCoords));
    // vec3 materialEmissive  = vec3(texture(fe_TextureEmissive,  fin.TexCoords));
    // vec3 materialShininess = texture(fe_TextureShininess, fin.TexCoords).a;
    vec3 materialShininess = 0.2;
    vec3 materialSpecular  = vec3(texture(fe_TextureSpecular,  fin.TexCoords));

    // cAmbient  = sAmbient * materialAmbient;
    cAmbient  = sAmbient * materialDiffuse;
    cDiffuse  = sDiffuse * materialDiffuse * dotNL;
    cSpecular = sSpecular * materialSpecular * pow(dotVR, materialShininess);
}