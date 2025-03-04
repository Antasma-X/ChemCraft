#version 330 core
out vec4 FragColor;

uniform vec3 color;
void main() {
    //Blue
    FragColor = vec4(color,1.0);
}