#version 330 core
in vec2 aTex;

uniform sampler2D obj_texture;
out vec4 FragColor;

void main() {
    vec2 uv = gl_FragCoord.xy / vec2(800.0, 600.0);
    vec3 interpolated_color = vec3(uv.x, uv.y, 0.5);
    FragColor = vec4(interpolated_color, 1.0);

    //FragColor = vec4(1.0f, 0.5f, 0.43f, 1.0f);
    //FragColor = texture(obj_texture, aTex);
}
