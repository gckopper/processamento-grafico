#version 330 core
in vec3 vcolor;
out vec4 color;
void main() {
    color = vec4(vcolor.xyz, 1.0);
};
