#version 430 core

in Vout
{
    vec4 Color;
} fin;

layout(location = 0) out vec4 FragColor;

void
main()
{
    FragColor = fin.Color;
}
