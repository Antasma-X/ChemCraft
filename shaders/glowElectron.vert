#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in float aTransparency;
void main(){
    // draw directly into NDC so no matrices/uniforms can break it
    gl_Position = vec4(aPos * 0.5, 0.0, 1.0); // scaled to fit
}
