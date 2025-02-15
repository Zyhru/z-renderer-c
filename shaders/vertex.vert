#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 tex;

out vec3 aColor;
out vec2 aTex;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    //gl_Position = vec4(pos, 1.0f);
    aColor = color;
    aTex = tex;
}
