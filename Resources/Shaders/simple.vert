#version 330

layout (location = 0) in vec3 position;
out vec3 pos;

uniform mat4 transform;

void main()
{
    pos = position + 0.5;
    //gl_Position = vec4(position.xyz, 1.0);
    gl_Position = transform * vec4(position.xyz, 1.0);
}
