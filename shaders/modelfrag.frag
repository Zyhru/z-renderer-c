#version 330 core
in vec2 aTex;

uniform sampler2D obj_texture;
out vec4 FragColor;

void main() {
   FragColor = vec4(0.8f, 0.8f, 0.8f, 1.0f);
   //FragColor = texture(obj_texture, aTex);
}
