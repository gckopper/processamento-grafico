#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
out vec3 vcolor;
void main() {
    // 2D only
    gl_Position = vec4(position.xy, 1.0, 1.0);
    vcolor = color;
};
