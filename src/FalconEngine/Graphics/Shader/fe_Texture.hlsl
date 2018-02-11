Texture2D fe_TextureAmbient : register(t0);
Texture2D fe_TextureDiffuse : register(t1);
Texture2D fe_TextureEmissive : register(t2);
Texture2D fe_TextureShininess : register(t3);
Texture2D fe_TextureSpecular : register(t4);
Texture2DArray fe_TextureFont : register(t5);

SamplerState fe_TextureAmbientSampler : register(s0);
SamplerState fe_TextureDiffuseSampler : register(s1);
SamplerState fe_TextureEmissiveSampler : register(s2);
SamplerState fe_TextureShininessSampler : register(s3);
SamplerState fe_TextureSpecularSampler : register(s4);
SamplerState fe_TextureFontSampler : register(s5);