#version 330 core
layout (location = 0) in vec2 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

//out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj*view*model*vec4(aPos.x,aPos.y, 0.0, 1.0);
    //ourColor = aColor;
    TexCoord = aTexCoord;
}