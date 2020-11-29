#version 460

struct MaterialProperties
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct LightProperties
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // attenuation
    float constant;
    float linear;
    float quadratic;
};

in vec3 normal_vector;
in vec3 fragPosition;
in vec2 tex_coord;
  
uniform MaterialProperties material;
uniform LightProperties light;

uniform vec3 viewPosition;

out vec4 fragColor;

void main()
{
    // Get from texture
    vec3 diffuseFromTex = vec3(texture(material.diffuse, tex_coord));
    vec3 specularFromTex = vec3(texture(material.specular, tex_coord));

    // attenuation
    float distant = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distant + light.quadratic * (distant * distant));
    
    // ambient
    vec3 ambient = light.ambient * diffuseFromTex;

    // diffuse
    vec3 norm = normalize(normal_vector);
    vec3 lightDir = normalize(light.position - fragPosition);
    float angle_light = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * angle_light * diffuseFromTex;

    // specular
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectedLight = reflect(-lightDir, norm);
    float spec = pow(max(dot(reflectedLight, viewDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * specularFromTex);

    vec3 result = ambient + specular + diffuse;
    result *= attenuation;
    fragColor = vec4(result, 0.0);
}