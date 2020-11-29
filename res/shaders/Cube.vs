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
	// here can be a problem with not normal matrix as normals can be not normals due to ununiform scale
	normal_vector = vec3(model *  vec4(surface_normal, 0.0));
	fragPosition = vec3(model *  vec4(vertex_position, 1.0));
	tex_coord = texture_position;
}