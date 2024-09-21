#version 330 core
layout (location = 0) in vec2 position;
uniform mat4 projection;

void main() {
    // 2D only
    gl_Position = projection * vec4(position.xy, 1.0, 1.0);
};
