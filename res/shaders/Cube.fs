#version 460

struct MaterialProperties
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct LightProperties
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 normal_vector;
in vec3 fragPosition;
  
uniform MaterialProperties material;
uniform LightProperties light;

uniform vec3 viewPosition;

out vec4 fragColor;

void main()
{
    // ambient
    vec3 ambient = light.ambient * material.ambient;

    // diffuse
    vec3 norm = normalize(normal_vector);
    vec3 lightDir = normalize(light.position - fragPosition);
    float angle_light = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (angle_light * material.diffuse);

    // specular
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectedLight = reflect(-lightDir, norm);
    float spec = pow(max(dot(reflectedLight, viewDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    
    vec3 result = ambient + specular + diffuse;
    fragColor = vec4(result, 0.0);
}