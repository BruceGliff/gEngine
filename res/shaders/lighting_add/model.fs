#version 460
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normals;// TODO

struct SMaterialNode {
    sampler2D Tex;
    vec4 Col;
    int IsTex;
};
struct SMaterial {
    SMaterialNode _Diffuse;
    SMaterialNode _Ambient;
    SMaterialNode _Specular;
};
vec4 selectColor(SMaterialNode mat) {
    if (mat.IsTex == 1)
        return texture(mat.Tex, TexCoords);
    else
        return mat.Col;
}


struct SColorComponents {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SGlobalLight {
    vec3 direction;
    SColorComponents colors;
};

struct SPointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	SColorComponents colors;
};


struct SSpotLight {
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
  
    SColorComponents colors;      
};

// Material
uniform SMaterial Material;
// camera
uniform vec3 viewPos;
// lights
#define NR_POINT_LIGHTS 10
uniform SGlobalLight GlobalLight;
uniform SPointLight PointLights[NR_POINT_LIGHTS];
uniform SSpotLight PointLight;

void main() {
    vec4 diffColor = selectColor(Material._Diffuse);
    vec4 specColor = selectColor(Material._Specular);
    vec4 ambtColor = selectColor(Material._Ambient);

    if (diffColor.a <  0.1)
        discard;
    FragColor = ambtColor;
}

