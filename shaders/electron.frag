#version 330 core
out vec4 FragColor;

in float transparency;
void main() {
    //works somehow 
    vec2 coord = gl_PointCoord - vec2(0.5); 
    if (dot(coord, coord) > 0.25) discard;

    FragColor = vec4(1.0, 1.0, 1.0, transparency); // White dot
}