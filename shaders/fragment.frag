#version 330 core
in vec3 aColor;
in vec2 aTex;

uniform sampler2D minecraft_grass;
uniform sampler2D dvd_logo;

out vec4 FragColor;

void main() {
   //FragColor = vec4(aColor, 1.0f);
   FragColor = texture(minecraft_grass, aTex);
   //FragColor = texture(minecraft_grass, aTex) * vec4(aColor, 1.0f);
}
