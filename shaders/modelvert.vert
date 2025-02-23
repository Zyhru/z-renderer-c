#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 aTex;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    aTex = tex;
}
