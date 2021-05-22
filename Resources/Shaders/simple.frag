#version 330

in vec3 pos;
out vec4 color;

void main()
{
    color = vec4(sin(pos.x), sin(pos.y), sin(pos.z), 1.0);
}
