#version 330 core
layout(location = 0) in vec2 aPos;

out vec3 color;

flat out vec3 startPos;
out vec3 vertPos;


uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj*view*vec4(aPos.x,aPos.y, 0.0, 1.0);

    vertPos = gl_Position.xyz ;
    startPos  = vertPos;

    if (gl_VertexID < 1){
        //Red
        color = vec3(1.0, 0.0, 0.0); 
    }
    else{
        //blue
        color = vec3(0.0, 1.0, 0.0);
    }
}



