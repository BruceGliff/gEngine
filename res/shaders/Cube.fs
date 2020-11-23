#version 460

in vec3 normal_vector;
in vec3 fragPosition;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

out vec4 fragColor;

void main()
{
    //  angle calculations beetwen light and normal
    vec3 lightDir = normalize(lightPosition - fragPosition);
    vec3 norm = normalize(normal_vector);
    float angle_light = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = angle_light * lightColor;

    // angle calculations beetwen reflect light and viewPosition
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectedLight = reflect(-lightDir, norm);
    float angle_reflect = max(dot(reflectedLight, viewDir), 0.0);

    float specularStrength = 0.5;
    float spec = pow(angle_reflect, 32);
    vec3 specular = specularStrength * spec * lightColor; 


    float ambientStrength = 0.1;
    vec3 ambient =  ambientStrength * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragColor = vec4(result, 1.0);
}