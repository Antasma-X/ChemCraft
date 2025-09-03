#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 localPos;
 
void main() {
    gl_Position = proj * view * model * vec4(aPos, 0.0, 1.0);
    localPos = aPos;
}