#version 460
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D Tex_Diffuse;
uniform sampler2D Tex_Specular;

void main()
{
    vec4 texColor = texture(Tex_Diffuse, TexCoords);
    if (texColor.a <  0.1)
        discard;
    FragColor = texColor;
}