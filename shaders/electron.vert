#version 330 core
layout(location = 0) in vec2 aPos;
layout(location =1) in float aTransparency;

out vec2 localPos;
out float transparency;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position=proj*view*model*vec4(aPos,0.0,1.0);
    localPos=aPos;
    transparency=aTransparency;
}