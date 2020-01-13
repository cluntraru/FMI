#version 450 core
layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 inColor;

layout (location = 0) uniform mat4 translate;

out vec4 color;

void main() {
    gl_Position = translate * pos;
    color = inColor;
}
