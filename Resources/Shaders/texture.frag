#version 330

in vec2 o_texture_coord;
out vec4 color;

uniform sampler2D texture_sampler;
uniform vec4 in_color;

void main()
{
    color = in_color * texture(texture_sampler, o_texture_coord);
}
