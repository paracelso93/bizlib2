#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coord;

out vec2 o_texture_coord;

uniform mat4 transform;

void main()
{
    o_texture_coord = texture_coord;
    gl_Position = transform * vec4(position, 1.0);
}
