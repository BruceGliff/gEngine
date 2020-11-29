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
    // For spotlight
    vec3 direction;
    float cutOff; // cos of the angle
    float outerCutOff;

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
    vec3 specular = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 diffuseFromTex = vec3(texture(material.diffuse, tex_coord));
    vec3 ambient = light.ambient * diffuseFromTex;
    vec3 lightDir = normalize(light.position - fragPosition);
    float attenuation = 1.0;
    float intensity = 0.0;
    float thetta = dot(lightDir, normalize(-light.direction));
    if (thetta > light.outerCutOff)
    {
        intensity = 1.0;
        if (thetta < light.cutOff)
        {
            float epsilon   = light.cutOff - light.outerCutOff;
            intensity = clamp((thetta - light.outerCutOff) / epsilon, 0.0, 1.0); 
        }

        vec3 specularFromTex = vec3(texture(material.specular, tex_coord));
        // attenuation
        float distant = length(light.position - fragPosition);
        attenuation = 1.0 / (light.constant + light.linear * distant + light.quadratic * (distant * distant));
        // diffuse
        vec3 norm = normalize(normal_vector);
        float angle_light = max(dot(norm, lightDir), 0.0);
        diffuse = light.diffuse * angle_light * diffuseFromTex;
        // specular
        vec3 viewDir = normalize(viewPosition - fragPosition);
        vec3 reflectedLight = reflect(-lightDir, norm);
        float spec = pow(max(dot(reflectedLight, viewDir), 0.0), material.shininess);
        specular = light.specular * (spec * specularFromTex);
    }

    vec3 sd = (specular + diffuse) * attenuation * intensity;
    vec3 result = ambient + sd;
    fragColor = vec4(result, 0.0);
}