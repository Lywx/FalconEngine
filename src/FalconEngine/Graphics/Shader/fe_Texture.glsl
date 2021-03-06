layout (binding = 0) uniform sampler2D      fe_TextureAmbient;
layout (binding = 1) uniform sampler2D      fe_TextureDiffuse;
layout (binding = 2) uniform sampler2D      fe_TextureEmissive;
layout (binding = 3) uniform sampler2D      fe_TextureShininess;
layout (binding = 4) uniform sampler2D      fe_TextureSpecular;
layout (binding = 5) uniform sampler2DArray fe_TextureFont;
uniform              bool                   fe_TextureAmbientExist;
uniform              bool                   fe_TextureDiffuseExist;
uniform              bool                   fe_TextureEmissiveExist;
uniform              bool                   fe_TextureSpecularExist;
uniform              bool                   fe_TextureShininessExist;
