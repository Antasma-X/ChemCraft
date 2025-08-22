#version 330 core

in vec2 localPos;
in float transparency;

out vec4 FragColor;

void main() {
    float dist=length(localPos);
    if (dist > 1.0) discard;

    FragColor = vec4(1.0, 1.0, 1.0, transparency); 
}