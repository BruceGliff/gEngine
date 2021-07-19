#version 460
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D Tex_Diffuse;
uniform vec4 Col_Diffuse;
uniform int IsTex_Diffuse;

uniform sampler2D Tex_Specular;
uniform vec4 Col_Specular;
uniform int IsTex_Specular;

uniform sampler2D Tex_Ambient;
uniform vec4 Col_Ambient;
uniform int IsTex_Ambient;

vec4 selectColor(int Is_Texture, sampler2D tex, vec4 color) {
    if (Is_Texture == 1)
        return texture(tex, TexCoords);
    else
        return color;
}

void main() {
    vec4 diffColor = selectColor(IsTex_Diffuse, Tex_Diffuse, Col_Diffuse);
    vec4 specColor = selectColor(IsTex_Specular, Tex_Specular, Col_Specular);
    vec4 ambtColor = selectColor(IsTex_Ambient, Tex_Ambient, Col_Ambient);

    if (diffColor.a <  0.1)
        discard;
    FragColor = ambtColor;
}

