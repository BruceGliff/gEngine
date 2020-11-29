#version 460

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 surface_normal;
layout (location = 2) in vec2 texture_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal_vector;
out vec3 fragPosition;
out vec2 tex_coord;

void main()
{
	gl_Position = projection * view * model * vec4(vertex_position, 1.0);
	normal_vector = surface_normal;
	fragPosition = vec3(model *  vec4(vertex_position, 1.0));
	tex_coord = texture_position;
}