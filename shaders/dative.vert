#version 330 core
layout(location = 0) in vec2 aPos;

out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj*view*model*vec4(aPos.x,aPos.y, 0.0, 1.0);

    if (gl_VertexID < 2){
        //Red
        color = vec3(1.0, 0.0, 0.0); 
    }
    else{
        //white
        color = vec3(1.0, 1.0, 1.0);
    }
}