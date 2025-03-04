#version 330 core
layout(location = 0) in vec2 aPos;
layout(location =1) in float aTransparency;

out float transparency;


void main() {
    gl_Position = vec4(aPos.x,aPos.y, 0.0, 1.0);
    gl_PointSize = 8.0f; // Dot size in pixels

    transparency=aTransparency;
}