void 
CalcPhongLighting(
    in vec2 texCoord,
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

    // vec3 materialAmbient = vec3(texture(fe_TextureAmbient, texCoord));
    vec3 materialDiffuse = vec3(texture(fe_TextureDiffuse, texCoord));
    // vec3 materialEmissive = vec3(texture(fe_TextureEmissive, texCoord));
    // float materialShininess = texture(fe_TextureShininess, texCoord).a;
    float materialShininess = 0.2;
    vec3 materialSpecular  = vec3(texture(fe_TextureSpecular, texCoord));

    // cAmbient  = sAmbient * materialAmbient;
    cAmbient  = sAmbient * materialDiffuse;
    cDiffuse  = sDiffuse * materialDiffuse * dotNL;
    cSpecular = sSpecular * materialSpecular * pow(dotVR, materialShininess);
}