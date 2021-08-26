#version 460
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

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
uniform int NumberOFPointLight;
uniform SPointLight PointLights[NR_POINT_LIGHTS];
uniform SSpotLight PointLight;

vec3 CalcDirLight(SGlobalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(SPointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec4 diffColor = selectColor(Material._Diffuse); // To discard transparent objects
    if (diffColor.a <  0.1)
        discard;
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0);//CalcDirLight(GlobalLight, norm, viewDir);

    for(int i = 0; i < NumberOFPointLight; i++)
        result += CalcPointLight(PointLights[i], norm, FragPos, viewDir);  

    FragColor = vec4(result, 1.0);
}


vec3 CalcDirLight(SGlobalLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float shininess = 32.0; // TODO make it material attribute
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // combine results
    vec3 ambient = light.colors.ambient * vec3(selectColor(Material._Ambient));
    vec3 diffuse = light.colors.diffuse * diff * vec3(selectColor(Material._Diffuse));
    vec3 specular = light.colors.specular * spec * vec3(selectColor(Material._Specular));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(SPointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float shininess = 32.0; // TODO make it material attribute
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.colors.ambient  * vec3(selectColor(Material._Ambient));
    vec3 diffuse  = light.colors.diffuse  * diff * vec3(selectColor(Material._Diffuse));
    vec3 specular = light.colors.specular * spec * vec3(selectColor(Material._Specular));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 