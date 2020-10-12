#version 460
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec2 texture_coord_noIntrop;
out vec3 color;
out vec2 tex_coord;
void main()
{
   color = vertex_color;
   tex_coord = texture_coord_noIntrop;
   gl_Position = vec4(vertex_position, 1.0);
}