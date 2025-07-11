//#version 330 core
//out vec4 FragColor;

//in float transparency;
//void main() {
    //works somehow 
//    vec2 coord = gl_PointCoord - vec2(0.5); 
//    if (dot(coord, coord) > 0.25) discard;

//    FragColor = vec4(1.0, 1.0, 1.0, transparency); // White dot
//} 

#version 330 core

in vec2 localPos;
in float transparency;

out vec4 FragColor;



void main() {
    float dist = length(localPos);     // distance from center
    if (dist > 1.0) discard;           // outside unit circle

    FragColor = vec4(1.0, 1.0, 1.0, transparency); 
}