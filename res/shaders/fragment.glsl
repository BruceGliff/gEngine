#version 460
in vec3 color;
in vec2 tex_coord;
out vec4 frag_color;


uniform sampler2D tex;

void main() 
{
   frag_color = texture(tex, tex_coord) * vec4(color, 1.0) * 1.3;
}