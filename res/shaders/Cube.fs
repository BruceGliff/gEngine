#version 460

in vec3 normal_vector;
in vec3 fragPosition;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;

out vec4 fragColor;

void main()
{
    //  angle calculations
    vec3 lightDir = normalize(lightPosition - fragPosition);
    vec3 norm = normalize(normal_vector);
    float angle = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = angle * lightColor;


    float ambientStrength = 0.1;
    vec3 ambient =  ambientStrength * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    fragColor = vec4(result, 1.0);
}