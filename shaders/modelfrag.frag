#version 330 core
in vec2 aTex;

uniform sampler2D obj_texture;
out vec4 FragColor;

void main() {
   FragColor = vec4(1.0f, 0.5f, 0.43f, 1.0f);
   //FragColor = texture(obj_texture, aTex);
}
