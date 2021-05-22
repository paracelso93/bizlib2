#version 330

in vec2 o_texture_coord;
out vec4 color;

uniform sampler2D texture_sampler;

void main()
{
    color = texture(texture_sampler, o_texture_coord);
}
