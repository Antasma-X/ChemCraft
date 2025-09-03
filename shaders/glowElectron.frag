#version 330 core
in vec2 localPos;
out vec4 FragColor;

uniform float glow;  // you said this is 0.5

void main() {
    //float dist=length(localPos);
    //if (dist > 1.0) discard;

    FragColor = vec4(1.0, 0.0, 0.0,1.0); 
}