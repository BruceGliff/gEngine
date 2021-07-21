#version 460
out vec4 FragColor;

in vec2 TexCoords;

struct SMaterial {
    sampler2D Tex;
    vec4 Col;
    int IsTex;
};
uniform SMaterial _Diffuse;
uniform SMaterial _Specular;
uniform SMaterial _Ambient;
vec4 selectColor(SMaterial mat) {
    if (mat.IsTex == 1)
        return texture(mat.Tex, TexCoords);
    else
        return mat.Col;
}

void main() {
    vec4 diffColor = selectColor(_Diffuse);
    vec4 specColor = selectColor(_Specular);
    vec4 ambtColor = selectColor(_Ambient);

    if (diffColor.a <  0.1)
        discard;
    FragColor = ambtColor;
}

