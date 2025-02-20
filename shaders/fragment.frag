#version 330 core

in vec3 aColor;
in vec2 aTex;

uniform sampler2D minecraft_grass;
out vec4 FragColor;

void main() {
   //FragColor = texture(minecraft_grass, aTex) * vec4(aColor, 1.0f);
   //FragColor = vec4(aColor, 1.0f);
   FragColor = texture(minecraft_grass, aTex);
}
